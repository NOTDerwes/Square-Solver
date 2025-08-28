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

void test_solve_equation(char path[]) {
    FILE *input_file = fopen(path, "r");

    int red_nums = 0;

    Coeffs test_cf = {.a = NAN, .b = NAN, .c = NAN};
    Roots expected = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};

    int correct_tests_amount = 0;
    int tests_amount = 0;

    while (true) {
        reset_structs(&test_cf,
                      &expected);

        red_nums = fscanf(input_file, "%lf %lf %lf | %d", &test_cf.a, &test_cf.b, &test_cf.c, &expected.amount);

        if (expected.amount == TwoRoots) {
            fscanf(input_file, "%lf %lf", &expected.x1, &expected.x2);
            if (expected.x1 > expected.x2)
                swap_doubles(&expected.x1, &expected.x2);
        }
        else if (expected.amount == OneRoot)
            fscanf(input_file, "%lf", &expected.x1);

        if (check_EOF(red_nums)) {
            break;
        }
        if (test_one_equation(test_cf,
                             expected))
            correct_tests_amount++;

        tests_amount++;
    }
    printf(GREEN "CORRECTLY COMPLETED TESTS: %lg%%\n\n" NC, 100.0 * correct_tests_amount / tests_amount);
}


void test_with_dyn_arr(char path[]) {
    Coeffs test_cf = {.a = NAN, .b = NAN, .c = NAN};
    Roots expected = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};

    int correct_tests_amount = 0;
    int tests_amount = 0;

    FILE *input_file = fopen(path, "rb");

    if (!input_file) {
        printf("Cannot open file");
        return;
    }
    //MYASSERT(input_file, "File \"test_input.txt.\" is missing or placed in wrong directory");

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
        reset_structs(&test_cf,
                      &expected);

        sscanf(pos, "%lf %lf %lf | %d%n", &test_cf.a, &test_cf.b, &test_cf.c, &expected.amount, &shift);
        pos += shift;

        if (expected.amount == TwoRoots) {
            sscanf(pos, "%lf %lf%n", &expected.x1, &expected.x2, &shift);
            pos += shift;

            if (expected.x1 > expected.x2)
                swap_doubles(&expected.x1, &expected.x2);
        }
        else if (expected.amount == OneRoot) {
            sscanf(pos, "%lf%n", &expected.x1, &shift);
            pos += shift;
        }

        if (test_one_equation(test_cf,
                             expected))
            correct_tests_amount++;
        tests_amount++;
    }
    printf(GREEN "CORRECTLY COMPLETED TESTS: %lg%%\n\n", 100.0 * correct_tests_amount / tests_amount);
    free(input);
}


bool test_one_equation(Coeffs test_cf,
                       Roots expected) {
    Roots result_rts = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};

    solve_square_equation(test_cf,
                          &result_rts);

    if ((result_rts.amount != expected.amount) ||
        !absolutely_same_doubles(expected.x2, result_rts.x2) ||
        !absolutely_same_doubles(expected.x1, result_rts.x1)) {
        printf("ERROR in func \"solve_square_equation\"!\n\nINPUT COEFFS\na: %lf\nb: %lf\nc: %lf\n", test_cf.a, test_cf.b, test_cf.c);
        printf("EXPECTED\nroots amount: %d\nx1: %lf\nx2: %lf\n", expected.amount, expected.x1, expected.x2);
        printf("GOT\nroots amount: %d\nx1: %lf\nx2: %lf\n", result_rts.amount, result_rts.x1, result_rts.x2);
        printf("PLEASE CHECK YOUR FUNCTION!\n\n\n\n");
        return false;
    }
    return true;
}
