#include <stdio.h>

int devider(int a);

int main(void) {
    int a;
    scanf("%d", &a);

    printf("%d", devider(a));

    return 0;
}

int devider(int a) {
    int ost;
    int count;
    if (a < 0) a *= -1;
    for (int i = 1; i <= a; i++) {
        ost = i;
        if (a == i) return i;
        while (ost >= a - i) ost -= a - i;
        if (ost == 0) {
            count = 0;
            for (int j = 2; j <= a - i; j++) {
                ost = a - i;
                while (ost - j >= j) ost -= j;
                if (ost - j == 0) count++;
            }
            if (count == 1) return a - i;
        }
    }
    return 0;
}