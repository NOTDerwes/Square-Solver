/*!
 * @file unit_tests.c
 * @brief Модуль тестирования решения квадратных уравнений
 * @author NOTDerwes
 * @date 25.08.2025
 * @version Beta
 *
 * Модуль предоставляет функции для тестирования решения квадратных уравнений
 */

#include <stdio.h>
#include <math.h>

#include "unit_tests.h"
#include "double_operations.h"
#include "string_operations.h"

int test_solve_equation(char path[]) {
    FILE *input_file = fopen(path, "r");
    if (!input_file) {
        printf(CONSOLE_ERROR_MESSAGE("MISSING TEST INPUT FILE"));
        return FILEERR;
    }

    int red_nums = 0;
    SquareEquation test_equation = {
        .coeffs = {.a = NAN, .b = NAN, .c = NAN},
        .roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot}
    };

    int correct_tests_amount = 0;
    int tests_amount = 0;

    while (!check_EOF(red_nums)) {
        reset_structs(&test_equation);

        red_nums = fscanf(input_file, "%lf %lf %lf | %d", &test_equation.coeffs.a, &test_equation.coeffs.b, &test_equation.coeffs.c, &test_equation.roots.amount);

        if (test_equation.roots.amount == TwoRoots) {
            fscanf(input_file, "%lf %lf", &test_equation.roots.x1, &test_equation.roots.x2);
            if (test_equation.roots.x1 > test_equation.roots.x2)
                swap_doubles(&test_equation.roots.x1, &test_equation.roots.x2);
        }
        else if (test_equation.roots.amount == OneRoot)
            fscanf(input_file, "%lf", &test_equation.roots.x1);

        if (check_EOF(red_nums)) {
            break;
        }

        if (test_one_equation(test_equation))
            correct_tests_amount++;

        tests_amount++;
    }
    printf(GREEN "CORRECTLY COMPLETED TESTS: %lg%%\n\n" NC, 100.0 * correct_tests_amount / tests_amount);
    return PASSED;
}


int test_with_dyn_arr(char path[]) {
    SquareEquation test_equation = {
        .coeffs = {.a = NAN, .b = NAN, .c = NAN},
        .roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot}
    };

    int correct_tests_amount = 0;
    int tests_amount = 0;

    FILE *input_file = fopen(path, "rb");

    if (!input_file) {
        printf("Cannot open file");
        return FILEERR;
    }

    fseek(input_file, 0, SEEK_END);
    size_t inp_size = (size_t) ftell(input_file);
    fseek(input_file, 0, SEEK_SET);
    char *input = (char*) malloc(inp_size + 1);
    char *pos = input;
    int shift = 0;


    fread(input, 1, inp_size, input_file);
    input[inp_size] = '\0';
    fclose(input_file);

    while (pos - input + 1 < (int) inp_size) {
        reset_structs(&test_equation);

        sscanf(pos, "%lf %lf %lf | %d%n", &test_equation.coeffs.a, &test_equation.coeffs.b, &test_equation.coeffs.c, &test_equation.roots.amount, &shift);
        pos += shift;

        if (test_equation.roots.amount == TwoRoots) {
            sscanf(pos, "%lf %lf%n", &test_equation.roots.x1, &test_equation.roots.x2, &shift);
            pos += shift;

            if (test_equation.roots.x1 > test_equation.roots.x2)
                swap_doubles(&test_equation.roots.x1, &test_equation.roots.x2);
        }
        else if (test_equation.roots.amount == OneRoot) {
            sscanf(pos, "%lf%n", &test_equation.roots.x1, &shift);
            pos += shift;
        }

        if (test_one_equation(test_equation))
            correct_tests_amount++;
        tests_amount++;
    }
    printf(GREEN "CORRECTLY COMPLETED TESTS: %lg%%\n\n", 100.0 * correct_tests_amount / tests_amount);

    free(input);
    return PASSED;
}

bool test_one_equation(SquareEquation test_equation) {
    SquareEquation result_equation = {
        .coeffs = test_equation.coeffs,
        .roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot}
    };

    if (solve_square_equation(&result_equation) != SOLVED ||
        (result_equation.roots.amount != test_equation.roots.amount) ||
        !absolutely_same_doubles(test_equation.roots.x2, result_equation.roots.x2) ||
        !absolutely_same_doubles(test_equation.roots.x1, result_equation.roots.x1)) {
        printf("ERROR in func \"solve_square_equation\"!\n\nINPUT COEFFS\na: %lf\nb: %lf\nc: %lf\n", test_equation.coeffs.a, test_equation.coeffs.b, test_equation.coeffs.c);
        printf("EXPECTED\nroots amount: %d\nx1: %lf\nx2: %lf\n", test_equation.roots.amount, test_equation.roots.x1, test_equation.roots.x2);
        printf("GOT\nroots amount: %d\nx1: %lf\nx2: %lf\n", result_equation.roots.amount, result_equation.roots.x1, result_equation.roots.x2);
        printf("PLEASE CHECK YOUR FUNCTION!\n\n\n\n");
        return false;
    }
    return true;
}
