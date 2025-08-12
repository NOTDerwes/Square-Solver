#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define MAXSIZE 100
int flag = 1; //принимает значение -1 для чисел, находящихся в правой части ур-я


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
    // Введите квадратное уравнение
    while ((symb = getchar()) != '\n' && size < MAXSIZE - 1) {
        massive[size++] = symb;
    }
    massive[size] = '\0';
    for (int r = 0; r < size; r++) {
        if (massive[r] == 'x') {
            switch (massive[r + 1]) {
                case '^': { //если стоит знак степени, значит это коэфф a
                    a += koefficient(massive, l, r - 1);
                    r += 3;
                    l = r;
                    break;
                }
                default: { //степени нет, значит коэфф b
                    b += koefficient(massive, l, r - 1);
                    r += 1;
                    l = r;
                    break;
                }
            }
        }
        else
            switch(massive[r + 1]){
                case '+': case '-': case '\0': case '=': {
                    c += koefficient(massive, l, r);
                    r += 1;
                    l = r;
                    break;
                }
                default:
                    break;
            }
        if (massive[l] == '=') {
            flag = -1;
            l++;
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
            printf("Корень: %.2f\n", x1);
        }
        else
            printf("Корни есть, но они мнимые(\n");
    }
    else {
        if (b) {
            x1 = -c / b;
            printf("Корень: %.2f\n", x1);
        }
        else {
            if (c)
                printf("Корней нет(\n");
            else
                printf("Корень: 0\n");
        }
    }
    printf("Коэффициенты приведенного уравнения:\n");
    printf("x^2: %.2f, x^1: %.2f, x^0: %.2f\n", a, b, c);
    return 0;
}

float koefficient(char dgt_massive[], int l, int r) { //функция получения численного коэффициента из подстроки
    if (r <= l) { //в случае, когда перед х-ом нет коэффициента
        if (isdigit(dgt_massive[l])) //проверка, что это коэфф перед х, а не цифра
            return (dgt_massive[l] - '0') * flag;
        else
            return flag;
    }
    char digits[r - l + 1];
    float nums;
    for (int i = l; i <= r; i++)
        digits[i - l] = dgt_massive[i];
    nums = atof(digits);
    return nums * flag;
}
