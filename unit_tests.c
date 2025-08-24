#include <stdio.h>
#include <math.h>

#include "unit_tests.h"
#include "double_operations.h"
#include "solve_equation.h"

bool check_EOF(int symbol_eof) {
    return symbol_eof == EOF;
}


void test_solve_equation(char path[]) {
    FILE *input_file = fopen(path, "r");

    int red_nums = 0;

    double test_a = NAN, test_b = NAN, test_c = NAN;
    double expected_x1 = NAN, expected_x2 = NAN;
    int expected_rts_amount = UndigistedRoot;

    int correct_tests_amount = 0;
    int tests_amount = 0;

    while (true) {
        test_a = test_b = test_c = NAN;
        expected_x1 = expected_x2 =  NAN;
        expected_rts_amount = UndigistedRoot;

        red_nums = fscanf(input_file, "%lf %lf %lf | %d", &test_a, &test_b, &test_c, &expected_rts_amount);

        if (expected_rts_amount == TwoRoots) {
            fscanf(input_file, "%lf %lf", &expected_x1, &expected_x2);
            if (expected_x1 > expected_x2)
                swap_doubles(&expected_x1, &expected_x2);
        }
        else if (expected_rts_amount == OneRoot)
            fscanf(input_file, "%lf", &expected_x1);

        if (check_EOF(red_nums)) {
            printf("MEET END OF TEST FILE\n\n");
            break;
        }
        if (test_one_equation(test_a, test_b, test_c,
                             expected_x1, expected_x2, expected_rts_amount))
            correct_tests_amount++;

        tests_amount++;
    }
    printf("CORRECTLY COMPLETED TESTS: %lg%%\n\n", 100.0 * correct_tests_amount / tests_amount);
}


int test_one_equation(double test_a, double test_b, double test_c,
                       double expected_x1, double expected_x2, int expected_rts_amount) {
    struct Coeffs test_cf = {.a = test_a, .b = test_b, .c = test_c};
    struct Roots result_rts = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};
    solve_square_equation(test_cf,
                          &result_rts);

    if ((result_rts.amount != expected_rts_amount) ||
        !equal_doubles(expected_x2, result_rts.x2) ||
        !equal_doubles(expected_x1, result_rts.x1)) {
        printf("ERROR in func \"solve_square_equation\"!\n\nINPUT COEFFS\na: %lf\nb: %lf\nc: %lf\n", test_a, test_b, test_c);
        printf("EXPECTED\nroots amount: %d\nx1: %lf\nx2: %lf\n", expected_rts_amount, expected_x1, expected_x2);
        printf("GOT\nroots amount: %d\nx1: %lf\nx2: %lf\n", result_rts.amount, result_rts.x1, result_rts.x2);
        printf("PLEASE CHECK YOUR FUNCTION!\n\n\n\n");
        return 0;
    }
    return 1;
}
