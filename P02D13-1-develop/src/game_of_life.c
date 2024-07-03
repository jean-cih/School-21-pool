#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 82
#define HEIGHT 27
#define LIFE 1
#define DEAD 2
#define GENESIS 3
#define NOT 0

void instruction();
int **declaration_matrix();
void first_generation1(int **matrix, char path);
void next_generation(int **matrix);
void render(int **current_generation);
int finding_neighbours(int **matrix, int y, int x);
void closure_field(int **matrix);
void leave_game();
void control(int *speed);
void end_game();

int main(int argc, char **argv) {
    int speed = 200000;
    int **gen_matrix = declaration_matrix();

    first_generation1(gen_matrix, argv[argc - 1][0]);

    initscr();

    while (speed != 0) {
        nodelay(stdscr, true);

        instruction();
        closure_field(gen_matrix);
        render(gen_matrix);
        next_generation(gen_matrix);
        control(&speed);

        usleep(speed);
        clear();
    }
    nodelay(stdscr, false);
    endwin();

    end_game();

    free(gen_matrix);

    return 0;
}
void control(int *speed) {
    char sign;
    sign = getch();
    if (sign == 'Q' || sign == 'q') *speed = 0;
    if (sign == '-' && *speed <= 300000) *speed += 10000;
    if (sign == '=' && *speed >= 20000) *speed -= 10000;
}

void instruction() {
    printf("\033[1;31;40m");
    printw("\t\t\t  WELCOME TO THE GAME OF LIFE\n");
    printw("\t\t\t       Change game speed\n");
    printw("\t     Tap + to increase speed   |");
    printw("   Tap - to decrease speed\n");
    printf("\033[1;34;40m");
}

void end_game() {
    printf("\033[1;31;40m");
    printf("\t\t\tYou have just left the game\n");
}

void leave_game() { printw("\t\t\tQ/q - leave the game\n"); }

int **declaration_matrix() {
    int **matrix = malloc(WIDTH * HEIGHT * sizeof(int) + HEIGHT * sizeof(int *));
    int *p = (int *)(matrix + HEIGHT);
    for (int i = 0; i < HEIGHT; i++) matrix[i] = p + WIDTH * i;

    return matrix;
}

void first_generation1(int **matrix, char path) {
    char x;
    int choose;
    char *paths[] = {"coor1.txt", "coor2.txt", "coor3.txt", "coor4.txt",
                     "coor5.txt", "coor6.txt", "coor7.txt", "coor8.txt"};
    if (path == '1')
        choose = 0;
    else if (path == '2')
        choose = 1;
    else if (path == '3')
        choose = 2;
    else if (path == '4')
        choose = 3;
    else if (path == '5')
        choose = 4;
    else if (path == '6')
        choose = 5;
    else if (path == '7')
        choose = 6;
    else
        choose = 7;

    FILE *file = fopen(paths[choose], "r");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (fscanf(file, "%c", &x) == 1 && x == '1') matrix[i][j] = LIFE;
        }
    }
    fclose(file);
}

int finding_neighbours(int **matrix, int y, int x) {
    int neighbours;
    if (matrix[y][x] == NOT)
        neighbours = 0;
    else
        neighbours = -1;

    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++)
            if (matrix[i][j] == LIFE || matrix[i][j] == DEAD) neighbours++;
    }

    return neighbours;
}

void next_generation(int **matrix) {
    for (int i = 1; i < HEIGHT - 1; i++) {
        for (int j = 1; j < WIDTH - 1; j++) {
            int neighbours = finding_neighbours(matrix, i, j);

            if (matrix[i][j] == NOT && neighbours == 3) matrix[i][j] = GENESIS;

            if (matrix[i][j] == LIFE && (neighbours < 2 || neighbours > 3)) matrix[i][j] = DEAD;
        }
    }
}

void render(int **current_generation) {
    printf("\033[1;32;40m");

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (current_generation[i][j] == GENESIS) current_generation[i][j] = LIFE;
            if (current_generation[i][j] == DEAD) current_generation[i][j] = NOT;

            if (i == 0 || i == HEIGHT - 1)
                printw("-");
            else if (j == 0 || j == WIDTH - 1)
                printw("|");
            else if (current_generation[i][j] == LIFE) {
                printw("o");
            } else
                printw(" ");
        }
        printw("\n");
    }

    leave_game();

    refresh();
}

void closure_field(int **matrix) {
    for (int j = 0; j < WIDTH; j++) {
        matrix[0][j] = matrix[HEIGHT - 2][j];
        matrix[HEIGHT - 1][j] = matrix[1][j];
    }

    for (int i = 0; i < HEIGHT; i++) {
        matrix[i][0] = matrix[i][WIDTH - 2];
        matrix[i][WIDTH - 1] = matrix[i][1];
    }

    matrix[0][0] = matrix[HEIGHT - 2][WIDTH - 2];
    matrix[HEIGHT - 1][WIDTH - 1] = matrix[1][1];
    matrix[HEIGHT - 1][0] = matrix[1][WIDTH - 1];
    matrix[0][WIDTH - 1] = matrix[HEIGHT - 1][1];
}
