#include "user/user.h"

int main(int argc, char const *argv[]) {
    char buf[MAXLINE];
    int n;
    while ((n = readline(0, buf)) > 0) {
        printf("%d:%s\n", n, buf);
    }
    printf("%d:%s\n", n, buf);
    exit(0);
}
