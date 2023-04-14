#pragma once

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

struct Direction{
    int bit;
    int dx;
    int dy;
    int oppositeBit;
};

class MazeGenerator{
    private:
        std::vector<std::vector<int>> maze;
        int width = 0;
        int height = 0;

        void generateMaze(int cx, int cy);
        std::vector<Direction> getShuffledDirections();
        bool between(int v, int upper);
    public:
        MazeGenerator(int width = 10, int height = 10);
};