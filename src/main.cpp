#include <iostream>
#include <raylib.h>
#include <chrono>
#include "../lib/Background.h"
#include "../lib/Snake.h"

int main() {
    const int screenWidth = 600;
    const int screenHeight = 650;

    InitWindow(screenWidth, screenHeight, "˚｡⋆Snake⋆｡˚");
    SetTargetFPS(60);
    Color color = {40, 50, 65, 255};

    Snake snake;
    Texture2D snakeTexture = LoadTexture("../assets/SnakeBlock1.png");
    Texture2D foodTexture = LoadTexture("../assets/Apple.png");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(color);
        
        // Виведення тексту внизу екрану
        DrawText(("Your score: " + std::to_string(snake.getMoney())).c_str(), 10, screenHeight - 30, 20, LIGHTGRAY);

        snake.Draw();

        // snake.FoodGeneration();

        snake.UpdateSnake();
        snake.SnakeDraw(snakeTexture);
        snake.DrawFood(foodTexture);

        EndDrawing();
    }

    UnloadTexture(snakeTexture);
    UnloadTexture(foodTexture); 

    CloseWindow();
    return 0;
}
