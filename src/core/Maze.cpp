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
            else if (obj == Maze::Object::EMPTY){
                float x1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                float x2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                float y1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                float y2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                int randomNum = rand()%4;
                if (randomNum == 0){
                    models.push_back(new Model("../assets/meshes/Rocks/Rocks.dae", glm::vec3(col + x1, -0.35f, row + y1), glm::vec3{0.3f,0.3f,0.3f}, 0.0f, false));
                }else if (randomNum == 1){
                    models.push_back(new Model("../assets/meshes/RocksVar1/RocksVar1.dae", glm::vec3(col + x2, -0.35f, row + y2), glm::vec3{0.3f,0.3f,0.3f}, 0.0f, false));
                }
                for (int i = 0; i < 2; i++){
                    addRandomizedModel("../assets/meshes/LowPolyPlant/LowPolyPlant.dae", glm::vec3{col, -0.55f, row}, glm::vec3{0.1f}, false);
                }
                addRandomizedModel("../assets/meshes/grassSpot/grassSpot.obj", glm::vec3{col, -0.5f, row});
            }
        }
    }
    cubes = new Cube{cubePositions};
}

void Maze::addRandomizedModel(std::string path, glm::vec3 position, glm::vec3 size, bool flip){
    float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
    float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
    float sizeOffset = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
    float rotation = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * 3.14f;
    models.push_back(new Model(path.c_str(), glm::vec3(position.x + x, position.y, position.z + z), size + glm::vec3{(sizeOffset/2.0f)/10.0f}, glm::degrees(rotation), flip));
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
    : objects {
        height,
        std::vector{width, Maze::Object::EMPTY}
    },
    width{width},
    height{height}
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

    // using a float in range [0,1] and rounding it after seems to produce less clusters
    std::uniform_real_distribution<double> choice(0, 1);
    int count = 0;

    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            if (count == amount) 
                return;

            Object obj = objects[row][col];
            if (obj == Maze::Object::EMPTY && std::round(choice(gen))){
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