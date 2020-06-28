//
// Created by linux on 6/25/20.
//

#include <stdio.h>
#include <unistd.h>

//read
//return : a number of bytes which is read
ssize_t readn(int fd, void *buf, size_t count){
    if (fd < 0 || buf == NULL || count <= 0){
        return -1;
    }

    int totalRead = 0;
    char * ptr = (char * )buf;

    while (totalRead < count){
        int nRead = read(fd, ptr, count - totalRead);

        if (nRead < 0){
            return -1;
        } else if (nRead == 0){
            return totalRead;
        }
        totalRead += nRead;
        ptr += nRead;
    }
    return totalRead;
}

//write
//return : a number of bytes which is written
ssize_t writen(int fd, const void * buf, size_t count){
    if (fd < 0 || buf == NULL || count <= 0){
        return -1;
    }

    int totalWrite = 0;
    const char * ptr = (const char * )buf;

    while (totalWrite < count){
        int nWrite = read(fd, ptr, count - totalWrite);

        if ( nWrite < 0){
            return -1;
        } else if ( nWrite == 0){
            return totalWrite;
        }
        totalWrite +=  nWrite;
        ptr +=  nWrite;
    }
    return totalWrite;
}