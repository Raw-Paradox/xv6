#include "lib/user.h"
#include "kernel/param.h"

// debug-use
void print_argv(char** argv) {
    while (*argv) {
        printf("%s ", *argv);
        argv++;
    }
    printf("\n");
}

void runline(int argc, char** argv, char* line) {
    // printf("%s", line);
    if (line == 0 || strlen(line) == 0) {
        return;
    }
    char* start = line;
    while (*start == ' ') {
        start++;
    }
    char* p = start;
    while (*p != '\0') {
        if (*p == ' ') {
            *p = '\0';
            argv[argc] = (char*)malloc((p - start + 1) * sizeof(char));
            strcpy(argv[argc], start);
            argc++;
            do {
                p++;
            } while (*p == ' ');
            start = p;
            continue;
        }
        p++;
    }
    if (start != p) {
        argv[argc] = (char*)malloc((p - start + 1) * sizeof(char));
        strcpy(argv[argc], start);
        argc++;
    }
    argv[argc] = 0;
    // printf("ready to run:");
    // print_argv(argv);
    if (fork() == 0) {
        exec(argv[0], argv);
    }
    wait(0);
}

int main(int argc, char const* argv[]) {
    char* exec_argv[MAXARG];
    exec_argv[0] = "echo";
    int i;
    for (i = 0; i < argc - 1; i++) {
        exec_argv[i] = (char*)malloc((strlen(argv[i + 1]) + 1) * sizeof(char*));
        strcpy(exec_argv[i], argv[i + 1]);
    }
    i = i > 0 ? i : 1;
    int r;
    char buf[MAXLINE];
    buf[0] = '\0';
    while (1) {
        r = readline(0, buf);
        if (r > 0) {
            runline(i, exec_argv, buf);
        } else if (r == 0) {
            break;
        } else {
            fprintf(2, "xargs: line is too long\n");
            exit(1);
        }
    }
    exit(0);
}
