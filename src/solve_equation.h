#ifndef SOLVE_EQUATION_H
#define SOLVE_EQUATION_H

/*!
 * @file solve_equation.h
 * @brief Модуль решения квадратных и линейных уравнений
 * @author NOTDerwes
 * @date 25.08.2025
 * @version Beta
 *
 * Модуль предоставляет функции для решения квадратных уравнений вида @f$ ax^2 + bx + c = 0 @f$
 * и линейных уравнений вида @f$ kx + b = 0 @f$ с решением частных случаев.
 */

/*!
 * @enum roots_count
 * @brief Количество корней уравнения
 *
 * Перечисление возможных случаев количества корней уравнения,
 * включая специальные случаи.
 */
enum roots_count {
    UndigistedRoot = 3,  ///< Неопределенное значение (инициализация)
    UndefinedRoot = -1,  ///< Бесконечное количество корней
    ZeroRoots = 0,       ///< Нет корней
    OneRoot = 1,         ///< Один корень
    TwoRoots = 2,        ///< Два корня
};

/*!
 * @struct Coeffs
 * @brief Коэффициенты квадратного уравнения
 *
 * Структура хранит коэффициенты квадратного уравнения вида @f$ ax^2 + bx + c = 0 @f$
 */
typedef struct {
    double a; ///< Коэффициент при @f$ x^2 @f$
    double b; ///< Коэффициент при @f$ x @f$
    double c; ///< Свободный член
} Coeffs;

/*!
 * @struct Roots
 * @brief Корни уравнения и информация о них
 *
 * Структура хранит корни уравнения и информацию об их количестве.
 * Для отдельных случаев корням присваиваются значения NaN.
 */
typedef struct {
    double x1; ///< Меньший корень уравнения, по умолчанию NaN (если корней нет или бесконечно)
    double x2; ///< Больший корень уравнения, по умолчанию NaN (если меньше 2 корней или бесконечно)
    enum roots_count amount; ///< Количество корней (см. roots_count)
} Roots;

/*!
 * @brief Решение квадратного уравнения
 *
 * Решает квадратное уравнение вида @f$ ax^2 + bx + c = 0 @f$.
 * Обрабатывает все частные случаи: вырожденные уравнения,
 * линейные случаи, отсутствие корней.
 *
 * @param[in] equation_coeffs Коэффициенты уравнения
 * @param[out] equation_roots Указатель на структуру для результатов
 *
 * @note Для @f$ a = 0 @f$ вызывает solve_linear_equation()
 * @note Устанавливает x1 и x2 в NaN при отсутствии корней, если корень один, устанавливает только x2 в NaN
 * @see solve_linear_equation(), reset_structs()
 */
void solve_square_equation(Coeffs equation_coeffs,
                           Roots *equation_roots);

/*!
 * @brief Решение линейного уравнения
 *
 * Решает линейное уравнение вида @f$ kx + b = 0 @f$ .
 * Обрабатывает частные случаи: @f$ k = 0, b = 0 @f$.
 *
 * @param[in] k Коэффициент при x
 * @param[in] b Свободный член
 * @param[out] x Указатель для сохранения корня
 * @param[out] roots_amount Указатель для сохранения количества корней
 *
 * @warning x и roots_amount не должны быть NULL
 *
 * @note Устанавливает x в NaN при отсутствии корней
 * @note Для @f$ k = 0 @f$ и @f$ b = 0 @f$: бесконечное количество корней
 * @note Для @f$ k = 0 @f$ и @f$ b \neq 0 @f$: нет корней
 * @see solve_square_equation(), Roots
 */
void solve_linear_equation(double k, double b,
                           double *x,
                           int *roots_amount);

/*!
 * @brief Сброс структур в начальное состояние
 *
 * Инициализирует структуры Coeffs и Roots
 * значениями по умолчанию (NaN для коэффициентов и
 * для корней, UndigistedRoot для их количества).
 *
 * @param[out] reseting_coeffs Указатель на структуру коэффициентов
 * @param[out] reseting_roots Указатель на структуру корней
 *
 * @warning Указатели не должны быть NULL
 * @note Используется для сброса структур при повторном использовании
 */
void reset_structs(Coeffs *reseting_coeffs,
                   Roots *reseting_roots);

#endif
