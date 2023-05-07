#include "Maze.h"

Maze::Maze(std::vector<std::vector<Maze::Object>> objects)
    : objects{objects}
{
    std::vector<glm::vec3> cubePositions{};
    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            Object obj = objects[row][col];
            std::cout << col << " " << row;
            std::cout << " ";
            if (obj == Maze::Object::WALL){
                std::cout << "WALL";
                auto cubePos = glm::vec3(col, 0, row);
                cubePositions.push_back(cubePos);
            }
            else if (obj == Maze::Object::EMPTY){
                float x1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                // float x2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                // float x3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                float y1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                // float y2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                // float y3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX) - 0.5f;
                models.push_back(Model("../assets/meshes/grassSpot/grassSpot.obj", glm::vec3(col + x1, -0.5f, row + y1)));
                // models.push_back(Model("../assets/meshes/grassSpot/grassSpot.obj", glm::vec3(col + x2, -0.5f, row + y2)));
                // models.push_back(Model("../assets/meshes/grassSpot/grassSpot.obj", glm::vec3(col + x3, -0.5f, row + y3)));
                std::cout << "EMPTY";

            }
        }
        std::cout << std::endl;
    }
    cubes = new Cube{cubePositions};
}

Maze::~Maze()
{
    delete cubes;
}

void Maze::draw()
{
    cubes->draw();
    for (auto model: models){
        model.draw();
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
