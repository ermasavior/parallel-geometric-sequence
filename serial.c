#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[]) {
    long n;
    double a, r;
    double sum = 0;

    // ./main <a> <r> <n>
    a = strtol(argv[1], NULL, 10);
    r = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);

    for (int i = 0; i < n; i++) {
        sum += a * pow(r, i);
    }

    printf("a = %.2lf, r = %.2lf, n = %ld\n", a, r, n);
    printf("Sn = %.2lf\n", sum);

    return 0;
}