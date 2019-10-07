#define PI 3.14159265358979323846
#define E_NUM 2.7182818284590452354

#include <math.h>

typedef double my_float;

my_float my_abs(my_float x) {
    return x < 0 ? -x : x;
}

my_float my_modf(my_float x, my_float m) {
    return x - m * (int)(x/m);
}

my_float my_pow(my_float x, int n) {
    my_float resultado = 1;
    for(int i = 0; i < n; i++) {
        resultado *= x;
    }
    return resultado;
}