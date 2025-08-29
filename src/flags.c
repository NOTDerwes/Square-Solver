#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "../headers/flags.h"


int write_flags(int argc, char *argv[]) {
    int flags = 0;
     for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--test") == 0 || strcmp(argv[i], "-t") == 0) {
            // char *test_file_path = "./tests/test_input.txt"; // Путь до файла с тестами по умолчанию
            // if (i + 1 < argc && argv[i + 1][0] != '-') {
            //         test_file_path = argv[++i]; // Берем следующий аргумент как путь
            // }
            flags |= (int)pow(2, Test);
        }

        if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0)
            flags |= (int)pow(2, Version);

        if (strcmp(argv[i], "--how") == 0 || strcmp(argv[i], "--solve-instruction") == 0) {
//             FILE *instruction_file = fopen("../secrets/instruction.txt", "r");
//
//             printf(YELLOW "Как вы это сделали?\n");
//             printf(GREEN BOLD "Ачивка \"Исследователь\" получена\n" NC);
//             printf(MAGENTA "Обнаружьте флаг --how/--solve-instruction неизвестным автору кода способом " CYAN "(Вы точно не рылись в моем коде :))\n");
//             printf(YELLOW "В качестве награды Вы получаете гайд по решению квадратного уравнения\n\n" NC);
//
//             if (!instruction_file) {
//                 printf(PINK "К сожалению, файл с инструкцией не найден(. Вам придется подумать самим\n" NC);
//                 return 0;
//             }
//             else {
//                 //char *text;
//                 //fscanf(instruction_file, "%s", text);
//                 //printf("%s\n", *text);
//                 printf(BLACK BORDER_HASH "\n" NC);
//                 printf(BOLD BLUE "ПОЗДРАВЛЯЕМ, Вы решили квадратное уравнение.\n" NC);
//                 printf(BLACK BORDER_HASH "\n" NC);
//                 return 0;
//             }
            flags |= (int)pow(2, Instruction);
        }
        if (strcmp(argv[i], "--meow") == 0)
            flags |= (int)pow(2, Meow);

        if (strcmp(argv[i], "--meow-plus") == 0)
            flags |= (int)pow(2, MeowPlus);

        if (strcmp(argv[i], "--meow-plus-plus") == 0)
            flags |= (int)pow(2, MeowPlusPlus);

        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0)
            flags |= (int)pow(2, Help);
    }
    return flags;
}


int is_flag_on(int flags, enum flag_pos pos) {
    return flags & (int)pow(2, pos);
}

// if (is_flag_on(flags, Version)) {
//     printf("Решатель квадратных уравнений\n");
//     printf("Версия: Beta\n");
//     printf("Автор: NOTDerwes\n");
// }
// if (is_flag_on(flags, Meow)) {
//     meow();
//     return 0;
// }
// if(is_flag_on(flags, MeowPlus)) {
//     meow_plus();
//     return 0;
// }
// if (is_flag_on(flags, MeowPlusPlus)) {
//     meow_plus_plus();
//     return 0;
// }
// if (is_flag_on(flags, Help)) {
//     printf("Флаги запуска программы ");
//     printf("Решатель Квадратных Уравнений\n");
//     printf("Функции:\n");
//     printf("    -h, --help                Показать это сообщение\n");
//     printf("    -v, --version             Информация о версии\n");
//     printf("    -t, --test <path_to_test> Запустить тесты, хранящиеся по пути path_to_file. По умолчанию запускает авторские тесты\n");
//     return 0;
// }
