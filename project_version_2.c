#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

void input(double *a, double *b, double *c);
void input_coeff(char curr_coeff, double *inputing_coeff);
int is_double(double *num);
void clean_buffer();
void solve_equation(double a, double b, double c,
                           double *x1, double *x2,
                           int *roots_amount);
void print_ans(double x1, double x2, int roots_amount);


void input(double *a, double *b, double *c) { //function gets coeffs of equation
    printf("Введите коэффициенты квадратного трёхчлена.\n");
    input_coeff('a', a);
    input_coeff('b', b);
    input_coeff('c', c);
}


void input_coeff(char curr_coeff, double *inputing_coeff) { //function gets current coeff
    int correct_input = 0; //check if inputing letters instead of digits
    int flag_retry = 1;
    do {
        printf("Введите коэффициент %c: ", curr_coeff);
        correct_input = scanf("%lf", inputing_coeff);

        assert(inputing_coeff != NULL || "NULL pointer on input");

        if (!correct_input || !is_double(inputing_coeff))
            printf("Коэффициент %c введен в неправильном формате! Попробуйте ещё раз\n", curr_coeff);
        else
            flag_retry = 0;

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

    *roots_amount = 0; //default amount of roots
    if (fabs(a) < DBL_EPSILON) { //equation of type bx+c=0
        if (fabs(b) < DBL_EPSILON) { //equation of type c=0
            if (fabs(c) < DBL_EPSILON)
                *roots_amount = -1; //undefined root
        }
        else { //equation of type bx+c=0, b != 0
            *x1 = -c / b;
            *roots_amount = 1;
        }
    }
    else { //square equation of type ax^2+bx+c=0, a != 0
        double discriminant = b * b - 4 * a * c; //discriminant
        if (discriminant > 0) { //2 roots
            *x1 = (-b - sqrt(discriminant)) / (2 * a); //smaller root
            *x2 = (-b + sqrt(discriminant)) / (2 * a); //bigger root
            *roots_amount = 2;
        }
        else if (fabs(discriminant) < DBL_EPSILON) { //one root
            *x1 = -b / (2 * a);
            *roots_amount = 1;
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

    assert(-1 <= roots_amount && roots_amount <= 2);
    assert(!isnan(x1) || roots_amount < 1);

    if (roots_amount == 0) //0 roots
            printf("КОРНЕЙ НЕТ!!!\n\n");
    else if (roots_amount == -1) //undefined root
        printf("Корень не определен\n\n");
    else if (roots_amount == 1) //1 root
        printf("Корень равен %g\n\n", x1);
    else if (roots_amount == 2) //2 roots
        printf("Меньший корень равен %g\nБольший корень равен %g\n\n", x1, x2);
}


int main() {
    double a = NAN, b = NAN, c = NAN; //coeffs of equation
    double x1 = NAN, x2 = NAN; //roots of equation
    int roots_amount = NAN; //amount of roots, default value - 0
    char if_continue[10] = {}; //flag if user wants to continue inputing equations
    int continue_enter = 1;
    while (continue_enter) {
        a = NAN, b = NAN, c = NAN;
        x1 = NAN, x2 = NAN;
        input(&a, &b, &c); //input of coeffs
        solve_equation(a, b, c, &x1, &x2, &roots_amount); //solving of the equation
        print_ans(x1, x2, roots_amount); //answer outputting

        printf("Введите \"Да\", если хотите ввести ещё одно уравнение\n");
        scanf("%3s", if_continue);
        clean_buffer();

        if (strcmp(if_continue, "Да")) { //if inputed not "Да", program finishes
            printf("Программа завершена\n");
            continue_enter=0;
        }
    }
    return 0;
}
