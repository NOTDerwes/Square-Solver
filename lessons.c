#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
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

    if (a) {
        discr = (b * b - 4 * a * c);

        if (discr > 0) {
            x1 = (-b - sqrt(discr)) / (2 * a);
            x2 = (-b + sqrt(discr)) / (2 * a);
            printf("Корень 1: %.2f\n", x1);
            printf("Корень 2: %.2f\n", x2);
        }
        else if (discr == 0) {
            x1 = -b / (2 * a);
            printf("Корень: %.2f \n", x1);
        }
        else
            printf("Корни есть, но они мнимые(");
    }
    else {
        if (b) {
            x1 = -c / b;
            printf("Корень: %.2f\n", x1);
        }
        else
        printf("Корней нет(");
    }
    return 0;
}

float koefficient(char dgt_massive[], int l, int r) { //функция получения численного коэффициента из подстроки
    if (r + 1 == l) { //в случае, когда перед х-ом нет коэффициента
        if (isdigit(dgt_massive[l])) //проверка, что это коэфф перед х, а не цифра
            return dgt_massive[l] - '0';
        else
            return 1;
    }
    char digits[r - l + 1];
    float nums;
    for (int i = l; i <= r; i++)
        digits[i - l] = dgt_massive[i];
    nums = atof(digits);
    return nums;
}
