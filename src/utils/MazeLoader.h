
#include <iostream>
#include <fstream> 
#include <string>
#include <vector>
#include "../objects/based/Cube.h"

class MazeLoader {
    static constexpr char* WALLCHAR = "#";
    static constexpr char* EMPTYCHAR = " ";

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
};