
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include "../objects/based/Cube.h"

class MazeLoader {
    static const char WALLCHAR = '#';
    static const char EMPTYCHAR = ' ';

    public:
        MazeLoader();
        ~MazeLoader();

        std::vector<Cube*> loadMazeFromFile(std::string fileName);

    private:
        void loadMaze();
        void loadLine(const std::string& line);
        void addCube(Cube* cube);

        std::ifstream* mazeFile;
        std::vector<Cube*> mazeCubes;

        float colOffset = 0.0f;
        float rowOffset = 0.0f;
};