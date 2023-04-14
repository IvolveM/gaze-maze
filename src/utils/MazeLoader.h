
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include "../objects/based/Cube.h"
#include "MazeGenerator.h"

class MazeLoader {
    static const char WALLCHAR = '#';
    static const char EMPTYCHAR = ' ';

    public:
        MazeLoader();
        ~MazeLoader();

        Cube* loadMazeFromFile(std::string fileName);

    private:
        void loadMaze();
        void loadLine(const std::string& line);
        void addCubePosition(const glm::vec3& cubePos);

        Cube* mazeInstance;
        std::vector<glm::vec3> cubePositions;
        std::ifstream* mazeFile;

        float colOffset = 0.0f;
        float rowOffset = 0.0f;
};