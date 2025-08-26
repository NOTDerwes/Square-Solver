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
#include <assert.h>

#include "double_operations.h"
#include "solve_equation.h"
#include "unit_tests.h"
#include "user_interaction.h"
#include "myassert.h"


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
    MYASSERT(0, "Zero value");
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
