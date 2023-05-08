#pragma once

#include "../objects/based/Cube.h"
#include "../objects/model/Model.h"
#include "../utils/ColorPicker.h"

#include <vector>
#include <random>

class Maze {
    public:
        enum Object {
            WALL,
            EMPTY
        };

        ~Maze();
        void draw();
        void drawPickerBuffer();
        Mesh getMesh();
        std::vector<std::vector<Maze::Object>> getGrid();

        void addPickableModels(char* modelPath, const int amount, const bool flipUvs = true);
        void removePickableModel(unsigned char pixel[4]);

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
    private:
        std::vector<std::vector<Maze::Object>> objects;
        Cube* cubes;
        std::vector<Model*> models{};
        ColorPicker* picker;
        
        Maze(std::vector<std::vector<Maze::Object>> objects);
        void addRandomizedModel(std::string path, glm::vec3 position, glm::vec3 size = glm::vec3{1.0f}, bool flip = true);
};