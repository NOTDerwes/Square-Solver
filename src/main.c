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
    // Запуск программы с флагами
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--test") == 0 || strcmp(argv[i], "-t") == 0) {
            char *test_file_path = "./tests/test_input.txt"; // Путь до файла с тестами по умолчанию
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                    test_file_path = argv[++i]; // Берем следующий аргумент как путь
            }
            test_solve_equation(test_file_path);
            return 0;
        }
        else if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
            printf("Решатель квадратных уравнений\n");
            printf("Версия: Beta\n");
            printf("Автор: NOTDerwes\n");
            return 0;
        }
        else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            printf("Флаги запуска программы ");
            printf("Решатель Квадратных Уравнений\n");
            printf("Функции:\n");
            printf("    -h, --help                Показать это сообщение\n");
            printf("    -v, --version             Информация о версии\n");
            printf("    -t, --test <path_to_test> Запустить тесты, хранящиеся по пути path_to_file. По умолчанию запускает авторские тесты\n");
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
