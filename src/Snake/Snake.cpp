#include <iostream>
#include <random>
#include <thread>
#include "../../lib/Snake.h"

Snake::Snake() {
    this->numRows = 20;
    this->numCols = 20;

    this->money = 0.0f;
    this->calories = 0;
    this->growthThreshold = 10; // Приклад: Зростання при 10 калоріях

    this->snakeRow = numRows / 2;
    this->snakeCol = numCols / 2;
    this->dirRow = 0;
    this->dirCol = 1;

    this->snakeSize = 3; // Початковий розмір змійки - 1 клітинка
    this->body.push_back({snakeRow, snakeCol}); // Додаємо початкову позицію змійки
    FoodGeneration();

}

Snake::~Snake(){    }

void Snake::setMoney(){
    this->money = getCalories() / 0.5f;
}
int Snake::getMoney(){
    return this->money;
}


void Snake::snakeGrowth(){
    this->snakeSize = getCalories();
}

int Snake::getCalories(){
    return this->calories;
}

void Snake::SnakeEatFood() {
    if (snakeRow == getFoodRow() && snakeCol == getFoodCol()) {
        calories += 1; // Додаємо 1 калорію за їжу
        std::cout << "Calories: " << calories << std::endl;

        if (calories >= growthThreshold) {
            snakeSize++;
            calories = 0;
        }

        FoodGeneration();
    }
}


void Snake::UpdateSnake() {
    // Оновлення напрямку
    if (IsKeyPressed(KEY_W) && dirRow == 0) { dirRow = -1; dirCol = 0; }
    if (IsKeyPressed(KEY_S) && dirRow == 0) { dirRow = 1; dirCol = 0; }
    if (IsKeyPressed(KEY_A) && dirCol == 0) { dirRow = 0; dirCol = -1; }
    if (IsKeyPressed(KEY_D) && dirCol == 0) { dirRow = 0; dirCol = 1; }

    // Оновлення позиції голови
    int newRow = snakeRow + dirRow;
    int newCol = snakeCol + dirCol;

    // Телепортація через межі
    if (newRow < 0) newRow = numRows - 1;
    if (newRow >= numRows) newRow = 0;
    if (newCol < 0) newCol = numCols - 1;
    if (newCol >= numCols) newCol = 0;

    // Додаємо нову голову
    body.insert(body.begin(), {newRow, newCol});

    // Видаляємо хвіст, якщо довжина перевищує snakeSize
    SnakeClear();

    // Оновлюємо позицію голови
    snakeRow = newRow;
    snakeCol = newCol;
}


void Snake::SnakeDraw() {
    for (const SnakeSegment& segment : body) {
        grid[segment.row][segment.col] = 4;
    }
    // Затримка після малювання всіх сегментів
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Snake::SnakeClear() {
    std::cout << "Body size before clearing: " << body.size() << ", Snake size: " << snakeSize << std::endl;
    if (body.size() > snakeSize) {
        body.pop_back();
        std::cout << "Removed tail segment. New body size: " << body.size() << std::endl;
    }
}

