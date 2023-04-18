#include "Maze.h"

Maze::Maze(std::vector<std::vector<Maze::Object>> objects)
    : objects{objects}
{
    std::vector<glm::vec3> cubePositions{};
    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            if (objects[row][col] == Maze::Object::WALL){
                for (int i = 0; i < 1000; i++){
                    auto cubePos = glm::vec3(col, i, row);
                    cubePositions.push_back(cubePos);
                }
            }
        }
    }
    cubes = new Cube{cubePositions};
}

void Maze::draw()
{
    cubes->draw();
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
    objects[height - 1]     [width - 1] = Maze::Object::EMPTY;
    objects[height - 1]     [width - 2] = Maze::Object::EMPTY;
    objects[height - 2] [width - 1] = Maze::Object::EMPTY;
    return new Maze(objects);
}

Mesh Maze::getMesh(){
    return *(this->cubes);
}
