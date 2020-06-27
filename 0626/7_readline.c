//
// Created by linux on 6/25/20.
//
//server

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int readLine(int fd, void *buf, size_t size){
    if (fd < 0 || buf == NULL || size == 0){
        return -1;
    }

    int totalRead = 0;
    char *ptr = (char*)buf;
    while (1){
        char chBuf;
        int nRead = read(fd, &chBuf, sizeof(chBuf));
        if (nRead < 0){
            perror("read");
            return -1;
        } else if (nRead == 0){
            //EOF
            if (totalRead == 0){
                return 0;
            }
            break;
        } else{
            if (totalRead < size-1){
                *ptr++ = chBuf;
                ++totalRead;
            }
            if (chBuf == '\n'){
                break;
            }
        }
    }
    *ptr = '\0';
    return totalRead;
}

int main(){
    int fd = open("myfifo", O_RDONLY);
    if (fd < 0){
        perror("open");
        return -1;
    }

    char buf [BUFSIZ];
    int idx = 0;

    int nRead = readLine(fd, buf, sizeof(buf));
    if (nRead < 0){
        fprintf(stderr, "readLine error\n");
        return -1;
    }

    fputs(buf, stdout);
    close(fd);

    return 0;
}