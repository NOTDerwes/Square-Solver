#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#define INPUTSIZE 20
#define ZERO 0


enum roots_count {
    UndigistedRoot = 3,
    UndefinedRoot = -1,
    ZeroRoots,
    OneRoot,
    TwoRoots
};

enum doubles_compare_flag {
    Smaller = -1,
    Equal,
    Bigger
};

struct Coeffs {
    double a;
    double b;
    double c;
};

struct Roots {
    double x1;
    double x2;
    int amount;
};


void input(struct Coeffs *equation_coeffs);
void input_coeff(char curr_coeff, double *inputing_coeff);
void swap_doubles(double *first, double *second);
void reset_structs(struct Coeffs *reseting_coeffs,
                   struct Roots *reseting_roots);
bool is_double(double num);
int letters_left();
void clean_buffer();
void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots);
void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount);
int compare_doubles(double first, double second);
bool equal_doubles(double first, double second);
bool check_EOF(int if_eof);
bool same_double_type(double first, double second);
void print_ans(struct Roots equation_roots);
void test_solve_equation(char path[]);


void input(struct Coeffs *equation_coeffs) { //function gets coeffs of equation
    printf("Введите коэффициенты квадратного трёхчлена.\n");
    input_coeff('a', &equation_coeffs -> a);
    input_coeff('b', &equation_coeffs -> b);
    input_coeff('c', &equation_coeffs -> c);
}


void input_coeff(char curr_coeff, double *inputing_coeff) { //function gets current coeff
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


void swap_doubles(double *first, double *second) {
    double temp = *first;
    *first = *second;
    *second = temp;
}


void reset_structs(struct Coeffs *reseting_coeffs,
                   struct Roots *reseting_roots) {
    reseting_coeffs -> a = NAN;
    reseting_coeffs -> b = NAN;
    reseting_coeffs -> c = NAN;
    reseting_roots -> x1 = NAN;
    reseting_roots -> x2 = NAN;
    reseting_roots -> amount = UndigistedRoot;
}


 bool is_double(double num) { //checks if number is double-like
    return !isnan(num) && !isinf(num);
}


int compare_doubles(double first, double second) {
    double delta = first - second;
    if (delta < -DBL_EPSILON)
        return Smaller;
    else if (delta > DBL_EPSILON)
        return Bigger;
    return Equal;
}


int letters_left() { //checks if letters left in input buffer
    if (getchar() != '\n')
        return 1;
    return 0;
}


void clean_buffer() { //cleans buffer after using scanf
    while (getchar() != '\n') {}
}


void solve_square_equation(struct Coeffs equation_coeffs,
                           struct Roots *equation_roots) { //function solves equation
    double a = equation_coeffs.a, b = equation_coeffs.b, c = equation_coeffs.c;
    double *x1 = &(equation_roots -> x1), *x2 = &(equation_roots -> x2);
    int *roots_amount = &(equation_roots -> amount);

    //checking of programmer errors
    assert(x1 || "NULL pointer on x1");
    assert(x2 || "NULL pointer on x2");
    assert(!isnan(a) || "a is nan");
    assert(!isnan(b) || "b is nan");
    assert(!isnan(c) || "c is nan");

    *roots_amount = ZeroRoots; //default amount of roots

    if (equal_doubles(a, ZERO)) { //equation of type bx+c=0
        solve_linear_equation(b, c, x1, roots_amount);
        return;
    }
    else { //square equation of type ax^2+bx+c=0, a != 0
        double discriminant = b * b - 4 * a * c; //discriminant
        if (discriminant > 0) { //2 roots
            *x1 = (-b - sqrt(discriminant)) / (2 * a); //smaller root
            *x2 = (-b + sqrt(discriminant)) / (2 * a); //bigger root
            *roots_amount = TwoRoots;
        }
        else if (equal_doubles(discriminant, ZERO)) { //one root
            *x1 = -b / (2 * a);
            *roots_amount = OneRoot;
        }
    }

    //if root equals -0, turn it to 0
    if (equal_doubles(*x1, ZERO))
        *x1 = 0;

    if (equal_doubles(*x2, ZERO))
        *x2 = 0;
}


void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount) { //solves equations of type kx+b=0
    if (equal_doubles(k, ZERO)) { //equation of type b=0
            if (equal_doubles(b, ZERO))
                *roots_amount = UndefinedRoot; //undefined root
        }
        else { //equation of type kx+b=0, k != 0
            *x = -b / k;
            *roots_amount = OneRoot;
        }
    //if root equals -0, turn it to 0
    if (equal_doubles(*x, ZERO))
        *x = 0;
}


bool same_double_type(double first, double second) {
    if(isinf(first) && isinf(second))
        return signbit(first) == signbit(second);
    return (isnan(first) && isnan(second)) ||
            (is_double(first) && is_double(second));
}


bool equal_doubles(double first, double second) {
    if (same_double_type(first, second)) {
        if (is_double(first))
            return compare_doubles(first, second) == Equal;
        return true;
    }
    return false;
}


bool check_EOF(int if_eof) {
    return if_eof == EOF;
}


void test_solve_equation(char path[]) {
    struct Coeffs test_cf = {.a = NAN, .b = NAN, .c = NAN};
    struct Roots expected_rts = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};
    struct Roots result_rts = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};

    FILE *input_file = fopen(path, "r");
    int red_nums = 0;

    while (true) {
        reset_structs(&test_cf,
                      &expected_rts);
        result_rts.x1 = NAN;
        result_rts.x2 = NAN;
        result_rts.amount = UndigistedRoot;

        red_nums = fscanf(input_file, "%lf %lf %lf | %d", &test_cf.a, &test_cf.b, &test_cf.c, &expected_rts.amount);

        if (expected_rts.amount == TwoRoots) {
            fscanf(input_file, "%lf %lf", &expected_rts.x1, &expected_rts.x2);
            if (expected_rts.x1 > expected_rts.x2)
                swap_doubles(&expected_rts.x1, &expected_rts.x2);
        }
        else if (expected_rts.amount == OneRoot)
            fscanf(input_file, "%lf", &expected_rts.x1);

        if (check_EOF(red_nums)) {
            printf("MEET END OF TEST FILE\n\n");
            break;
        }

        solve_square_equation(test_cf,
                              &result_rts);

        if ((result_rts.amount != expected_rts.amount) ||
            !same_double_type(expected_rts.x2, result_rts.x2) ||
            !same_double_type(expected_rts.x1, result_rts.x1) ||
            !equal_doubles(expected_rts.x2, result_rts.x2) ||
            !equal_doubles(expected_rts.x1, result_rts.x1)) {
            printf("%d %d %d %d %d\n", (result_rts.amount != expected_rts.amount),
            !same_double_type(expected_rts.x2, result_rts.x2),
            !same_double_type(expected_rts.x1, result_rts.x1),
            !equal_doubles(expected_rts.x2, result_rts.x2),
            !equal_doubles(expected_rts.x1, result_rts.x1));
            printf("ERROR in func \"solve_square_equation\"!\n\nINPUT COEFFS\na: %lf\nb: %lf\nc: %lf\n", test_cf.a, test_cf.b, test_cf.c);
            printf("EXPECTED\nroots amount: %d\nx1: %lf\nx2: %lf\n", expected_rts.amount, expected_rts.x1, expected_rts.x2);
            printf("GOT\nroots amount: %d\nx1: %lf\nx2: %lf\n", result_rts.amount, result_rts.x1, result_rts.x2);
            printf("PLEASE CHECK YOUR FUNCTION!\n\n\n\n");
        }
    }
}


void print_ans(struct Roots equation_roots) { //print roots
    double x1 = equation_roots.x1, x2 = equation_roots.x2;
    int roots_amount = equation_roots.amount;
    assert(roots_amount != UndigistedRoot);
    assert(!isnan(x1) || roots_amount < OneRoot);

    if (roots_amount == ZeroRoots) //0 roots
            printf("КОРНЕЙ НЕТ!!!\n\n");
    else if (roots_amount == UndefinedRoot) //undefined root
        printf("Корень не определен\n\n");
    else if (roots_amount == OneRoot) //1 root
        printf("Корень равен %g\n\n", x1);
    else if (roots_amount == TwoRoots) //2 roots
        printf("Меньший корень равен %g\nБольший корень равен %g\n\n", x1, x2);
}


int main() {
    test_solve_equation("test_input.txt");
    char if_continue[INPUTSIZE] = {}; //flag if user wants to continue inputing equations
    struct Coeffs equation_coeffs = {.a = NAN, .b = NAN, .c = NAN};
    struct Roots equation_roots = {.x1 = NAN, .x2 = NAN, .amount = UndigistedRoot};
    bool continue_enter = true;
    while (continue_enter) {
        reset_structs(&equation_coeffs,
                      &equation_roots);
        input(&equation_coeffs); //input of coeffs
        solve_square_equation(equation_coeffs,
                              &equation_roots); //solving of the equation
        print_ans(equation_roots); //answer outputting
        printf("Введите \"Да\", если хотите ввести ещё одно уравнение\n");
        scanf("%5s", if_continue);
        clean_buffer();

        if (strcmp(if_continue, "Да")) { //if inputed not "Да", program finishes
            printf("Программа завершена\n");
            continue_enter = false;
        }
    }
    return 0;
}


