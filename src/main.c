/*!
 * @file main.c
 * @brief Главный модуль программы решения квадратных уравнений
 * @author NOTDerwes
 * @date 25.08.2025
 * @version Beta
 *
 * Программа для решения квадратных уравнений вида @f$ ax^2 + bx + c = 0 @f$
 * с обработкой пользовательского ввода и выводом результатов.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "double_operations.h"
#include "solve_equation.h"
#include "unit_tests.h"
#include "myassert.h"

#define INPUTSIZE 20 ///< Размер буфера для ввода
#define YES_ANSWER "Да" ///< Строка подтверждения продолжения

/**
 * @brief Ввод коэффициентов уравнения
 *
 * Запрашивает у пользователя ввод коэффициентов a, b, c
 * для квадратного уравнения @f$ ax^2 + bx + c = 0 @f$
 *
 * @param[out] equation_coeffs Указатель на структуру для коэффициентов
 *
 * @warning equation_coeffs не должен быть NULL
 * @see input_coeff
 */
void input(Coeffs *equation_coeffs);

/**
 * @brief Ввод отдельного коэффициента
 *
 * Запрашивает ввод конкретного коэффициента с проверкой
 * корректности ввода и обработкой ошибок
 *
 * @param[in] curr_coeff Обозначение коэффициента ('a', 'b' или 'c')
 * @param[out] inputing_coeff Указатель для сохранения коэффициента
 *
 * @warning inputing_coeff не должен быть NULL
 * @note Повторяет запрос при некорректном вводе
 * @see letters_left
 * @see clean_buffer
 * @see is_double
 */
void input_coeff(char curr_coeff, double *inputing_coeff);

/**
 * @brief Проверка наличия символов в буфере ввода
 *
 * Проверяет, остались ли символы в буфере ввода после scanf
 *
 * @return 1 если в буфере есть символы
 * @return 0 если буфер пуст
 *
 * @note Используется для проверки корректности ввода чисел
 */
int letters_left();

/**
 * @brief Очистка буфера ввода
 *
 * Очищает стандартный поток ввода до символа новой строки
 *
 * @note Используется после некорректного ввода
 */
void clean_buffer();

/**
 * @brief Запрос на продолжение работы
 *
 * Запрашивает у пользователя подтверждение продолжения работы программы
 *
 * @return true если пользователь ввел "Да"
 * @return false если пользователь ввел что-то другое
 *
 * @see YES_ANSWER
 */
bool continue_enter();

/**
 * @brief Вывод результатов решения уравнения
 *
 * Выводит корни уравнения в зависимости от их количества
 * и типа (действительные, комплексные, специальные случаи)
 *
 * @param[in] equation_roots Структура с результатами решения
 *
 * @warning equation_roots.amount не должен быть UndigistedRoot
 * @note Форматирует вывод для разных случаев количества корней
 */
void print_ans(Roots equation_roots);

void input(Coeffs *equation_coeffs)
{
    MYASSERT(equation_coeffs, "NULL pointer on equation_coeffs");

    printf("Введите коэффициенты квадратного трёхчлена.\n");
    input_coeff('a', &equation_coeffs->a);
    input_coeff('b', &equation_coeffs->b);
    input_coeff('c', &equation_coeffs->c);
}

void input_coeff(char curr_coeff, double *inputing_coeff)
{
    MYASSERT(inputing_coeff, "NULL pointer on inputing_coeff");

    bool flag_retry = true;
    do {
        printf("Введите коэффициент %c: ", curr_coeff);
        int scan_result = scanf("%lf", inputing_coeff);

        if (scan_result != 1 || letters_left() || !is_double(*inputing_coeff)) {
            printf("Коэффициент %c введен в неправильном формате! Попробуйте ещё раз\n", curr_coeff);
            clean_buffer();
        } else {
            flag_retry = false;
        }
    } while(flag_retry);
}

int letters_left()
{
    if (getchar() != '\n')
        return 1;
    return 0;
}

void clean_buffer()
{
    while (getchar() != '\n') {}
}

bool continue_enter()
{
    char confirmation[INPUTSIZE] = "";
    printf("Введите \"Да\", если хотите продолжить:\n");
    scanf("%5s", confirmation);
    clean_buffer();

    if (strncmp(confirmation, YES_ANSWER, sizeof(YES_ANSWER)) != 0) {
        return false;
    }
    return true;
}

void print_ans(Roots equation_roots)
{
    double x1 = equation_roots.x1;
    double x2 = equation_roots.x2;
    int roots_amount = equation_roots.amount;

    MYASSERT(roots_amount != UndigistedRoot, "Roots not calculated");
    MYASSERT((!isnan(x1) || roots_amount < OneRoot), "Invalid root state");

    switch (roots_amount) {
        case ZeroRoots:
            printf("КОРНЕЙ НЕТ!!!\n\n");
            break;
        case UndefinedRoot:
            printf("Корень не определен\n\n");
            break;
        case OneRoot:
            printf("Корень равен %g\n\n", x1);
            break;
        case TwoRoots:
            printf("Меньший корень равен %g\nБольший корень равен %g\n\n", x1, x2);
            break;
        default:
            printf("Неизвестное количество корней: %d\n\n", roots_amount);
    }
}

/**
 * @brief Главная функция программы
 *
 * Основная логика программы:
 * 1. Запуск модульных тестов
 * 2. Инициализация структур данных
 * 3. Основной цикл работы с пользователем
 * 4. Обработка ввода и вывод результатов
 *
 * @return 0 при успешном завершении
 *
 * @note Бесконечный цикл с возможностью выхода по команде пользователя
 * @see test_solve_equation
 * @see reset_structs
 * @see input
 * @see solve_square_equation
 * @see print_ans
 * @see continue_enter
 */
int main(int argc, char *argv[]) {
    //Запуск тестов
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--test") == 0) {
            test_solve_equation("./tests/test_input.txt");
            return 0;
        }
    }

    // Инициализация структур данных
    Coeffs equation_coeffs = {.a = NAN, .b = NAN, .c = NAN};
    Roots equation_roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};

    // Основной цикл работы программы
    do {
        // Сброс структур перед новым вычислением
        reset_structs(&equation_coeffs, &equation_roots);

        // Ввод коэффициентов уравнения
        input(&equation_coeffs);

        // Решение квадратного уравнения
        solve_square_equation(equation_coeffs, &equation_roots);

        // Вывод результатов
        print_ans(equation_roots);

    } while (continue_enter()); // Проверка желания продолжить

    return 0;
}
