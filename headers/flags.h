#ifndef FLAGS_H
#define FLAGS_H


enum flag_pos {
    Test = 0,
    Version = 1,
    Instruction = 2,
    Meow = 3,
    MeowPlus = 4,
    MeowPlusPlus = 5,
    Help = 6,
    SINGLE = 7,
    FILE_INPUT = 8
};

enum flags_status {
    FinishProgram = 0,
    ExecuteMain = 1,
    FlagsRed = 124
};

typedef struct {
    int Flags;
    char *TestFilePath;
    char *InstructionPath;
} FlagsInfo;

int read_flags(int argc, char *argv[], FlagsInfo *information);

int is_flag_on(int flags, enum flag_pos pos);

int execute_flags(int argc, char *argv[], FlagsInfo *information);

#endif
