#include "Maze.h"

Maze::Maze(std::vector<std::vector<MazeItem::Object>> objects)
    : objects{objects},
    picker{new ColorPicker()}
{
    srand(unsigned(time(NULL)));
    std::vector<glm::vec3> cubePositions{};

    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            MazeItem::Object obj = objects[row][col];
            if (obj == MazeItem::Object::WALL){
                auto cubePos = glm::vec3(col, 0, row);
                cubePositions.push_back(cubePos);
            }
            else if (obj == MazeItem::Object::EMPTY){
                int randomNum = rand() % 4;
                int placeFlower = rand() % 2;
                if (randomNum == 0){
                    addRandomizedModel("../assets/meshes/Rocks/Rocks.dae", glm::vec3{col, -0.35f, row}, glm::vec3{0.3f}, false);
                }else if (randomNum == 1){
                    addRandomizedModel("../assets/meshes/RocksVar1/RocksVar1.dae", glm::vec3{col, -0.35f, row}, glm::vec3{0.3f}, false);
                }
                if (placeFlower) {
                    addRandomizedModel("../assets/meshes/LowPolyPlant/LowPolyPlant.dae", glm::vec3{col, -0.55f, row}, glm::vec3{0.1f}, false);
                }
                addRandomizedModel("../assets/meshes/grassSpot/grassSpot.obj", glm::vec3{col, -0.5f, row});
            }
        }
    }
    addSpawnSurroundingCubes(cubePositions);
    cubes = new Cube{cubePositions};
}

void Maze::addRandomizedModel(std::string path, glm::vec3 position, glm::vec3 size, bool flip){
    float x = (float) rand() / RAND_MAX - 0.5f;
    float z = (float) rand() / RAND_MAX - 0.5f;
    float sizeOffset = (float) rand() / RAND_MAX - 0.5f;
    float rotation = (float) rand() / RAND_MAX * 3.14f;
    models.push_back(new Model(path.c_str(), glm::vec3(position.x + x, position.y, position.z + z), size + glm::vec3{(sizeOffset/2.0f)/10.0f}, glm::degrees(rotation), flip));
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
    for (auto model : models)
        delete model;
    delete picker;
    for (auto enemy : enemies)
        delete enemy;
}

void Maze::draw() {
    cubes->draw();
    for (const auto& model: models){
        model->draw();
    }
    for (const auto& enemy: enemies){
        enemy->draw();
    }
}

void Maze::update(const float dt) {
    for (const auto& enemy: enemies){
        enemy->update(dt);
    }
}

Maze::MazeBuilder::MazeBuilder(int width, int height)
    : 
    width{width},
    height{height},
    objects {
        height,
        std::vector{width, MazeItem::Object::EMPTY}
    }
{

}

void Maze::MazeBuilder::addWall(int x, int y)
{
    objects[y][x] = MazeItem::Object::WALL;
}

Maze* Maze::MazeBuilder::build()
{
    objects[0][0] = MazeItem::Object::EMPTY;
    objects[0][1] = MazeItem::Object::EMPTY;
    objects[1][0] = MazeItem::Object::EMPTY;
    objects[height - 1][width - 1] = MazeItem::Object::EMPTY;
    objects[height - 1][width - 2] = MazeItem::Object::EMPTY;
    objects[height - 2][width - 1] = MazeItem::Object::EMPTY;
    return new Maze(objects);
}

Mesh Maze::getMesh(){
    return *(this->cubes);
}

void Maze::addPickableModels(char* modelPath, const int amount, const bool flipUvs) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distPos(-0.25, 0.25);
    std::uniform_int_distribution<> distRot(0, 359);

    // using a float in range [0,1] and rounding it after seems to produce less clusters
    std::uniform_real_distribution<double> choice(0, 1);
    int count = 0;

    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            if (count == amount) 
                return;

            MazeItem::Object obj = objects[row][col];
            if (obj == MazeItem::Object::EMPTY && std::round(choice(gen))){
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

void Maze::removePickableModel(unsigned char pixel[4], const glm::vec3& playerPos, const float minDistance) {
    Model* m = this->picker->getModelByColor(pixel);
    if (m == nullptr){
        std::cout << "Could not find object with id " << pixel << std::endl;
        return;
    } 

    if (glm::distance2(playerPos, m->getPosition()) > minDistance * minDistance)
        return;

    auto it{std::find_if(models.begin(), models.end(), [m](const Model* model){return m == model;})};
    if (it != models.end()) {
        auto idx{it - models.begin()};
        this->models.erase(models.begin() + idx);
        this->picker->removeModelByColor(pixel);
        delete m;
    }
    ResourceManager::playSound("eating");
}

void Maze::drawPickerBuffer() {
    this->picker->drawModels();
}

glm::ivec2 Maze::getRandomEmptyPos() const {
    std::vector<glm::ivec2> empty = {};
    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            if (objects[row][col] == MazeItem::Object::EMPTY) {
                empty.push_back(glm::ivec2(col, row));
            }
        }
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomPos(0, empty.size()-1);
    return empty[randomPos(gen)];
}

void Maze::addEnemies(const int amount) {
    for (int i = 0; i < amount; i++) {
        this->enemies.push_back(
            new Enemy(100.0f, getRandomEmptyPos(), objects, glm::vec3(1.0f,1.0f,1.0f))
        );
    }
}