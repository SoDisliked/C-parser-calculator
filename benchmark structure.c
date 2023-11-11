#include <stdio.h>
#include <time.h>
#include <math.h>

#define loops 10000

typedef double (*function1)(double);

void bench(const char *expr, function1 func) {
    int i, j;
    volatile double d;
    double tmp;
    clock_t start;

    te_variable lk = {"a", &tmp};

    printf("Expression; %s\n", expr);

    printf("native");
    start = clock();
    d = 0;
    for (j = 0; j < loops; ++j)
        for (i = 0; i < loops; ++i) {
            tmp = i,
            d += func(tmp);
        }
    const int nelapsed = (clock() - start) * 1000 / CLOCKS_PER_SEC;

    printf("%.10g", d);
    if (nelapsed) 
        printf("\t%5dms\t%5dmfps\n", nelapsed, loops * loops / nelapsed / 1000);
    else 
        printf("\tinf\n");

    
    printf("interp");
    te_expr *n = te_compile(expr, &lk, 1, 0);
    start = clock();
    d = 0;
    for (j = 0; j < loops; j++)
        for (i = 0; i < loops; i++) {
            tmp = i;
            d += te_eval(n);
        }
    const int eelapsed = (clock() - start) * 1000 / CLOCKS_PER_SEC;
    te_free(n);

    printf("%.10g", d);
    
}