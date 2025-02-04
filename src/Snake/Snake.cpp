#include <iostream>
#include <random>
#include <thread>
#include "../../lib/Snake.h"


Snake::Snake() {
    this->numRows = 20;
    this->numCols = 20;

    this->money = 0.0f;
    this->calories = 0;
    this->growthThreshold = 10;

    this->snakeRow = numRows / 2;
    this->snakeCol = numCols / 2;
    this->dirRow = 0;
    this->dirCol = 1;

    this->snakeSize = 3;
    // Додаємо початкову позицію змійки
    this->body.push_back({snakeRow, snakeCol});
    
    this->SnakeIsDead = false;
    
    FoodGeneration();

}

Snake::~Snake(){    
    UnloadTexture(snakeTexture);
    UnloadTexture(foodTexture);
}

void Snake::setMoney(int valueMoney){
    this->money = static_cast<float>(valueMoney);
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
        grid[getFoodRow()][getFoodCol()] = 7;
        calories += 1;
        setMoney(calories);
        // std::cout << "Calories: " << calories << std::endl;

        // Збільшуємо розмір змії відразу після їжі
        snakeSize++;
        // std::cout << "Розмір: " << snakeSize << std::endl;

        FoodGeneration();
    }
}



void Snake::UpdateSnake() {
    // Оновлення напрямку
    if (IsKeyPressed(KEY_W) && dirRow == 0) { dirRow = -1; dirCol = 0; }
    if (IsKeyPressed(KEY_S) && dirRow == 0) { dirRow = 1; dirCol = 0; }
    if (IsKeyPressed(KEY_A) && dirCol == 0) { dirRow = 0; dirCol = -1; }
    if (IsKeyPressed(KEY_D) && dirCol == 0) { dirRow = 0; dirCol = 1; }

    if (IsKeyPressed(KEY_UP) && dirRow == 0) { dirRow = -1; dirCol = 0; }
    if (IsKeyPressed(KEY_DOWN) && dirRow == 0) { dirRow = 1; dirCol = 0; }
    if (IsKeyPressed(KEY_LEFT) && dirCol == 0) { dirRow = 0; dirCol = -1; }
    if (IsKeyPressed(KEY_RIGHT) && dirCol == 0) { dirRow = 0; dirCol = 1; }

    // Оновлення позиції голови
    int newRow = snakeRow + dirRow;
    int newCol = snakeCol + dirCol;

    // Телепортація через межі
    if (newRow < 0) newRow = numRows - 1;
    if (newRow >= numRows) newRow = 0;
    if (newCol < 0) newCol = numCols - 1;
    if (newCol >= numCols) newCol = 0;


    CrashedIntoSnake(newRow, newCol);
    SnakeEatFood();

    // Додаємо нову голову
    body.insert(body.begin(), {newRow, newCol});

    // Видаляємо хвіст, якщо довжина перевищує snakeSize
    if (body.size() > snakeSize) {
    SnakeSegment tail = body.back(); // Беремо останній елемент змійки (хвіст)
    body.pop_back();

    // Очищуємо клітинку, де був хвіст
    grid[tail.row][tail.col] = 6;
}

    // Оновлюємо позицію голови
    snakeRow = newRow;
    snakeCol = newCol;
}


void Snake::CrashedIntoSnake(int valueRow, int valueCol){
     // Перевірка на зіткнення з собою
    for (const auto& segment : body) {
        if (segment.row == valueRow && segment.col == valueCol) {
            std::cout << "Game Over! Snake collided with itself." << std::endl;
            SnakeIsDead = true;
        }
    }
}

void Snake::Reset() {
    this->snakeRow = numRows / 2;
    this->snakeCol = numCols / 2;
    this->dirRow = 0;
    this->dirCol = 1;

    this->snakeSize = 3;
    this->calories = 0;
    this->money = 0.0f;
    this->SnakeIsDead = false;
    this->body.clear();
    this->body.push_back({snakeRow, snakeCol});

    FoodGeneration();
}


void Snake::SnakeClear() {
    std::cout << "Body size before clearing: " << body.size() << ", Snake size: " << snakeSize << std::endl;
    if (body.size() > snakeSize) {
        body.pop_back();
        std::cout << "Removed tail segment. New body size: " << body.size() << std::endl;
    }
}



void Snake::SnakeDraw() {
    DrawFood(foodTexture);

    for (const SnakeSegment& segment : body) {

        DrawTexture(snakeTexture, segment.col * 30, segment.row * 30, WHITE);
        grid[segment.row][segment.col] = 7;
    }
    // Затримка після малювання всіх сегментів
    std::this_thread::sleep_for(std::chrono::milliseconds(80));
}



// Затримка після малювання всіх сегментів
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
// void Snake::SnakeDraw() {
//     for (const SnakeSegment& segment : body) {
//         grid[segment.row][segment.col] = 4;
//     }
//     // Затримка після малювання всіх сегментів
//     std::this_thread::sleep_for(std::chrono::milliseconds(100));
// }


