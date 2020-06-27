//cons : so difficult to be used by user
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

void __quit(const char *msg, int line) {
    char buf[BUFSIZ];
    sprintf(buf, "%s(%d)", msg, line);
    perror(buf);
    exit(1);
}
#define err_quit(msg)	__quit(msg, __LINE__)

int main() {
    int ssock = socket(PF_INET, SOCK_STREAM, 0);
    if (ssock == -1)
        err_quit("socket");

    struct sockaddr_in saddr = {0,};
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8080);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int value = 1;
    if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1){
        err_quit("setsockopt");
    }

    if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1){
        err_quit("bind");
    }

    if (listen(ssock, 10) == -1){
        err_quit("listen");
    }

    printf("[server] running...\n");

    // 서버 소켓 등록

    struct pollfd poll_fds[1024];
    int fd_cnt = 0;

    poll_fds[fd_cnt].fd = ssock;
    poll_fds[fd_cnt].events = POLLIN;
    ++fd_cnt;


    char buf[BUFSIZ];
    while (1) {
        int result = poll(poll_fds, fd_cnt, -1);
        //-1 means blocking, it will release after 136years.
        //input or output happen exclusively.

        if (result < 0){
            err_quit("poll");
            break;
        }
        else if (result == 0){          // timeout
            continue;
        }
        //if event is happen, that event's info will stored in pollfd structure

        for (int j = 0; j < result; ++j) {
            if (poll_fds[j].fd == ssock){
                struct sockaddr_in caddr = {0,};
                int caddr_len = sizeof(caddr);
                int csock = accept(ssock, (struct sockaddr *)&caddr, (unsigned int *)&caddr_len);
                if (csock < 0){
                    err_quit("accept");
                    break;
                }
                printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

                //register new client
                poll_fds[fd_cnt].fd = csock;
                poll_fds[fd_cnt].events = POLLIN;
                ++fd_cnt;
            } else {
                /*
                if (poll_fds[j].revents & POLLIN){
                    //TO DO
                } else if (poll_fds[j].revents & POLLOUT){
                    //TO DO
                }*/
                int nRead = read(poll_fds[j].fd, buf, sizeof(buf));
                if (nRead < 0) {
                    err_quit("read");
                    break;
                }
                else if (nRead == 0) {
                    close(poll_fds[j].fd);
                    poll_fds[j] = poll_fds[--fd_cnt];
                }
                else {
                    write(j, buf, nRead);
                    close(poll_fds[j].fd);
                    poll_fds[j] = poll_fds[--fd_cnt];
                }
            }
        }
    }	// end of while

    close(ssock);
    return 0;
}
/*
 * #include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <poll.h>

// 아래의 코드를 select를 사용한 코드로 변경해 보세요 :D

void __quit(const char *msg, int line) {
	char buf[BUFSIZ];
	sprintf(buf, "%s(%d)", msg, line);
	perror(buf);
	exit(1);
}
#define err_quit(msg)	__quit(msg, __LINE__)

int main() {
	int ssock = socket(PF_INET, SOCK_STREAM, 0);
	if (ssock == -1)
		err_quit("socket");

	struct sockaddr_in saddr = {0,};
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);


	int value = 1;
	if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value)) == -1)
		err_quit("setsockopt");

	if (bind(ssock, (struct sockaddr *)&saddr, sizeof(saddr)) == -1)
		err_quit("bind");

	if (listen(ssock, 10) == -1)
		err_quit("listen");
	printf("[server] running...\n");

	// 서버 소켓 등록
	// struct pollfd {
	//    int   fd;         /* file descriptor */
//    short events;     /* requested events */
//    short revents;    /* returned events */
//// };
//struct pollfd poll_fds[1024];	// poll: 2K
//int fd_cnt = 0;
//
//poll_fds[fd_cnt].fd = ssock;
//poll_fds[fd_cnt].events = POLLIN;
//++fd_cnt;
//
//char buf[BUFSIZ];
//while (1) {
//int ret = poll(poll_fds, fd_cnt, -1);
//if (ret < 0)
//err_quit("poll");
//else if (ret == 0)	// timeout
//continue;
//
//for (int i = 0; i < fd_cnt; i++) {
//if (poll_fds[i].revents & POLLIN) {
//if (poll_fds[i].fd == ssock) {
//struct sockaddr_in caddr = {0,};
//int caddr_len = sizeof(caddr);
//int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
//if (csock < 0)
//err_quit("accept");
//printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));
//
//// 새로운 클라이언트를 등록합니다.
//poll_fds[fd_cnt].fd = csock;
//poll_fds[fd_cnt].events = POLLIN;
//++fd_cnt;
//}
//else {
//int nRead = read(poll_fds[i].fd, buf, sizeof(buf));
//write(1, buf, nRead);
//if (nRead < 0) {
//err_quit("read");
//}
//else if (nRead == 0) {
//close(poll_fds[i].fd);
//poll_fds[i] = poll_fds[--fd_cnt];
//}
//else {
//write(poll_fds[i].fd, buf, nRead);
//close(poll_fds[i].fd);
//poll_fds[i] = poll_fds[--fd_cnt];
//}
//}
//}
//}
//}
//
//close(ssock);
//return 0;
//}
//
//
//*/