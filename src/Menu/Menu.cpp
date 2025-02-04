#include <raylib.h>
#include <iostream>
#include "../../lib/Menu.h"

Menu::Menu() {
    screenHeight = 650;
    screenWidth = 600;

    isInMenu = true;
    isPaused = false;

    this->Massage = "";
}

Menu::~Menu() {}

void Menu::ResetGame() {
    snake.Reset();
    setMessage("");
    isPaused = false;
}

// Функція для відображення екрану меню
void Menu::ShowMenu() {
    Color buttonColor = {100, 100, 255, 255};
    Color buttonHoverColor = {120, 120, 255, 255};
    
    Vector2 buttonPosition = {(float)(screenWidth / 2 - 100), (float)(screenHeight / 2 - 30)};
    Vector2 buttonSize = {200, 50};

    if (getMessage() != ""){
        DrawText((getMessage() + "\n\nYour score: " + std::to_string(snake.getMoney())).c_str(), screenWidth - 400, screenHeight - 450, 20, LIGHTGRAY);
    }
    
    // Кнопка для початку гри
    if (CheckCollisionPointRec(GetMousePosition(), {buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y})) {
        buttonColor = buttonHoverColor;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ResetGame(); // Скидаємо гру перед початком
            isInMenu = false;
            Start();
        }
    }
    DrawRectangle(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y, buttonColor);
    DrawText("Start Game", buttonPosition.x + 50, buttonPosition.y + 15, 20, LIGHTGRAY);

    // Кнопка для виходу
    buttonPosition.y += 60;
    if (CheckCollisionPointRec(GetMousePosition(), {buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y})) {
        buttonColor = buttonHoverColor;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Exit();
        }
    }
    DrawRectangle(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y, buttonColor);
    DrawText("Exit", buttonPosition.x + 85, buttonPosition.y + 15, 20, LIGHTGRAY);
}

void Menu::setMessage(std::string valueMessage){
    this->Massage = valueMessage;
}

std::string Menu::getMessage(){
    return this->Massage;
}

void Menu::Start() {
    isInMenu = false;

    // Якщо гра на паузі, відображаємо повідомлення про паузу і кнопку "Продовжити"
    if (isPaused) {
        DrawText("Game Paused", screenWidth / 2 - 130, screenHeight / 2 - 50, 40, LIGHTGRAY);

        // Кнопка для продовження гри
        Color buttonColor = {100, 100, 255, 255};
        Color buttonHoverColor = {120, 120, 255, 255};
        Vector2 buttonPosition = {(float)(screenWidth / 2 - 100), (float)(screenHeight / 2 + 30)};
        Vector2 buttonSize = {200, 50};

        if (CheckCollisionPointRec(GetMousePosition(), {buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y})) {
            buttonColor = buttonHoverColor;
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Pause();  // Продовжити гру (скасувати паузу)
            }
        }

        DrawRectangle(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y, buttonColor);
        DrawText("Continue", buttonPosition.x + 50, buttonPosition.y + 15, 20, LIGHTGRAY);

        return;  // Не оновлюємо змію, поки гра на паузі
    }

    // Кнопка для паузи
    Color buttonColor = {100, 100, 255, 255};
    Color buttonHoverColor = {120, 120, 255, 255};
    Vector2 buttonPosition = {(float)(screenWidth - 200), (float)(screenHeight - 60)};
    Vector2 buttonSize = {150, 40};

    if (CheckCollisionPointRec(GetMousePosition(), {buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y})) {
        buttonColor = buttonHoverColor;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            Pause();
        }
    }

    DrawRectangle(buttonPosition.x, buttonPosition.y, buttonSize.x, buttonSize.y, buttonColor);
    DrawText("Pause", buttonPosition.x + 45, buttonPosition.y + 10, 20, LIGHTGRAY);

    // Оновлюємо змію і її малювання
    snake.UpdateSnake();
    snake.SnakeDraw();

    // Перевірка на смерть змії
    if (snake.SnakeIsDead) {
        setMessage("Game Over!");
        isInMenu = true;
    } else {
        DrawText(("Your score: " + std::to_string(snake.getMoney())).c_str(), 10, screenHeight - 30, 20, LIGHTGRAY);
    }
}

void Menu::Pause() {
    isPaused = !isPaused;
}


void Menu::Exit() {
    CloseWindow();
}
