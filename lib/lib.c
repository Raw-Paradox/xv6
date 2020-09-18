#include "lib/user.h"

static char base[MAXLINE];
static char *p = base;
//WARNING: Thread-unsafe
//donot preserve '\n'
int readline(int fd, char *buf) {
    int i;
    for (i = 0; (base + i) != p && base[i] != '\n'; i++)
        ;
    if ((base + i) != p) {
        memcpy(buf, base, i);
        buf[i] = '\0';
        char temp[MAXLINE];
        memcpy(temp, base + i + 1, (p - base) - (i + 1));
        memcpy(base, temp, (p - base) - (i + 1));
        p -= (i + 1);
        // printf("%d bytes in buffer\n", p - base);
        return 1;
    }
    int n;
    while (p != (base + MAXLINE) && (n = read(fd, p, MAXLINE - (p - base) - 1)) >= 0) {
        // printf("read %d bytes from file\n", n);
        if (n == 0) {  //EOF
            int r = p - base;
            memcpy(buf, base, r);
            buf[r] = '\0';
            p = base;
            return 0;
        }
        int i;
        for (i = 0; i < n && p[i] != '\n'; i++)
            ;
        // printf("(p - base):%d i:%d n:%d\n", (p - base), i, n);
        if (i < n) {
            p = p + i + 1;
            int r = p - base - 1;
            memcpy(buf, base, r);
            buf[r] = '\0';
            char temp[MAXLINE];
            memcpy(temp, p, n - i);
            memcpy(base, temp, n - i);
            p = base + (n - i) - 1;
            // printf("%d bytes in buffer\n", p - base);
            return 1;
        } else {
            p += n;
        }
    }
    p = base;
    return -1;
}