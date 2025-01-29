#pragma once

#include <vector>
#include <raylib.h>
#include "Background.h"

class Food : public Background {
    private:
        float calories;
    public:

        Food();
        ~Food();
        float getCalories();
        // void SnakeEatFood(int colorFood);
        void FoodGeneration();
};
