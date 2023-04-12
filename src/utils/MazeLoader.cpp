
#include "MazeLoader.h"

MazeLoader::MazeLoader(std::string fileName) {
    this->mazeFile = ifstream(fileName);
}

std::string MazeLoader::loadLine() {
    if (!this->mazeFile.is_open()) {
        std::cout << "File is closed" << std::endl;
        throw ReadingClosedFileException;
    }
    if (!this->mazeFile.good()) {
        std::cout << "All line are read" << std::endl;
        return nullptr;
    }
    std::string ret;
    std::getline(this->mazeFile, ret);
    return ret;
}