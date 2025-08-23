#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>
#define UNDEFINED_ROOTS -1
#define ZERO_ROOTS 0
#define ONE_ROOT 1
#define TWO_ROOTS 2
#define TRUE 1
#define FALSE 0


void input(struct coeffs *);
void input_coeff(char curr_coeff, double *inputing_coeff);
int is_double(double *num);
void clean_buffer();
void solve_equation(double a, double b, double c,
                    double *x1, double *x2,
                    int *roots_amount);
void print_ans(double x1, double x2, int roots_amount);

struct coeffs {
    double a;
    double b;
    double c;
};

struct roots {
    double x1;
    double x2;
    int amount;
};

void input(struct coeffs *equation_coeffs) { //function gets coeffs of equation
    printf("Введите коэффициенты квадратного трёхчлена.\n");
    input_coeff('a', &equation_coeffs -> a);
    input_coeff('b', &equation_coeffs -> b);
    input_coeff('c', &equation_coeffs -> c);
}


void input_coeff(char curr_coeff, double *inputing_coeff) { //function gets current coeff
    int correct_input = FALSE; //check if inputing letters instead of digits
    int flag_retry = TRUE;
    do {
        printf("Введите коэффициент %c: ", curr_coeff);
        correct_input = scanf("%lf", inputing_coeff);

        assert(inputing_coeff != NULL || "NULL pointer on input");

        if (!correct_input || !is_double(inputing_coeff))
            printf("Коэффициент %c введен в неправильном формате! Попробуйте ещё раз\n", curr_coeff);
        else
            flag_retry = FALSE;

        clean_buffer();
    } while(flag_retry);
}


int is_double(double *num) { //checks if number is double-like
    return !isnan(*num) && !isinf(*num);
}


void clean_buffer() { //cleans buffer after using scanf
    while (getchar() != '\n') {}
}


void solve_equation(double a, double b, double c,
                           double *x1, double *x2,
                           int *roots_amount) { //function solves equation

    //checking of programmer errors
    assert(x1 != NULL || "NULL pointer on x1");
    assert(x2 != NULL || "NULL pointer on x2");
    assert(!isnan(a) || "a is nan");
    assert(!isnan(b) || "b is nan");
    assert(!isnan(c) || "c is nan");

    *roots_amount = ZERO_ROOTS; //default amount of roots
    if (fabs(a) < DBL_EPSILON) { //equation of type bx+c=0
        if (fabs(b) < DBL_EPSILON) { //equation of type c=0
            if (fabs(c) < DBL_EPSILON)
                *roots_amount = UNDEFINED_ROOTS; //undefined root
        }
        else { //equation of type bx+c=0, b != 0
            *x1 = -c / b;
            *roots_amount = ONE_ROOT;
        }
    }
    else { //square equation of type ax^2+bx+c=0, a != 0
        double discriminant = b * b - 4 * a * c; //discriminant
        if (discriminant > 0) { //2 roots
            *x1 = (-b - sqrt(discriminant)) / (2 * a); //smaller root
            *x2 = (-b + sqrt(discriminant)) / (2 * a); //bigger root
            *roots_amount = TWO_ROOTS;
        }
        else if (fabs(discriminant) < DBL_EPSILON) { //one root
            *x1 = -b / (2 * a);
            *roots_amount = ONE_ROOT;
        }
    }

    //if root equals -0, turn it to 0
    if (fabs(*x1) < DBL_EPSILON)
        *x1 = 0;

    if (fabs(*x2) < DBL_EPSILON)
        *x2 = 0;
}


void print_ans(double x1, double x2,
               int roots_amount) { //print roots

    assert(UNDEFINED_ROOTS <= roots_amount && roots_amount <= TWO_ROOTS);
    assert(!isnan(x1) || roots_amount < ONE_ROOT);

    if (roots_amount == ZERO_ROOTS) //0 roots
            printf("КОРНЕЙ НЕТ!!!\n\n");
    else if (roots_amount == UNDEFINED_ROOTS) //undefined root
        printf("Корень не определен\n\n");
    else if (roots_amount == ONE_ROOT) //1 root
        printf("Корень равен %g\n\n", x1);
    else if (roots_amount == TWO_ROOTS) //2 roots
        printf("Меньший корень равен %g\nБольший корень равен %g\n\n", x1, x2);
}


int main() {
    char if_continue[10] = {}; //flag if user wants to continue inputing equations
    struct coeffs equation_coeffs = {NAN};
    struct roots equation_roots = {NAN};
    int continue_enter = TRUE;
    while (continue_enter) {
        equation_coeffs = {NAN};
        equation_roots = {NAN};
        input(&equation_coeffs); //input of coeffs
        solve_equation(equation_coeffs.a, equation_coeffs.b, equation_coeffs.c,
                       &equation_roots.x1, &equation_roots.x2, &equation_roots.amount); //solving of the equation
        print_ans(equation_roots.x1, equation_roots.x2, equation_roots.amount); //answer outputting
        printf("Введите \"Да\", если хотите ввести ещё одно уравнение\n");
        scanf("%5s", if_continue);
        clean_buffer();

        if (strcmp(if_continue, "Да")) { //if inputed not "Да", program finishes
            printf("Программа завершена\n");
            continue_enter = FALSE;
        }
    }
    return 0;
}
