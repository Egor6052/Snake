#ifndef MENU_H
#define MENU_H

#include <raylib.h>
#include "Snake.h"

class Menu {
public:
    Menu();
    ~Menu();

    void ShowMenu();
    std::string Massage;
    void setMessage(std::string valueMessage);
    void ResetGame();
    std::string getMessage();


    void Start();
    void Pause();
    void Exit();

    bool isInMenu;
    bool isPaused;
    Snake snake;

    Snake& getSnake() {
        return snake;
    }


private:
    int screenWidth, screenHeight;
};

#endif
