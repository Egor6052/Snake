#pragma once

#include <vector>
#include <raylib.h>
#include "Food.h"


struct SnakeSegment {
    int row;
    int col;
};

class Snake : public Food {

    private:
        int numRows;
        int numCols;

        int snakeRow, snakeCol;

        std::size_t snakeSize;
        int dirRow, dirCol;
        
        std::vector<SnakeSegment> body;
        int calories;
        int growthThreshold; 

        float money;

    public:
        Snake();
        ~Snake();

        void setMoney();
        int getMoney();
        void snakeGrowth();

        void SnakeDraw();
        void SnakeClear();

        void UpdateSnake();
        void SnakeEatFood();
        int getCalories();
        // void FoodGeneration();
};
