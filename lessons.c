#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100

float koefficient(char dgt_massive[], int l, int r);

int main() {
    double x1, x2; //корни уравнения
    double discr; //дискриминант
    char symb; // текущий символ
    float a, b, c; //коэффициенты уравнения
    char massive[MAXSIZE];
    int l, size;
    l = size = 0;
    a = b = c = 0;
    // Введите квадратное уравнение вида ax^2+bx+c
    while ((symb = getchar()) != '\n' && size < MAXSIZE - 1) {
        massive[size++] = symb;
    }
    massive[size] = '\0';
    for (int r = 0; r < size; r++) {
        if (massive[r] == 'x') {
            switch (massive[r + 1]) {
                    case '^': { //если стоит знак степени, значит это коэфф a
                        a = koefficient(massive, l, r - 1);
                        r += 3;
                        l = r;
                        break;
                    }
                    default: { //степени нет, значит коэфф b
                        b = koefficient(massive, l, r - 1);
                        r += 1;
                        l = r;
                        break;
                    }
            }
        }
        else
            switch(massive[r + 1]){
                case '+': case '-': case '\0': {
                    c = koefficient(massive, l, r);
                    r += 1;
                    l = r;
                    break;
                }
                default:
                    break;
            }
    }

    discr = sqrt((b * b - 4 * a * c));

    x1 = (-1 * b - discr) / (2 * a);
    x2 = (-1 * b + discr) / (2 * a);

    if (x1 == x2)
        printf("Корень: %.2f \n", x1);
    else{
        printf("Корень 1: %.2f\n", x1);
        printf("Корень 2: %.2f\n", x2);
    }
    return 0;
}

float koefficient(char dgt_massive[], int l, int r) { //функция получения численного коэффициента из подстроки

    char digits[r - l + 1];
    float nums;
    for (int i = l; i <= r; i++)
        digits[i - l] = dgt_massive[i];
    nums = atof(digits);
    memset(digits, 0, sizeof(digits));
    return nums;
}
