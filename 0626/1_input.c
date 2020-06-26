#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fifo = open("./myfifo", O_RDONLY);
    if (fifo < 0){
        perror("open");
        return -1;
    }

    char buf[BUFSIZ];
    while (1){
        int nRead = read(STDIN_FILENO, buf, sizeof(buf));
        if (nRead < 0){
            perror("read");
            break; //return -1;
        }
        write(STDOUT_FILENO, buf, nRead);

        nRead = read(fifo, buf, sizeof(buf));
        if (nRead < 0){
            perror("read");
            break;//return -1
        }
        write(STDOUT_FILENO, buf, nRead);
    }
    close(fifo);
    return 0;
}