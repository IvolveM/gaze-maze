
#include "MazeLoader.h"
#include <random>

MazeLoader::MazeLoader() {

}

MazeLoader::~MazeLoader() {
    delete this->mazeFile;
}

Cube* MazeLoader::loadMazeFromFile(std::string fileName) {
    this->mazeFile = new std::ifstream(fileName);
    loadMaze();
    this->mazeFile->close();
    return this->mazeInstance;
}

void MazeLoader::loadMaze() {
    if (this->mazeFile->is_open()) {
        std::string line;
        while (this->mazeFile->good()) {
            std::getline(*(this->mazeFile), line);
            loadLine(line);
        }
        this->mazeInstance = new Cube(this->cubePositions);
    }
    else {
        std::cout << "Couldn't open file" << std::endl;
    }
}

void MazeLoader::loadLine(const std::string& line) {
    for (const char& el : line) {
        if (WALLCHAR == el) {
            for (int i = 0; i < 10; i++){
                addCubePosition(glm::vec3(this->colOffset, (float)i, this->rowOffset));
            }
        }
        else if (EMPTYCHAR == el) {}
        this->colOffset++;
    }
    this->colOffset = 0.0f;
    this->rowOffset++;
}

void MazeLoader::addCubePosition(const glm::vec3& cubePos) {
    this->cubePositions.push_back(cubePos);
}
