#include "ls.h"
int main(int argc, char** argv) {
    printf("argc = %d\n", argc);
    if (argc > 6) {
        printf(
            "argument number must be less than 5 (only support -l, -a, -d, -R, i)\n");
        return 0;
    }
    const char* arg_set[] = {"-l", "-a", "-d", "-R", "-i"};
    for (int i = 0; i < argc; i++) {
        printf("%s\n", arg_set[i]);
    }
    file_info haha;
    get_file_info(argv[0], &haha);
    return 0;
}