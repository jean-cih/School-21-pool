#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

#define HEIGHT 25
#define WIDTH 80

int x_left_plate = 12;
int x_right_plate = 12;
int x_ball = HEIGHT / 2 - 1;
int y_ball = WIDTH / 2 + 1;
int x_ball_step = 1;
int y_ball_step = 1;
int score_right = 0;
int score_left = 0;

void drawing_map();
void movement_ball();
void control_plates(char sign);
void drawing_winner();
void instruction();

int main() {
    int define_winner = 0;

    initscr();

    while (!define_winner) {
        nodelay(stdscr, true);
        instruction();
        movement_ball();
        drawing_map();
        char sign;
        sign = getch();
        control_plates(sign);

        define_winner = (score_right == 21 || score_left == 21) ? 1 : 0;

        if (sign == 'q' || sign == 'Q') {
            break;
        }

        usleep(70000);
        clear();
    }
    nodelay(stdscr, true);
    clear();
    endwin();
    printf("\033[1;33;40m");
    drawing_winner();

    return 0;
}

void drawing_map() {
    printf("\033[1;32;40m");
    for (int i = 0; i <= HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if ((i == 0 || i == HEIGHT)) {
                printw("-");
            } else if (i == x_ball && j == y_ball) {
                printw("o");
            } else if (j == WIDTH / 2 - 1 && i == 3 && score_left >= 10) {
                printw("|");
            } else if (j == WIDTH / 2 && i == 3 && score_left < 10) {
                printw("|");
            } else if (j == WIDTH / 2 && i != 3) {
                printw("|");
            } else if (i == 3 && j == 35 && score_left < 10) {
                printw("%d", score_left);
            } else if (i == 3 && j == 33 && score_left >= 10) {
                printw("%d", score_left);
            } else if (i == 3 && j == 45) {
                printw("%d", score_right);
            } else if (j == 0) {
                if (i == x_left_plate - 1 || i == x_left_plate || i == x_left_plate + 1)
                    printw("]");
                else
                    printw(" ");
            } else if (j == WIDTH) {
                if (i == x_right_plate - 1 || i == x_right_plate || i == x_right_plate + 1)
                    printw("[");
                else
                    printw(" ");
            } else
                printw(" ");
        }
        printw("\n");
    }
    refresh();
}

void movement_ball() {
    x_ball += x_ball_step;
    y_ball += y_ball_step;

    if (x_ball == 1 || x_ball == HEIGHT - 1) x_ball_step = -x_ball_step;
    if ((y_ball == WIDTH - 1) &&
        (x_ball == x_right_plate - 1 || x_ball == x_right_plate || x_ball == x_right_plate + 1)) {
        y_ball_step = -y_ball_step;
    }
    if (y_ball == WIDTH) {
        score_left++;
        x_ball = HEIGHT / 2 + 1;
        y_ball = WIDTH / 2 - 1;
        x_ball_step = -x_ball_step;
        y_ball_step = -y_ball_step;
    }
    if ((y_ball == 1) &&
        (x_ball == x_left_plate - 1 || x_ball == x_left_plate || x_ball == x_left_plate + 1)) {
        y_ball_step = -y_ball_step;
    }
    if (y_ball == 0) {
        score_right++;
        x_ball = HEIGHT / 2 + 1;
        y_ball = WIDTH / 2 + 1;
        x_ball_step = -x_ball_step;
        y_ball_step = -y_ball_step;
    }
}

void control_plates(char sign) {
    if ((sign == 'Z' || sign == 'z') && x_left_plate != 23) x_left_plate++;
    if ((sign == 'A' || sign == 'a') && x_left_plate != 2) x_left_plate--;
    if ((sign == 'M' || sign == 'm') && x_right_plate != 23) x_right_plate++;
    if ((sign == 'K' || sign == 'k') && x_right_plate != 2) x_right_plate--;
}

void drawing_winner() {
    if (score_right == 21)
        printf("\n\n                           The Winner is The right man\n\n\n");
    else if (score_left == 21)
        printf("\n\n                            The Winner is The left man\n\n\n");
}

void instruction() {
    printw("\n                                   Instruction\n");
    printw("                              Left - A/Z Right - K/M\n");
    printw("                             Tap Q/q to leave the game\n");
    printw("                                    Good Luck\n");
}