#include <iostream>
#include <raylib.h>
#include <chrono>
#include <thread>
#include "../lib/Background.h"
#include "../lib/Snake.h"

int main() {
    const int screenWidth = 750;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Attack");
    SetTargetFPS(60);

    Snake snake;
    Background background;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        
        snake.UpdateSnake();
        // snake.SnakeDraw();

        // Затримка на 50 мілісекунд
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
        background.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
