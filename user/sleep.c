#include "user/user.h"

int main(int argc, char const *argv[]) {
    if (argc < 2) {
        fprintf(2, "Usage: sleep ticks...\n");
        exit(1);
    }
    if (sleep(atoi(argv[1])) < 0) {
        fprintf(2, "sleep: some error occurred in sleeping\n");
        exit(1);
    }
    exit(0);
}
