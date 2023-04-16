#include "Maze.h"

Maze::Maze(std::vector<std::vector<Maze::Object>> objects)
    : objects{objects}
{
    std::vector<glm::vec3> cubePositions{};
    for (int row = 0; row < objects.size(); row++){
        for (int col = 0; col < objects[row].size(); col++){
            if (objects[row][col] == Maze::Object::WALL){
                auto cubePos = glm::vec3(col, 0.0f, row);
                cubePositions.push_back(cubePos);
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
    }
{

}

void Maze::MazeBuilder::addWall(int x, int y)
{
    objects[y][x] = Maze::Object::WALL;
}

Maze* Maze::MazeBuilder::build()
{
    return new Maze(objects);
}
