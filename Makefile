.PHONY: clean run debug test help doxy-docs doxy-open meow meow-plus meow-plus-plus
#Compiler and flags
CC = gcc
DIR = src
CFLAGS = -D_DEBUG -ggdb3 -std=c17 -O0 -Wall -Wextra \
        -Waggressive-loop-optimizations \
        -Wmissing-declarations -Wcast-align -Wcast-qual \
        -Wchar-subscripts -Wconditionally-supported -Wconversion \
        -Wempty-body -Wfloat-equal \
        -Wformat-nonliteral -Wformat-security -Wformat-signedness \
        -Wformat=2 -Winline -Wlogical-op \
        -Wpacked -Wpointer-arith \
        -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion \
        -Wstrict-overflow=2 \
        -Wsuggest-attribute=noreturn \
        -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef \
        -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros \
        -Wno-missing-field-initializers -Wno-narrowing \
        -Wno-old-style-cast -Wno-varargs -Wstack-protector \
        -fstack-protector \
        -fstrict-overflow \
        -fno-omit-frame-pointer -Wlarger-than=8192 \
        -Wstack-usage=8192 -pie -fPIE -Werror=vla

#Sanitizers
SANITIZERS = -fsanitize=address,alignment,bool,bounds,enum,$\
            float-cast-overflow,float-divide-by-zero,$\
            integer-divide-by-zero,leak,nonnull-attribute,$\
            null,object-size,return,returns-nonnull-attribute,$\
            shift,signed-integer-overflow,undefined,$\
            unreachable,vla-bound

LDFLAGS = $(SANITIZERS) -pie -fPIE -lm

#Source files
SRCS = $(DIR)/main.c $(DIR)/double_operations.c $(DIR)/solve_equation.c $(DIR)/unit_tests.c $(DIR)/user_interaction.c $(DIR)/string_operations.c
OBJS = $(SRCS:.c=.o)
TARGET = square_solver
DOCFILE = ./documentation/html/index.html
BROWSER = firefox #might be set to "google-chrome"

# 256 Colors
COLOR_256 = \033[38;5;
BG_256 = \033[48;5;

# Colors for output
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
ORANGE     := \033[38;5;208m
PURPLE     := \033[38;5;93m
PINK       := \033[38;5;199m
LIME       := \033[38;5;118m
TEAL       := \033[38;5;30m
LAVENDER   := \033[38;5;183m
CORAL      := \033[38;5;203m
GOLD       := \033[38;5;220m
SILVER     := \033[38;5;7m
MAROON     := \033[38;5;88m
NC = \033[0m

#Main target
$(TARGET): $(OBJS)
	@echo "$(BLUE)Сборка ...$(NC)"
	@if $(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS); then \
                echo "$(GREEN)Сборка проведена успешно в $(TARGET)!$(NC)"; \
        else \
                echo "$(RED)Ошибка при сборке$(NC)"; \
				echo "$(YELLOW)Удаление объектных файлов...$(NC)"; \
                rm -f $(OBJS) *.gcno *.gcda; \
        fi
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Compile .c to .o
%.o: %.c
	@echo "$(BLUE)Компиляция ...$(NC)"
	$(CC) $(CFLAGS) $(SANITIZERS) -c $< -o $@
	@echo "$(GREEN)Компиляция проведена успешно!$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Clean build files
clean:
	@echo "$(BLUE)Очистка...$(NC)"
	rm -f $(OBJS) $(TARGET) *.gcno *.gcda
	@echo "$(GREEN)Очистка завершена!$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Run the program
run: $(TARGET)
	@echo "$(CYAN)=== ЗАПУСК ПРОГРАММЫ ===$(NC)"
	./$(TARGET)
	@echo "$(GREEN)=== ПРОГРАММА ЗАВЕРШЕНА ===$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Run with debugger
debug: $(TARGET)
	@echo "$(BLUE)=== ЗАПУСК ОТЛАДКИ ===$(NC)"
	gdb -q ./$(TARGET)
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

#Run tests
test: $(TARGET)
	@echo "$(MAGENTA)=== ЗАПУСК ТЕСТОВ ===$(NC)"
	./$(TARGET) --test $(TEST_PATH)
	@echo "$(MAGENTA)=== ТЕСТЫ ЗАВЕРШЕНЫ ===$(NC)"
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

doxy-docs:
	doxygen Doxyfile
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

doxy-open:
	$(BROWSER) $(DOCFILE)
	@echo "$(RED)ДЕЛАЙ COMMIT НА GITHUB!!!$(NC)"

help:
	@echo "$(BLUE)Доступные команды:$(NC)"
	@echo "	$(MAGENTA)Команды по работе с файлами проекта:$(NC)"
	@echo "		$(CYAN)make all$(NC) - собрать обычную версию программы"
	@echo "		$(CYAN)make test TEST_PATH=default$(NC) - собрать тестовую версию и запустить тесты.\n\
			Для тестирования своих тестов нужно указать путь до тестируемого файла в TEST_PATH.\n\
			По умолчанию открывает файл с авторскими тестами"
	@echo "		$(CYAN)make clean$(NC) - очистить сборочные файлы"
	@echo "	$(MAGENTA)Команды по работе с документацией:$(NC)"
	@echo "		$(CYAN)make doxy-docs$(NC) - сгенерировать документацию по проекту"
	@echo "		$(CYAN)make doxy-open$(NC) - открыть документацию по проекту"
	@echo "	$(MAGENTA)Другие команды:$(NC)"
	@echo "		$(CYAN)make help$(NC) - показать эту справку"

meow:
	@echo "	,-.       _,---._ __  / \\"
	@echo "	/  )    .-'       './ /   \\"
	@echo "	(  (   ,'            '/    /|"
	@echo "	\\  '-\"             '\\'   / |"
	@echo "	'.              ,  \\ \\ /  |"
	@echo "	/'.          ,'-'----Y   |"
	@echo "	(            ;        |   '"
	@echo "	|  ,-.    ,-'         |  /"
	@echo "	|  | (   |            | /"
	@echo "	)  |  \\  '.___________|/"
	@echo "	'--'   '--"
	@echo "$(LIME) Полторашка $(YELLOW)ищет $(CYAN)еду $(BLUE)у $(MAGENTA)вас $(PEACH)в $(BLACK)коробке. $(RED)ПОКОРМИТЕ ПОЛТОРАШКУ!!!"

meow-plus:
	@echo "                                            oOOOOOOOOOOOOOOoo.."
	@echo "                                             \"\"\"\"\"\"\"\"\"\"\"OOOOOOOOo."
	@echo "                                           ..oooooooo..    \`\"\"OOOOO."
	@echo "                                       .oOOOOOOOOOOOOOOOOo     OOOOO"
	@echo "                     ..ooOOOOOOo..oooOOOOOOOOOOOOOOOOOOOOOOoooOOOOO'"
	@echo "            .Oo...ooOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\"'"
	@echo "        .oooOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\"~~"
	@echo "          \\oOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO'"
	@echo "           OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOoOOOOOOOOOOOOOOO'"
	@echo "          __\\OO/\"    \"OOOOOOOOOOOOOOOOOOOO\`OOOOOOOOOOOOO\""
	@echo "            /|\\   .oOOooo- \`OOOOOOOO\"\"   .O\`OOOOOOOOOO'"
	@echo "  oO--.        .oOOOO\"~    .OOOOO'      QQOOO\`OOOOOOOOOo"
	@echo "  +o--o\`----QQOOO\"~       .OOOOO'                 \`OOOOO"
	@echo "                         .OOOO'                  QQQQO\""
	@echo "                       QQQQO\""
	@echo "$(MAROON)Свежепоглаженная $(LIME)Полторашка $(MINT)играется $(BLACK)с $(LAVENDER)обитателем $(TEAL)копейки"

make meow-plus-plus:
	@echo "$(TEAL)           M.                                         .:M"
	@echo "           MMMM.                                   .:MMMM"
	@echo "           MMMMMMMM                             .:MMMMMMM"
	@echo "           :MMHHHMMMMHMM.  .:MMMMMMMMM:.      .:MMHHMHMM:"
	@echo "            :MMHHIIIHMMMM.:MMHHHHIIIHHMMMM. .:MMHIHIIHHM:"
	@echo "             MMMHIIIIHHMMMIIHHMHHIIIIIHHMMMMMMHHHIIIIHHM:"
	@echo "             :MMHIIIIIHMMMMMMMHHIIIIIIHHHMMMMMHHII:::IHM."
	@echo "              MH:I:::IHHMMMMMHHII:::IIHHMMMHHHMMM:I:IHMM"
	@echo "              :MHI:HHIHMMHHIIHII::.::IIHMMHHIHHMMM::HMM:"
	@echo "               MI::HHMMIIM:IIHII::..::HM:MHHII:::IHHMM:"
	@echo "               MMMHII::..:::IHMMHHHMHHMMI:::...::IHM:"
	@echo "               :MHHI::....::::HMMMMMMHHI::.. ..:::HM:"
	@echo "                :MI:.:MH:.....:HMMMMHHMIHMMHHI:HH.:M"
	@echo "                M:.I..MHHHHHMMMIHMMMMHMMHHHHHMMH:.:M."
	@echo "                M:.H..H  I:HM:MHMHI:IM:I:MM::  MMM:M:"
	@echo "                :M:HM:.M I:MHMIIMMIIHM I:MM::.:MMI:M."
	@echo "                'M::MM:IMH:MMII MMHIMHI :M::IIHMM:MM"
	@echo "                 MH:HMMHIHMMMMMMHMMIMHIIHHHHIMMHHMM"
	@echo "                  MI:MMMMHI:::::IMM:MHI:::IMMMMHIM"
	@echo "                  :IMHIHMMMMMM:MMMMMHHHHMMMHI:M"
	@echo "                    HI:IMIHMMMM:MMMMMMHHHMI:.:M      ....."
	@echo "        ............M::..:HMMMMIMHIIHMMMMHII:M:::''''"
	@echo "            ....:::MHI:.:HMMMMMMMMHHHMHHI::M:::::::''''''"
	@echo "           ''   ...:MHI:.::MMHHHMHMIHMMMMHH.MI.........."
	@echo "              ''  ...MHI::.::MHHHHIHHMM:::IHM           '''"
	@echo "                 '  IMH.::..::HMMHMMMH::..:HM:"
	@echo "                   :M:.H.IHMIIII::IIMHMMM:H.MH"
	@echo "                    IMMMH:HI:MMIMI:IHI:HIMIHM:"
	@echo "                  .MMI:.HIHMIMI:IHIHMMHIHI:MIM."
	@echo "                 .MHI:::HHIIIIIHHI:IIII::::M:IM."
	@echo "                .MMHII:::IHIII::::::IIIIIIHMHIIM"
	@echo "                MHHHI::.:IHHII:::.:::IIIIHMHIIHM:"
	@echo "               MHHHII::..::MII::.. ..:IIIHHHII:IM."
	@echo "              .MHHII::....:MHII::.  .:IHHHI::IIHMM."
	@echo "              MMHHII::.....:IHMI:. ..:IHII::..:HHMM"
	@echo "              MHHII:::......:IIHI...:IHI::.....::HM:"
	@echo "             :MMH:::........ ...::..::....  ...:IHMM"
	@echo "             IMHIII:::..........     .........::IHMM."
	@echo "             :MHIII::::......          .......::IHMM:"
	@echo "              MHHIII::::...             ......::IHMM:"
	@echo "              IMHHIII:::...             .....::IIHMM,"
	@echo "              :MHHIII:::I:::...     ....:::I:::IIHMM"
	@echo "               MMHHIII::IHI:::...........:::IIH:IHMM"
	@echo "               :MMHHII:IIHHI::::::.....:::::IH:IHMIM"
	@echo "                MMMHHII:IIHHI:::::::::::::IHI:IIHM:M."
	@echo "                MMMHHIII::IHHII:::::::::IHI:IIIHMM:M:"
	@echo "                :MMHHHIII::IIIHHII::::IHI..IIIHHM:MHM"
	@echo "                :MMMHHII:..:::IHHMMHHHHI:IIIIHHMM:MIM"
	@echo "                .MMMMHHII::.:IHHMM:::IIIIIIHHHMM:MI.M"
	@echo "              .MMMMHHII::.:IHHMM:::IIIIIIHHHMM:MI.M"
	@echo "            .MMMMHHMHHII:::IHHMM:::IIIIIHHHHMM:MI.IM."
	@echo "           .MMHMMMHHHII::::IHHMM::I&&&IHHHHMM:MMH::IM."
	@echo "          .MMHHMHMHHII:::.::IHMM::IIIIHHHMMMM:MMH::IHM"
	@echo "          :MHIIIHMMHHHII:::IIHMM::IIIHHMMMMM::MMMMHHHMM."
	@echo "          MMHI:IIHMMHHHI::::IHMM:IIIIHHHMMMM:MMMHI::IHMM."
	@echo "          MMH:::IHMMHHHHI:::IHMM:IIIHHHHMMMM:MMHI:.:IHHMM."
	@echo "          :MHI:::IHMHMHHII::IHMM:IIIHHHMMMMM:MHH::.::IHHM:"
	@echo "          'MHHI::IHMMHMHHII:IHMM:IIHHHHMMMM:MMHI:...:IHHMM."
	@echo "           :MHII:IIHMHIHHIIIIHMM:IIHHHHMMMM:MHHI:...:IIHMM:"
	@echo "           'MHIII:IHHMIHHHIIHHHMM:IHHHMMMMM:MHHI:..::IIHHM:"
	@echo "            :MHHIIIHHMIIHHHIHHHMM:HHHHMMMMM:MHII::::IIIHHMM"
	@echo "             MHHIIIIHMMIHHHIIHHMM:HHHHMMMM:MMHHIIHIIIIIHHMM."
	@echo "             'MHHIIIHHMIIHHIIIHMM:HHHMMMMH:MHHMHII:IIIHHHMM:"
	@echo "              'MHHIIIHMMIHHHIHHMM:HHHMMMHH:MMIMMMHHHIIIHHMM:"
	@echo "               'MHHIIHHMIHHHHHMMM:HHHMMMH:MIMMMMMMMMMMHIHHM:"
	@echo "                'MHIIIHMMIHHHHHMM:HHHMMMH:IMMMMMHHIHHHMMHHM'"
	@echo "                 :MHHIIHMIHHHHHMM:HHHMMMM:MMHMMHIHMHI:IHHHM"
	@echo "                  MHHIIHM:HHHHHMM:HHHMMMM:MMMHIHHIHMM:HHIHM"
	@echo "                   MHHIHM:IHHHHMM:HHHHMM:MMHMIIHMIMMMHMHIM:"
	@echo "                   :MHIHMH:HHHHMM:HHHHMM:MMHIIHMIIHHMMHIHM:"
	@echo "                    MMHHMH:HHHHMM:HHHHMM:MHHIHMMIIIMMMIIHM'"
	@echo "                    'MMMMH:HHHHMM:HHHMM:MHHHIMMHIIII::IHM:"
	@echo "                     :MMHM:HHHHMM:HHHMM:MHIHIMMHHIIIIIHM:"
	@echo "                      MMMM:HHHHMM:HHHHM:MHHMIMMMHHHIHHM:MMMM."
	@echo "                      :MMM:IHHHMM:HHHMM:MHHMIIMMMHHMM:MMMMMMM:"
	@echo "                      :MMM:IHHHM:HHHHMM:MMHHHIHHMMM:MMMMMMMMMM"
	@echo "                       MHM:IHHHM:HHHMMM:MMHHHHIIIMMIIMMMMMMMMM"
	@echo "                       MHM:HHHHM:HHHMMM:HMMHHHHHHHHHMMMMMMMMM:"
	@echo "                    .MI:MM:MHHMM:MHMMHMHHMMMMHHHHHHHMMMMMMMMM'"
	@echo "                   :IM:MMIM:M:MM:MH:MM:MH:MMMMMHHHHHMMMMMMMM'"
	@echo "                   :IM:M:IM:M:HM:IMIHM:IMI:MMMMMHHHMMMMMM:'"
	@echo "                    'M:MHM:HM:MN:HMIHM::M'   '::MMMMMMM:'"
	@echo "                       'M'HMM'M''M''HM'I'"
	@echo "$(LIME)Полторашка $(MAGENTA)выучила $(BLUE)плюсы $(GREEN)и $(ORANGE)взломала $(GOLD)вас$(NC). $(RED)Теперь она знает, где вы храните все свои вкусняшки"
