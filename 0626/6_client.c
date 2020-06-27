//
// Created by linux on 6/25/20.
//
//client

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    int fd = open("myfifo", O_WRONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    getchar();
    write(fd, "he", 2);
    getchar();
    write(fd, "ll", 2);
    getchar();
    write(fd, "o\n", 1);

    close(fd);

    return 0;
}