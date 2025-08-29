#ifndef FLAGS_H
#define FLAGS_H


enum flag_pos {
    Test,
    Version,
    Instruction,
    Meow,
    MeowPlus,
    MeowPlusPlus,
    Help
};

typedef struct {
    bool test_flag;
    bool version_flag;
    bool instruct_flag;
    bool meow_flag;
    bool meow_plus_flag;
    bool meow_plus_plus_flag;
    bool help_flag;
} Flags;

int write_flags(int argc, char *argv[]);

int is_flag_on(int flags, enum flag_pos pos);

#endif
