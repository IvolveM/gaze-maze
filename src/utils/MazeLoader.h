
#include <iostream>
#include <fstream> 
#include <string>

class MazeLoader {
    public:
        MazeLoader(std::string fileName);
        ~MazeLoader();

        String loadLine();

    private:
        std::ifstream mazeFile;
}

class ReadingClosedFileException : public std::exception {
    public:
        ReadingClosedFileException(std::string name){
            this->name = name;
        };

        const char * what () const throw () {
            return strcat("You tried to read a line from a file that hasn't been opened.");
        }
};
