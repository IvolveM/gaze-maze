
#include "MazeLoader.h"

MazeLoader::MazeLoader() {

}

MazeLoader::~MazeLoader() {
    delete this->mazeFile;
}

std::vector<Cube*> MazeLoader::loadMazeFromFile(std::string fileName) {
    this->mazeFile = new std::ifstream(fileName);
    loadMaze();
    this->mazeFile->close();
    return this->mazeCubes;
}

void MazeLoader::loadMaze() {
    if (this->mazeFile->is_open()) {
        std::string line;
        while (this->mazeFile->good()) {
            std::getline(*(this->mazeFile), line);
            loadLine(line);
        }
    }
    else {
        std::cout << "Couldn't open file" << std::endl;
    }
}

void MazeLoader::loadLine(const std::string& line) {
    for (const char& el : line) {
        if (WALLCHAR == el) {
            Cube* c = new Cube(glm::vec3(this->colOffset, 0.0f, this->rowOffset));
            addCube(c);
        }
        else if (EMPTYCHAR == el) {}
        this->colOffset++;
    }
    this->colOffset = 0.0f;
    this->rowOffset++;
}

void MazeLoader::addCube(Cube* cube) {
    this->mazeCubes.push_back(cube);
}
