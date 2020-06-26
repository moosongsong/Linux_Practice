//
// Created by moosong on 6/25/20.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/param.h>

int main(){
//    int fifo = open("./myfifo", O_RDONLY);
//    if (fifo < 0){
//        perror("open");
//        return -1;
//    }
    int fd = open("./myfifo", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }
    int max_fd = fd;

    fd_set read_fds;    // is same as  'BIT read_fds[1024];'
    // unsigned int read_fds[32];
    FD_ZERO(&read_fds);  //    is same as
                        //    for (int i = 0; i < 32; ++i) {
                        //        read_fds[i]=0;
                        //    }
    FD_SET(0,&read_fds);
    FD_SET(fd, &read_fds);

    char buf[BUFSIZ];
    while (1){
        fd_set  temp_fds = read_fds;

        int result = select(max_fd+1, &temp_fds, NULL, NULL, NULL);
        //if event is happen, it will make 0, so we should prepare temp fds, and use.

        if (result < 0){
            perror("select");
            break;      //return -1;
        }

        for (int i = 0; i < (max_fd + 1); ++i) {
            if (FD_ISSET((int)i,&temp_fds)){
                //do input & output
                int nRead = read(i, buf, sizeof(buf));
                if (nRead<0){
                    perror("read");
                    break; // return -1;
                }
                write(1, buf, nRead);
            }
        }

//        int nRead = read(STDIN_FILENO, buf, sizeof(buf));
//        if (nRead < 0){
//            perror("read");
//            break; //return -1;
//        }
//        write(STDOUT_FILENO, buf, nRead);
//
//        nRead = read(fifo, buf, sizeof(buf));
//        if (nRead < 0){
//            perror("read");
//            break;//return -1
//        }
//        write(STDOUT_FILENO, buf, nRead);
    }
    close(fd);
    return 0;
}