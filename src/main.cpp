#include <raylib.h>

int main() {
    // Ініціалізація вікна
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Sprite Animation Example");

    // Завантаження спрайт-листа
    Texture2D spriteSheet = LoadTexture("../sprites/box1.png");

    // Параметри анімації
    const int frameWidth = spriteSheet.width / 2;  // Ширина одного кадру (4 кадри в рядок)
    const int frameHeight = spriteSheet.height;   // Висота кадру (1 рядок)
    const int totalFrames = 2;                    // Загальна кількість кадрів
    float frameTime = 0.1f;                       // Час між кадрами (в секундах)
    float timer = 0.0f;                           // Таймер для перемикання кадрів
    int currentFrame = 0;                         // Поточний кадр

    // Область для відображення
    Rectangle frameRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    Vector2 position = { 400.0f, 225.0f };        // Позиція малювання
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Оновлення таймера і кадру
        timer += GetFrameTime();
        if (timer >= frameTime) {
            timer = 0.0f;
            currentFrame++;
            if (currentFrame >= totalFrames) currentFrame = 0;  // Перехід на перший кадр
            frameRec.x = (float)currentFrame * frameWidth;      // Оновлення області кадру
        }

        // Малювання
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Sprite Animation Example", 10, 10, 20, DARKGRAY);
        DrawTextureRec(spriteSheet, frameRec, position, WHITE); // Малюємо кадр

        EndDrawing();
    }

    // Завершення програми
    UnloadTexture(spriteSheet);
    CloseWindow();

    return 0;
}
