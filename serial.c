#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>   	// for clock_t, clock(), CLOCKS_PER_SEC

int main(int argc, char* argv[]) {
    long n;
    double a, r;
    double sum = 0;
	double time_spent = 0.0;

	clock_t begin = clock();

    // ./main <a> <r> <n>
    a = strtol(argv[1], NULL, 10);
    r = strtol(argv[2], NULL, 10);
    n = strtol(argv[3], NULL, 10);

    for (int i = 0; i < n; i++) {
        sum += a * pow(r, i);
    }
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("a = %.2lf, r = %.2lf, n = %ld\n", a, r, n);
    printf("Sn = %.2lf\n", sum);
    printf("Time elapsed is %f seconds\n", time_spent);

    return 0;
}