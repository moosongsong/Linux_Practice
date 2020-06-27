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

    char buf[BUFSIZ];
    int nRead = read(STDIN_FILENO, buf, sizeof(buf));
    if (nRead < 0) {
        perror("read");
        return -1;
    }
    write(fd, buf, nRead);
    close(fd);

    return 0;
}
