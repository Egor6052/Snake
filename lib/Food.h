#pragma once

#include <vector>
#include <raylib.h>
#include "Background.h"

class Food : public Background {
    private:
        int foodRow;
        int foodCol;

        // float calories;
    public:

        Food();
        ~Food();

        int getFoodRow();
        int getFoodCol();

        // float getCalories();
        void FoodGeneration();
};
