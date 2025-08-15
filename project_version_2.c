#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#define MAXSIZE 100
int flag = 1;

void input(char input_massive[]);
void get_koeff(char input_massive[], float koefs[]);
float str_to_num(char dgt_massive[], int l, int r);
void solve_equasion(float koeffs[], double x[]);
void print_ans(double x[]);


void input(char input_massive[]) { //функция ввода уравнения с форматированием
    char symb = '0';
    int size = 0;
    printf("Введите квадратное уравнение без пробелов:\n");
    while ((symb = getchar()) != '\n' && size < MAXSIZE) {
        if (symb == 'x') {
            if (size == 0 || input_massive[size - 1] == '+' ||
            input_massive[size - 1] == '-' || input_massive[size - 1] == '=') {
                input_massive[size] = '1';
                size++;
            }
        }
        input_massive[size] = symb;
        size++;
    }
    input_massive[size] = '\0';
}


void get_koeff(char input_massive[], float koefs[]) { //функция сканирует входную строку и считает коэффициенты полинома
    int l = 0;
    int size = strlen(input_massive);
    for (int r = 0; r < size; r++) {
        l = r;
        while (input_massive[r + 1] != '+' && input_massive[r + 1] != '-' &&
        input_massive[r + 1] != '=' && input_massive[r + 1] != '\0')
            r++;


        if (input_massive[r] == 'x')
            koefs[1] += str_to_num(input_massive, l, r - 1);

        else {
            if (input_massive[r - 1] == '^') {
                koefs[input_massive[r] - '0'] += str_to_num(input_massive, l, r - 3);
            }
            else
                koefs[0] += str_to_num(input_massive, l, r);
        }
        if (input_massive[r + 1] == '=') {
            r++;
            flag = -1; //переносим все значения из левой части ур-я в правую с коэфф -1
        }
    }
}


float str_to_num(char input_massive[], int l, int r) { //функция получения численного коэффициента из подстроки
    char digits[MAXSIZE] = {};
    float nums = 0;
    for (int i = l; i <= r; i++){
        digits[i - l] = input_massive[i];
    }
    nums = atof(digits);
    return nums * flag;
}


void solve_equasion(float koefs[], double x[]) { //решение квадратного уравнения
    float a = koefs[2], b = koefs[1], c = koefs[0];

    if (a == 0) {
        if (b != 0)
            x[0] = -c / b;
    }

    else {
        double discriminant = b * b - 4 * a * c;
        if (discriminant > 0) {
            x[0] = (-b - sqrt(discriminant)) / (2 * a);
            x[1] = (-b + sqrt(discriminant)) / (2 * a);
        }
        else if (discriminant == 0)
            x[0] = -b / (2 * a);
    }
}


void print_ans(double x[]) { //вывод решений уравнения
    if (x[1] == 0xFEEE) {
        if (x[0] == 0xFEEE)
            printf("КОРНЕЙ НЕТ!!!\n");
        else
            printf("Корень равен %.3f\n", x[0]);
    }
    else
        printf("Меньший корень равен %.3f\n Больший корень равен %.3f\n", x[0], x[1]);
}


int main() {
    char massive[MAXSIZE] = {};
    float koefs[3] = {0};
    double x[2] = {0xFEEE, 0xFEEE};
    input(massive);
    get_koeff(massive, koefs);
    solve_equasion(koefs, x);
    print_ans(x);
    return 0;
}
