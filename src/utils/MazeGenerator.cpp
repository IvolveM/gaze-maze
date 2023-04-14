#include "MazeGenerator.h"

MazeGenerator::MazeGenerator(int width, int height)
    :   maze{std::vector(width, std::vector(height, 0))},
        width{width},
        height{height}
{
    generateMaze(0, 0);
    for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) { // north 
            std::cout << (((maze[j][i] & 1) == 0) ? "##" : "# ");
        }
        std::cout << "#" << std::endl;
        for (int j = 0; j < height; j++) { // west
            std::cout << (((maze[j][i] & 8) == 0) ? "# " : "  ");
        }
        std::cout << "#" << std::endl;
    }
    for (int j = 0; j < width; j++) {
        std::cout << "##";
    }
    std::cout << "#" << std::endl;
}    

void MazeGenerator::generateMaze(int cx, int cy)
{
    std::vector<Direction> directions = getShuffledDirections();
    for (Direction direction : directions){
        int nx = cx + direction.dx;
        int ny = cy + direction.dy;
        if (between(nx, width) && between(ny, height) && (maze[nx][ny] == 0)){
            maze[cx][cy] |= direction.bit;
            maze[nx][ny] |= direction.oppositeBit;
            generateMaze(nx, ny);
        }
    }
}

std::vector<Direction> MazeGenerator::getShuffledDirections()
{
    std::vector<Direction> directions = {
        Direction{1, 0, -1, 2}, // North
        Direction{2, 0, 1, 1}, // South
        Direction{4, 1, 0, 8}, // East
        Direction{8, -1, 0, 4} // West
    };
    std::random_shuffle(std::begin(directions), std::end(directions));
    return directions;
}

bool MazeGenerator::between(int v, int upper){
    return (v >= 0) && (v < upper);
}