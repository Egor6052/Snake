#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    int X = 10, Y = 20;
    char array[X][Y];

    int a = X / 2, b = Y / 2;

    while (1) {
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                array[i][j] = (i == 0 || i == X - 1 || j == 0 || j == Y - 1) ? '#' : ' ';
            }
        }

        array[a][b] = '@';

        system("cls"); // Очищення екрана
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                printf("%c", array[i][j]);
            }
            printf("\n");
        }

        Sleep(100); // Затримка в 100 мс
        if (GetAsyncKeyState(VK_UP) & 0x8000 && a > 1) a--;
        if (GetAsyncKeyState(VK_DOWN) & 0x8000 && a < X - 2) a++;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000 && b > 1) b--;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && b < Y - 2) b++;
        if (GetAsyncKeyState('Q') & 0x8000) break;
    }

    printf("Game Over!\n");
    return 0;
}
