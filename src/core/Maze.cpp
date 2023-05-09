#include "Maze.h"

Maze::Maze(std::vector<std::vector<Maze::Object>> objects)
    : objects{objects},
    picker{new ColorPicker()}
{
    srand(unsigned(time(NULL)));
    std::vector<glm::mat4> cubeModelMatrices = {};

    std::vector<glm::mat4> rockPositions = {};
    std::vector<glm::mat4> rockVarPositions = {};
    std::vector<glm::mat4> lowPolyPlantPositions = {};
    std::vector<glm::mat4> grassSpotPositions = {};
    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            Object obj = objects[row][col];
            if (obj == Maze::Object::WALL){
                glm::mat4 model{1.0f};
                model = glm::translate(model, glm::vec3{col, 0.0f, row});
                model = glm::scale(model, glm::vec3{0.5f});
                cubeModelMatrices.push_back(model);
            }
            else if (obj == Maze::Object::EMPTY){
                int randomNum = rand() % 4;
                int placeFlower = rand() % 2;
                if (randomNum == 0){
                    rockPositions.push_back(getRandomizedModelMatrix(glm::vec3{col, -0.35f, row}, glm::vec3{0.3f}, false));
                }else if (randomNum == 1){
                    rockVarPositions.push_back(getRandomizedModelMatrix(glm::vec3{col, -0.35f, row}, glm::vec3{0.3f}, false));
                }
                if (placeFlower) {
                    lowPolyPlantPositions.push_back(getRandomizedModelMatrix(glm::vec3{col, -0.55f, row}, glm::vec3{0.1f}, false));
                }
                grassSpotPositions.push_back(getRandomizedModelMatrix(glm::vec3{col, -0.5f, row}));
                grassSpotPositions.push_back(getRandomizedModelMatrix(glm::vec3{col, -0.5f, row}));
            }
        }
    }
    models.push_back(new Model("../assets/meshes/Rocks/Rocks.dae", rockPositions, false));
    models.push_back(new Model("../assets/meshes/RocksVar1/RocksVar1.dae", rockVarPositions, false));
    models.push_back(new Model("../assets/meshes/LowPolyPlant/LowPolyPlant.dae", lowPolyPlantPositions, false));
    models.push_back(new Model("../assets/meshes/grassSpot/grassSpot.obj", grassSpotPositions, false));
    addSpawnSurroundingCubes(cubeModelMatrices);
    cubes = new Model{"../assets/meshes/Wall/Wall.dae", cubeModelMatrices};
}

glm::mat4 Maze::getRandomizedModelMatrix(glm::vec3 position, glm::vec3 size, bool flip){
    float x = (float) rand() / RAND_MAX - 0.5f;
    float z = (float) rand() / RAND_MAX - 0.5f;
    float sizeOffset = (float) rand() / RAND_MAX - 0.5f;
    float rotation = (float) rand() / RAND_MAX * 360.0f;
    glm::vec3 newPosition(position.x + x, position.y, position.z + z);
    glm::vec3 newSize = size + glm::vec3{(sizeOffset/2.0f)/10.0f};
    glm::mat4 model{1.0f};
    model = glm::translate(model, newPosition);
    model = glm::scale(model, newSize);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3{0.0f, 1.0f, 0.0f});
    return model;
}

void Maze::addSpawnSurroundingCubes(std::vector<glm::mat4> &cubeModelMatrices){
    std::vector<glm::vec3> positions = {
        {-1.0f, 0.0f, -1.0f}, 
        {0.0f, 0.0f, -1.0f}, 
        {1.0f, 0.0f, -1.0f}, 
        {2.0f, 0.0f, -1.0f}, 
        {-1.0f, 0.0f, 0.0f},
        {-1.0f, 0.0f, 1.0f},
        {-1.0f, 0.0f, 2.0f},
    };
    for(auto pos: positions){
        glm::mat4 model{1.0f};
        model = glm::translate(model, pos);
        model = glm::scale(model, glm::vec3{0.5f});
        cubeModelMatrices.push_back(model);
    }
}

Maze::~Maze()
{
    delete cubes;
    for (auto m : models)
        delete m;
    delete picker;
}

void Maze::draw()
{
    cubes->draw();
    for (auto model: models){
        model->draw();
    }
}

Maze::MazeBuilder::MazeBuilder(int width, int height)
    : 
    width{width},
    height{height},
    objects {
        height,
        std::vector{width, Maze::Object::EMPTY}
    }
{

}

void Maze::MazeBuilder::addWall(int x, int y)
{
    objects[y][x] = Maze::Object::WALL;
}

Maze* Maze::MazeBuilder::build()
{
    objects[0][0] = Maze::Object::EMPTY;
    objects[0][1] = Maze::Object::EMPTY;
    objects[1][0] = Maze::Object::EMPTY;
    objects[height - 1][width - 1] = Maze::Object::EMPTY;
    objects[height - 1][width - 2] = Maze::Object::EMPTY;
    objects[height - 2][width - 1] = Maze::Object::EMPTY;
    return new Maze(objects);
}

Mesh Maze::getMesh(){
    return Cube();
}

std::vector<std::vector<Maze::Object>> Maze::getGrid() {
    return this->objects;
}

void Maze::addPickableModels(char* modelPath, const int amount, const bool flipUvs) {
    srand(unsigned(time(NULL)));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distPos(-0.25, 0.25);
    std::uniform_real_distribution<double> distRot(0, 359);

    // shuffle indices
    std::vector<int> rowIndices(objects.size());
    std::vector<int> columnIndices(objects[0].size());
    std::iota(rowIndices.begin(), rowIndices.end(), 0);
    std::iota(columnIndices.begin(), columnIndices.end(), 0);
    std::random_shuffle(rowIndices.begin(), rowIndices.end());
    std::random_shuffle(columnIndices.begin(), columnIndices.end());

    int count = 0;

    for (int row : rowIndices){
        for (int col : columnIndices){
            if (count == amount) 
                return;

            Object obj = objects[row][col];
            if (obj == Maze::Object::EMPTY){
                float x = distPos(gen);
                float z = distPos(gen);
                float r = distRot(gen);

                Model* m = new Model(modelPath, glm::vec3(col + x, -0.43f, row + z), 
                                    glm::vec3(0.3f, 0.3f, 0.3f),
                                    r, flipUvs, ResourceManager::getShader("mesh"));
                models.push_back(m);
                picker->addModel(m);

                ++count;
            }
        }
    }
}

void Maze::removePickableModel(unsigned char pixel[4]) {
    Model* m = this->picker->getModelByColor(pixel);
    if (m == nullptr){
        std::cout << "Could not find object with id " << pixel << std::endl;
        return;
    } 
    auto it{std::find_if(models.begin(), models.end(), [m](const Model* model){return m == model;})};
    if (it != models.end()) {
        auto idx{it - models.begin()};
        this->models.erase(models.begin() + idx);
        this->picker->removeModelByColor(pixel);
        delete m;
    }
}

void Maze::drawPickerBuffer() {
    this->picker->drawModels();
}