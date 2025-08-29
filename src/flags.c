#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/flags.h"
#include "../.secrets/cats.h"
#include "../headers/string_operations.h"
#include "../headers/unit_tests.h"


int read_flags(int argc, char *argv[], FlagsInfo *information) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--test") == 0 || strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc && argv[i + 1][0] != '-')
                    information -> TestFilePath = argv[++i];

            information -> Flags |= (int)pow(2, Test);
        }

        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
            information -> Flags |= (int)pow(2, Version);

        if (strcmp(argv[i], "--how") == 0 || strcmp(argv[i], "--solve-instruction") == 0)
            information -> Flags |= (int)pow(2, Instruction);

        if (strcmp(argv[i], "--meow") == 0)
            information -> Flags |= (int)pow(2, Meow);

        if (strcmp(argv[i], "--meow-plus") == 0)
            information -> Flags |= (int)pow(2, MeowPlus);

        if (strcmp(argv[i], "--meow-plus-plus") == 0)
            information -> Flags |= (int)pow(2, MeowPlusPlus);

        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
            information -> Flags |= (int)pow(2, Help);
    }
    return FlagsRed;
}


int is_flag_on(int flags, enum flag_pos pos) {
    return flags & (int)pow(2, pos);
}

int execute_flags(int argc, char *argv[], FlagsInfo *information) {
    read_flags(argc, argv, information);

    if (is_flag_on(information -> Flags, Test)) {
        test_solve_equation(information -> TestFilePath);
        return FinishProgram;
    }

    if (is_flag_on(information -> Flags, Version)) {
        printf("Решатель квадратных уравнений\n");
        printf("Версия: Beta\n");
        printf("Автор: NOTDerwes\n");
        return FinishProgram;
    }

    if (is_flag_on(information -> Flags, Meow)) {
        meow();
        return FinishProgram;
    }

    if(is_flag_on(information -> Flags, MeowPlus)) {
        meow_plus();
        return FinishProgram;
    }

    if (is_flag_on(information -> Flags, MeowPlusPlus)) {
        meow_plus_plus();
        return FinishProgram;
    }

    if (is_flag_on(information -> Flags, Instruction)) {
        FILE *instruction_file = fopen(information -> InstructionPath, "rb");

        printf(YELLOW "Как вы это сделали?\n");
        printf(GREEN BOLD "Ачивка \"Исследователь\" получена\n" NC);
        printf(MAGENTA "Обнаружьте флаг --how/--solve-instruction неизвестным автору кода способом " CYAN "(Вы точно не рылись в моем коде :))\n");
        printf(YELLOW "В качестве награды Вы получаете гайд по решению квадратного уравнения\n\n" NC);

        if (!instruction_file) {
            printf(PINK "К сожалению, файл с инструкцией не найден(. Вам придется подумать самостоятельно\n" NC);
            return FinishProgram;
        }
        else {
            fseek(instruction_file, 0, SEEK_END);
            size_t size = (size_t) ftell(instruction_file);
            fseek(instruction_file, 0, SEEK_SET);

            char *text = (char*) malloc(size + 1);
            fread(text, 1, size, instruction_file);
            text[size] = '\0';
            fclose(instruction_file);

            printf(BLACK BORDER_HASH "\n" NC);
            printf("%s\n", text);
            printf(BOLD BLUE "ПОЗДРАВЛЯЕМ, Вы решили квадратное уравнение.\n" NC);
            printf(BLACK BORDER_HASH "\n" NC);
            return FinishProgram;
        }
    }

    if (is_flag_on(information -> Flags, Help)) {
        printf("Флаги запуска программы ");
        printf("Решатель Квадратных Уравнений\n");
        printf("Функции:\n");
        printf("    -h, --help                Показать это сообщение\n");
        printf("    -v, --version             Информация о версии\n");
        printf("    -t, --test <path_to_test> Запустить тесты, хранящиеся по пути path_to_file. По умолчанию запускает авторские тесты\n");
        return FinishProgram;
    }
    return ExecuteMain;
}
