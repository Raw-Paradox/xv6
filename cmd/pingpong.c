#include "lib/user.h"
// #include <semaphore.h>

int main(int argc, char const *argv[]) {
    int pipe_fds[2];
    pipe(pipe_fds);
    char ph;
    // sem_t* sem = sem_open("pingpong", O_CREAT);
    if (fork() == 0) {
        read(pipe_fds[0], &ph, 1);
        printf("%d: received ping\n", getpid());
        write(pipe_fds[1], "\n", 1);
        exit(0);
    }
    write(pipe_fds[1], "\n", 1);
    wait(0);
    read(pipe_fds[0], &ph, 1);
    printf("%d: received pong\n", getpid());
    exit(0);
}
