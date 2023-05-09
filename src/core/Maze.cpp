#include "Maze.h"

Maze::Maze(std::vector<std::vector<Maze::Object>> objects)
    : objects{objects},
    picker{new ColorPicker()}
{
    srand(unsigned(time(NULL)));
    std::vector<glm::vec3> cubePositions{};

    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            Object obj = objects[row][col];
            if (obj == Maze::Object::WALL){
                auto cubePos = glm::vec3(col, 0, row);
                cubePositions.push_back(cubePos);
            }
            // else if (obj == Maze::Object::EMPTY){
            //     int randomNum = rand() % 4;
            //     int placeFlower = rand() % 2;
            //     if (randomNum == 0){
            //         addRandomizedModel("../assets/meshes/Rocks/Rocks.dae", glm::vec3{col, -0.35f, row}, glm::vec3{0.3f}, false);
            //     }else if (randomNum == 1){
            //         addRandomizedModel("../assets/meshes/RocksVar1/RocksVar1.dae", glm::vec3{col, -0.35f, row}, glm::vec3{0.3f}, false);
            //     }
            //     if (placeFlower) {
            //         addRandomizedModel("../assets/meshes/LowPolyPlant/LowPolyPlant.dae", glm::vec3{col, -0.55f, row}, glm::vec3{0.1f}, false);
            //     }
            //     addRandomizedModel("../assets/meshes/grassSpot/grassSpot.obj", glm::vec3{col, -0.5f, row});
            // }
        }
    }
    glm::mat4 model{1.0f};
    model = glm::translate(model, glm::vec3{0.0f, 1.0f, 0.0f});
    std::vector<glm::mat4> modelPositions = {};
    modelPositions.push_back(model);
    models.push_back(new Model("../assets/meshes/Rocks/Rocks.dae", modelPositions, false));
    addSpawnSurroundingCubes(cubePositions);
    cubes = new Cube{cubePositions};
}

void Maze::addRandomizedModel(std::string path, glm::vec3 position, glm::vec3 size, bool flip){
    float x = (float) rand() / RAND_MAX - 0.5f;
    float z = (float) rand() / RAND_MAX - 0.5f;
    float sizeOffset = (float) rand() / RAND_MAX - 0.5f;
    float rotation = (float) rand() / RAND_MAX * 360.0f;
    models.push_back(new Model(path.c_str(), glm::vec3(position.x + x, position.y, position.z + z), size + glm::vec3{(sizeOffset/2.0f)/10.0f}, rotation, flip));
}

void Maze::addSpawnSurroundingCubes(std::vector<glm::vec3> &cubePositions){
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
        cubePositions.push_back(pos);
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
    // cubes->draw();
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
    return *(this->cubes);
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