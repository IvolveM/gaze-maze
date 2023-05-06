#pragma once

#include "../objects/based/Cube.h"
#include "../objects/model/Model.h"
#include <vector>
#include <random>

class Maze {
    private:
        enum Object {
            WALL,
            EMPTY
        };
        std::vector<std::vector<Maze::Object>> objects;
        std::vector<Model> models{};
        Cube* cubes;

        Maze(std::vector<std::vector<Maze::Object>> objects);
    public:
        ~Maze();
        void draw();
        Mesh getMesh();

        // builder class
        class MazeBuilder{
            private:
                int width = 0;
                int height = 0;
                std::vector<std::vector<Maze::Object>> objects{};
            public: 
                MazeBuilder(int width, int height);
                void addWall(int x, int y);
                Maze* build();
        };
};