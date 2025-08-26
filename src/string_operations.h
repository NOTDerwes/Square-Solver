#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define CYAN "\033[36m"
#define MAGENTA "\033[35m"
#define BOLD "\033[1m"
#define NC "\033[0m"

#define BORDER_SINGLE "────────────────────────────────────────"
#define BORDER_DOUBLE "════════════════════════════════════════"
#define BORDER_STAR   "****************************************"
#define BORDER_HASH   "########################################"
#define BORDER_EQUAL  "========================================"
#define BORDER_DASH   "----------------------------------------"


#define ERROR_MESSAGE(fmt)                       \
    YELLOW BORDER_HASH NC "\n" __DATE__ " "      \
    __TIME__ " " __FILE__ " %d\n" RED "[ERROR]:" \
    NC fmt "\n" YELLOW BORDER_HASH NC "\n",      \
    __LINE__


#define WRITE_TO_FILE(path, fmt)         \
    FILE *input_file = fopen(path, "a"); \
    if (input_file == NULL) {            \
        input_file = fopen(path, "w");   \
    }                                    \
    fprintf(input_file, fmt);            \
    fclose(input_file);

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
void clean_buffer();

#endif
