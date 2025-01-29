#include <iostream>
#include <raylib.h>
#include <chrono>
#include "../lib/Background.h"
#include "../lib/Snake.h"

int main() {
    const int screenWidth = 600;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "˚｡⋆Snake⋆｡˚");
    SetTargetFPS(60);

    Snake snake;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        // DrawText("Money: " + snake.getMoney(), 190, 200, 20, LIGHTGRAY);

        snake.Draw();

        snake.FoodGeneration();

        snake.UpdateSnake();
        snake.SnakeDraw();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
