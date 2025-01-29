#include <iostream>
#include "../../lib/Background.h"


Background::Background(){
    this->numRows = 20;
    this->numCols = 25;
    this->cellSize = 30;
    Initialize();

    colors = GetCellColors();
}
Background::~Background(){}

void Background::Print(){
    for (int row = 0; row < numRows; row ++){
        for (int column = 0; column < numCols; column++){
            std::cout << grid[row][column] << " ";
        }
        std::cout << std::endl;

    }
}

void Background::Initialize(){
    for (int row = 0; row < numRows; row ++){

        for (int column = 0; column < numCols; column ++){
            grid[row][column] = 0;
        }
    }
}


std::vector<Color> Background::GetCellColors() {
    Color darkGray = {26, 31, 40, 255};
    Color green = {34, 139, 34, 255};
    Color red = {220, 20, 60, 255};
    Color orange = {255, 140, 0, 255};
    Color yellow = {255, 255, 0, 255};
    Color purple = {128, 0, 128, 255};
    Color cyan = {0, 255, 255, 255};
    Color blue = {0, 0, 255, 255};

    return {darkGray, green, red, orange, yellow, purple, cyan, blue};
}

void Background::Drow(){
    for (int row = 0; row < numRows; row ++){
        for (int column = 0; column < numCols; column ++){
            int cellValue = grid[row][column];
            // DrawRectangle(x, y, w, h, color);
            DrawRectangle(column * cellSize + 1, row * cellSize + 1, cellSize - 1, cellSize -1, colors[cellValue]);
        }
    }
}


