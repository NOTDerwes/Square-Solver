#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include <ctype.h>
#define MAXSIZE 100 //макс размер входного массива

void input(char input_massive[]);
void get_koeff(char input_massive[], float koefs[]);
float str_to_num(char dgt_massive[], int l, int r, int flag);
void solve_equasion(float koeffs[], double x[]);
void print_ans(double x[]);


void input(char input_massive[]) { //функция ввода уравнения с форматированием
    char symb = '0'; //текущий символ
    int size = 0; //размер входного массива
    printf("Введите квадратное уравнение без пробелов и знаков умножения:\n");
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
    int flag = 1; //коэфф переноса эл-тов из правой части ур-я в левую, равен -1 после знака =
    int size = strlen(input_massive); //размер входного массива
    for (int r = 0; r < size; r++) {
        l = r;
        while (input_massive[r + 1] != '+' && input_massive[r + 1] != '-' &&
        input_massive[r + 1] != '=' && input_massive[r + 1] != '\0')
            r++;
        if (input_massive[r] == 'x')
            koefs[1] += str_to_num(input_massive, l, r - 1, flag);

        else {
            if (input_massive[r - 1] == '^') {
                koefs[input_massive[r] - '0'] += str_to_num(input_massive, l, r - 3, flag);
            }
            else
                koefs[0] += str_to_num(input_massive, l, r, flag);
        }
        if (input_massive[r + 1] == '=') {
            r++;
            flag = -1; //переносим все значения из левой части ур-я в правую с коэфф -1
        }
    }
}


float str_to_num(char input_massive[], int l, int r, int flag) { //функция получения численного коэффициента из подстроки
    char digits[MAXSIZE] = {}; //коэфф, записанный в виде char массива
    float nums = 0; //численная запись коэфф-а
    for (int i = l; i <= r; i++) {
        digits[i - l] = input_massive[i];
    }
    nums = atof(digits);
    return nums * flag;
}


void solve_equasion(float koefs[], double x[]) { //решение квадратного уравнения
    float a = koefs[2], b = koefs[1], c = koefs[0];
    if (a == 0) { //ур-е вида bx+c=0
        if (b == 0) { //ур-е вида c=0
            if (c == 0)
                x[0] = 0xDEADBEEF; //корень неопределен
        }
        else //ур-е вида bx+c=0, где b != 0
            x[0] = -c / b;
    }
    else { //ур-е вида ax^2+bx+c=0,где a != 0
        double discriminant = b * b - 4 * a * c; //дискриминант
        if (discriminant > 0) { //случай с 2мя корнями
            x[0] = (-b - sqrt(discriminant)) / (2 * a); //меньший корень
            x[1] = (-b + sqrt(discriminant)) / (2 * a); //больший корень
        }
        else if (discriminant == 0) //случай с единственным корнем
            x[0] = -b / (2 * a);
    }
    // при получении корня -0 превращаем его в 0
    if (x[0] == 0)
        x[0] = 0;
    if (x[1] == 0)
        x[1] = 0;
}


void print_ans(double x[]) { //вывод решений уравнения
    if (x[1] == 0xFEEE) { //не более одного корня
        if (x[0] == 0xFEEE) //отсутствие корней
            printf("КОРНЕЙ НЕТ!!!\n");
        else if (x[0] == 0xDEADBEEF) //бесконечное кол-во корней
            printf("Корень не определен\n");
        else //1 корень
            printf("Корень равен %.3f\n", x[0]);
    }
    else //2 корня
        printf("Меньший корень равен %.3f\nБольший корень равен %.3f\n", x[0], x[1]);
}


int main() {
    char massive[MAXSIZE] = {}; //строковый массив с исходным уравнением
    float koefs[3] = {0}; //коэффициенты ур-я, по умолчанию все равны 0
    double x[2] = {0xFEEE, 0xFEEE}; //корни ур-я, по умолчанию корней нет
    input(massive); //ввод ур-я
    get_koeff(massive, koefs); //высчитывание коэфф-ов ур-я
    solve_equasion(koefs, x); //решение квадратного ур-я
    print_ans(x); //вывод ответа
    return 0;
}
