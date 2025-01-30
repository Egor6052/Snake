#include <iostream>
#include <random>
#include "../../lib/Food.h"

Food::Food(){
    this->foodRow = 0;
    this->foodCol = 0;
    // this->calories = 0.0f;
}
Food::~Food(){  }

// float Food::getCalories(){
//     return this->calories;
// }

void Food::FoodGeneration() {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_int_distribution<int> rowDistribution(0, getNumRows() - 1);
    std::uniform_int_distribution<int> colDistribution(0, getNumCols() - 1);

    int randomRow, randomCol;
    do {
        randomRow = rowDistribution(generator);
        randomCol = colDistribution(generator);
    } while (grid[randomRow][randomCol] == 4); // Перевіряємо, що їжа не з'являється на змійці

    std::uniform_int_distribution<int> rand(1, 3); // Вибираємо випадковий колір їжі (від 1 до 8)
    int random = rand(generator);

    grid[randomRow][randomCol] = random;

        this->foodRow = randomRow;
        this->foodCol = randomCol;
}

int Food::getFoodRow(){
    return this->foodRow;
}
int Food::getFoodCol(){
    return this->foodCol;
}

// void Food::SnakeEatFood(int colorFood){
//     FoodGeneration();
//     if (colorFood == 1){
//         calories++;
//     } else if (colorFood == 2){
//         calories += 2;
//     } else if (colorFood == 3){
//         calories += 3;
//     } else if (colorFood == 4){
//         calories += 4;
//     } else if (colorFood == 5){
//         calories += 1;
//     } else if (colorFood == 6){
//         calories += 1;
//     } else if (colorFood == 7){
//         calories += 1;
//     } else if (colorFood == 8){
//         calories += 1;
//     }
// }
