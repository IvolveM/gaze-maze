#pragma once

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include "../objects/based/Cube.h"
#include "../core/Maze.h"
#include "MazeGenerator.h"

class MazeLoader {
    static const char WALLCHAR = '#';
    static const char EMPTYCHAR = ' ';

    public:
        MazeLoader();
        ~MazeLoader();

        Maze* loadMazeFromFile(std::string fileName);

    private:
        void loadMaze();
        void loadLine(const std::string& line);
        void addCubePosition(const glm::vec3& cubePos);

        Maze::MazeBuilder mazeBuilder;

        Cube* mazeInstance;
        std::vector<glm::vec3> cubePositions;
        std::ifstream* mazeFile;

        int colOffset = 0;
        int rowOffset = 0;
};