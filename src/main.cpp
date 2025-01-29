#include <iostream>
#include <raylib.h>
#include <chrono>
#include "../lib/Background.h"
#include "../lib/Snake.h"

int main() {
    const int screenWidth = 750;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Attack");
    SetTargetFPS(60);

    Snake snake;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        snake.Draw();

        snake.UpdateSnake();
        snake.SnakeDraw();
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
