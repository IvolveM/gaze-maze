#pragma once

#include "../objects/based/Cube.h"
#include <vector>

class Maze {
    private:
        enum Object {
            WALL,
            EMPTY
        };
        std::vector<std::vector<Maze::Object>> objects;
        Cube* cubes;

        Maze(std::vector<std::vector<Maze::Object>> objects);

    public:
        void draw();

        // builder class
        class MazeBuilder{
            private:
                std::vector<std::vector<Maze::Object>> objects{};
            public: 
                MazeBuilder(int width, int height);
                void addWall(int x, int y);
                Maze* build();
        };
};