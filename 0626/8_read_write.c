//
// Created by linux on 6/25/20.
//

#include <stdio.h>

//read
//return : a number of bytes which is read
ssize_t readn(int fd, void *buf, size_t count){
    if (fd < 0 || buf == NULL || count <= 0){
        return -1;
    }

}

//write
//return : a number of bytes which is written
ssize_t writen(int fd, const void * buf, size_t count){
    
}