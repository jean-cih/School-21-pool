#include <math.h>
#include <stdio.h>

void encoder();
void decoder();

int main(int argc, char **argv) {
    if (argc == 2){
        if (argv[argc - 1][0] == '0')
            encoder();
        else if (argv[argc - 1][0] == '1')
            decoder();
        else
            printf("n/a");
    }
    else
        printf("n/a");

    return 0;
}

void encoder() {
    char letter;
    while (1) {
        if(scanf("%c", &letter)){
            printf("%X ", letter);
            if(getchar() == '\n') break;
        }
        else{
            printf("n/a");
            break;
        }
    }
}

void decoder() {
    char code;
    while (1) {
        if(scanf("%X", &code)){
            printf("%c ", code);
            if(getchar() == '\n') break;
        }
        else{
            printf("n/a");
            break;
        }
    }
}