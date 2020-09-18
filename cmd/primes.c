#include "lib/user.h"

int main(int argc, char const *argv[]) {
    int pipeline[2];
    pipe(pipeline);
    int r_fd = pipeline[0];
    int w_fd = pipeline[1];
    if (fork() == 0) {  //the first child process
        while (1) {
            r_fd = pipeline[0];  //read from parent
            close(w_fd);         //close parent write fd
            pipe(pipeline);
            w_fd = pipeline[1];  //write to child
            if (fork() == 0) {   //only child continue the loop
                continue;
            } else {
                int base, recv;
                if (read(r_fd, &base, 4) > 0) {
                    printf("prime %d\n", base);
                    while (read(r_fd, &recv, 4) > 0) {
                        if (recv % base != 0) {  //drop it!
                            write(w_fd, &recv, 4);
                        }
                    }
                }
                close(r_fd);
                close(w_fd);
                wait(0);
                exit(0);
            }
        }
    }
    //ancestor!
    close(r_fd);                    //the ancestor donot need read
    for (int i = 2; i < 36; i++) {  //write source to child
        write(w_fd, &i, 4);
    }
    close(w_fd);
    wait(0);
    exit(0);
}
