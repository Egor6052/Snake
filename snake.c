#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

void enableRawMode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void disableRawMode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

int main() {
    int X, Y;

    printf("Enter X (rows): \n");
    scanf("%d", &X);
    printf("Enter Y (columns): \n");
    scanf("%d", &Y);

    char array[X][Y];

    int a = X / 2, b = Y / 2;

    enableRawMode();
    system("clear");

    while (1) {
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                if (i == 0 || i == X - 1 || j == 0 || j == Y - 1) {
                    array[i][j] = '#';
                } else {
                    array[i][j] = ' ';
                }
            }
        }

        // голова
        array[a][b] = '@';

        // Оновлення екрану
        system("clear");
        for (int i = 0; i < X; ++i) {
            for (int j = 0; j < Y; ++j) {
                printf("%c", array[i][j]);
            }
            printf("\n");
        }

        // Зчитування
        usleep(100000);
        char S;
        if (read(STDIN_FILENO, &S, 1) == 1) {
            if (S == 'w' && a > 1) a--;
            else if (S == 's' && a < X - 2) a++;
            else if (S == 'a' && b > 1) b--;
            else if (S == 'd' && b < Y - 2) b++;
            else if (S == 'q') break;
        }
    }

    disableRawMode();
    printf("Game Over!\n");
    return 0;
}
