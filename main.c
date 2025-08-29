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

#include <string.h>
#include <math.h>

#include "headers/solve_equation.h"
#include "headers/user_interaction.h"
#include "headers/myassert.h"
#include "headers/flags.h"


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

    FlagsInfo information = {
        .Flags = 0,
        .TestFilePath = "tests/test_input.txt",
        .InstructionPath = ".secrets/instruction.txt"
    };

    // Запуск программы с флагами
    if (execute_flags(argc, argv, &information) == FinishProgram)
        return 0;

    // Инициализация структур данных
    SquareEquation equation = {
        .coeffs = {.a = NAN, .b = NAN, .c = NAN},
        .roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot}
    };
    //MYASSERT(0, "ZERO VALUE GOT");
    // Основной цикл работы программы
    do {
        // Сброс структур перед новым вычислением
        reset_structs(&equation);

        // Ввод коэффициентов уравнения
        if (input(&equation.coeffs) == INPUTERR) return 1;

        // Решение квадратного уравнения
        if (solve_square_equation(&equation) != Solved) return 1;

        // Вывод результатов
        print_ans(equation.roots);

    } while (continue_enter()); // Проверка желания продолжить

    return 0;
}
