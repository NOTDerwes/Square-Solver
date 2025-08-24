#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "double_operations.h"
#include "solve_equation.h"
#include "unit_tests.h"

#define INPUTSIZE 20
char const * const YES_ANSWER = "Да";

void input(struct Coeffs *equation_coeffs);
void input_coeff(char curr_coeff, double *inputing_coeff);
void reset_structs(struct Coeffs *reseting_coeffs,
                   struct Roots *reseting_roots);
int letters_left();
void clean_buffer();
bool continue_enter();
void print_ans(struct Roots equation_roots);

void input(struct Coeffs *equation_coeffs) { ///function gets coeffs of equation
    printf("Введите коэффициенты квадратного трёхчлена.\n");
    input_coeff('a', &equation_coeffs -> a);
    input_coeff('b', &equation_coeffs -> b);
    input_coeff('c', &equation_coeffs -> c);
}


void input_coeff(char curr_coeff, double *inputing_coeff) { ///function gets current coeff
    bool flag_retry = true;
    do {
        printf("Введите коэффициент %c: ", curr_coeff);
        scanf("%lf", inputing_coeff);
        assert(inputing_coeff || "NULL pointer on input");
        if (letters_left() || !is_double(*inputing_coeff)) {
            printf("Коэффициент %c введен в неправильном формате! Попробуйте ещё раз\n", curr_coeff);
            clean_buffer();
        }
        else
            flag_retry = false;
    } while(flag_retry);
}

void reset_structs(struct Coeffs *reseting_coeffs,
                   struct Roots *reseting_roots) { ///set all Coeffs and Roots structure elements default value
    reseting_coeffs -> a = NAN;
    reseting_coeffs -> b = NAN;
    reseting_coeffs -> c = NAN;
    reseting_roots -> x1 = NAN;
    reseting_roots -> x2 = NAN;
    reseting_roots -> amount = UndigistedRoot;
}


int letters_left() { ///checks if letters left in input buffer
    if (getchar() != '\n')
        return 1;
    return 0;
}


void clean_buffer() { ///cleans buffer after using scanf
    while (getchar() != '\n') {}
}


bool continue_enter() {
    char confirmation[INPUTSIZE] = "";
    printf("Введите \"Да\", если хотите продолжить:\n");
    scanf("%5s", confirmation);
    clean_buffer();

    if (strncmp(confirmation, YES_ANSWER, sizeof(YES_ANSWER))) { ///if inputed not "Да", program finishes
        printf("Программа завершена\n");
        return false;
    }
    return true;
}


void print_ans(struct Roots equation_roots) { ///print roots
    double x1 = equation_roots.x1, x2 = equation_roots.x2;
    int roots_amount = equation_roots.amount;
    assert(roots_amount != UndigistedRoot);
    assert(!isnan(x1) || roots_amount < OneRoot);

    if (roots_amount == ZeroRoots) ///0 roots
            printf("КОРНЕЙ НЕТ!!!\n\n");
    else if (roots_amount == UndefinedRoot) ///undefined root
        printf("Корень не определен\n\n");
    else if (roots_amount == OneRoot) ///1 root
        printf("Корень равен %g\n\n", x1);
    else if (roots_amount == TwoRoots) ///2 roots
        printf("Меньший корень равен %g\nБольший корень равен %g\n\n", x1, x2);
}


int main() {
    test_solve_equation("test_input.txt");
    struct Coeffs equation_coeffs = {.a = NAN, .b = NAN, .c = NAN};
    struct Roots equation_roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};
    do {
        reset_structs(&equation_coeffs,
                      &equation_roots);
        input(&equation_coeffs); ///input of coeffs
        solve_square_equation(equation_coeffs,
                              &equation_roots); ///solving of the equation
        print_ans(equation_roots); ///answer outputting
    } while (continue_enter());
    return 0;
}


