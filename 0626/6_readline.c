//
// Created by linux on 6/25/20.
//
//server

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    int fd = open("myfifo", O_RDONLY);
    if (fd < 0){
        perror("open");
        return -1;
    }

    char buf [BUFSIZ];
    int idx = 0;

    while (1){
        char chBuf;
        int nRead = read(fd, &chBuf, sizeof(chBuf));
        if (nRead < 0){
            perror("read");
            return -1;
        }

        buf[idx++] = chBuf;
        if (chBuf == '\n'){
            break;
        }
    }
    buf[idx] = 0;
    fputs(buf, stdout);
    close(fd);

    return 0;
}