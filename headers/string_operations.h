#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define ORANGE "\033[38;5;208m"
#define PURPLE "\033[38;5;93m"
#define PINK "\033[38;5;199m"
#define LIME "\033[38;5;118m"
#define TEAL "\033[38;5;30m"
#define LAVENDER "\033[38;5;183m"
#define CORAL "\033[38;5;203m"
#define GOLD "\033[38;5;220m"
#define SILVER "\033[38;5;7m"
#define MAROON "\033[38;5;88m"
#define NC "\033[0m"

#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

#define BORDER_SINGLE "────────────────────────────────────────"
#define BORDER_DOUBLE "════════════════════════════════════════"
#define BORDER_STAR   "****************************************"
#define BORDER_HASH   "########################################"
#define BORDER_EQUAL  "========================================"
#define BORDER_DASH   "----------------------------------------"

#define META_INFO  __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__


#define ERROR_MESSAGE(fmt)                         \
    BORDER_HASH "\n%s %s\n[MEOWRROR] in %s %s %d: "   \
    fmt "\n" BORDER_HASH "\n", META_INFO

#define SUCCESS_MESSAGE()                            \
    BORDER_EQUAL                                     \
    "\n%s %s\n[SUCCESSMURRRLY FINISHED] in %s %s %d\n" \
     BORDER_EQUAL "\n", META_INFO                    \


#define CONSOLE_ERROR_MESSAGE(fmt)                 \
    YELLOW BORDER_HASH CYAN "\n%s %s\n" RED        \
    "[ERROR] in " MAGENTA "%s %s %d: " NC UNDERLINE\
    fmt "\n" YELLOW BORDER_HASH NC "\n", META_INFO

#define CONSOLE_SUCCESS_MESSAGE()                   \
    YELLOW BORDER_EQUAL CYAN "\n%s %s\n" GREEN      \
    "[SUCCESSFULLY FINISHED] in " MAGENTA "%s %s %d"\
    NC "\n" YELLOW BORDER_EQUAL NC "\n", META_INFO


#define WRITE_TO_FILE(path, fmt)            \
do {                                        \
    FILE *input_file = fopen(path, "a");    \
    if (input_file == NULL) {               \
        input_file = fopen(path, "w");      \
    }                                       \
    fprintf(input_file, fmt);               \
    fclose(input_file);                     \
} while(0)

/*!
 * @enum str_err
 * @brief Ошибки выполнения функций со строками
 *
 * Флаги ошибок функций, работающих со строками
 */
enum str_err {
    STRINGERR = -3,  ///< Вызов операций со строкой вызвал ошибку
    STRINGOK = 2           ///< Функция завершилась штатно
};

/*!
 * @brief Проверка символа на конец файла (EOF)
 *
 * Функция проверяет, является ли переданный символ маркером конца файла.
 *
 * @param[in] symbol_eof Проверяемый символ
 * @return @b true если символ является концом файла
 * @return @b false если символ не является концом файла
 *
 * @note Используется при чтении тестовых данных из файла
 */
bool check_EOF(int symbol_eof);

/**
 * @brief Проверка наличия символов в буфере ввода
 *
 * Проверяет, остались ли символы в буфере ввода после scanf
 *
 * @return @b 1 если в буфере есть символы
 * @return @b 0 если буфер пуст
 *
 * @note Используется для проверки корректности ввода чисел
 */
bool letters_left();

/**
 * @brief Очистка буфера ввода
 *
 * Очищает стандартный поток ввода до символа новой строки
 *
 * @note Используется после некорректного ввода
 */
int clean_buffer();

#endif
