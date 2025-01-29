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

    this->snakeSize = 1; // Початковий розмір змійки - 1 клітинка
    this->body.push_back({snakeRow, snakeCol}); // Додаємо початкову позицію змійки
}

Snake::~Snake(){    }

void Snake::setMoney(){
    this->money = getCalories() / 0.5f;
}
void Snake::snakeGrowth(){
    this->snakeSize = getCalories();
}

void Snake::SnakeEatFood(int foodValue) {
    calories += foodValue;
    if (calories >= growthThreshold) {
        SnakeSegment newSegment = {snakeRow, snakeCol};
        body.insert(body.begin(), newSegment);
        calories = 0;
        snakeSize++;
    }
}

void Snake::UpdateSnake() {
    // Читаємо натискання WASD і змінюємо напрямок руху
    if (IsKeyPressed(KEY_W) && dirRow == 0) {
        dirRow = -1; 
        dirCol = 0;
    }
    if (IsKeyPressed(KEY_S) && dirRow == 0) {
        dirRow = 1;
        dirCol = 0;
    }
    if (IsKeyPressed(KEY_A) && dirCol == 0) {
        dirRow = 0;
        dirCol = -1;
    }
    if (IsKeyPressed(KEY_D) && dirCol == 0) {
        dirRow = 0;
        dirCol = 1; 
    }

    // Оновлюємо позицію змійки
    snakeRow += dirRow;
    snakeCol += dirCol;

    // Перевірка на вихід за межі поля (телепортація на іншу сторону)
    if (snakeRow < 0) snakeRow = numRows - 1;
    if (snakeRow >= numRows) snakeRow = 0;
    if (snakeCol < 0) snakeCol = numCols - 1;
    if (snakeCol >= numCols) snakeCol = 0;

     // Оновлення тіла змійки
    for (int i = body.size() - 1; i > 0; --i) {
        body[i] = body[i - 1];
    }
    body[0] = {snakeRow, snakeCol};

    SnakeClear();
}

void Snake::SnakeDraw() {
    for (const SnakeSegment& segment : body) {
        grid[segment.row][segment.col] = 4;
    }
    // Затримка після малювання всіх сегментів
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

void Snake::SnakeClear() {
    if (body.size() > snakeSize) {
        body.pop_back();
        std::cout << "Removed tail segment. New body size: " << body.size() << std::endl;
    }
}
