#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H
#include <stdbool.h>
#include "solve_equation.h"

/** Function recieves values of coefficients of test square equation and expected correct roots.
If expected roots match to the roots, recieved as a result of work of function
"solve_square_equation", function returns 1, otherwise 0 */
bool test_one_equation(struct Coeffs test_cf,
                       struct Roots expected);
/** Function checks if last symbol of input is end of file.
Returns 1 if symbol is end of file, returns 0 otherwise */
bool check_EOF(int symbol_eof);
/** Function recieves values of coefficients of test square equation
and expected correct roots from test file "test_input.txt"
If some of the result values of roots doesn't match to expected roots value
function prints error, expected and result error.
When all tests are done, function returns percentage of correct tests */
void test_solve_equation(char path[]);

#endif
