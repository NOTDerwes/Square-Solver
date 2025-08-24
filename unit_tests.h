#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H
#include <stdbool.h>

int test_one_equation(double test_a, double test_b, double test_c,
                       double expected_x1, double expected_x2, int expected_rts_amount);
bool check_EOF(int symbol_eof);
void test_solve_equation(char path[]);

#endif
