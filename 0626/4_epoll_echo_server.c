//
// Created by linux on 6/25/20.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>

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
    // };
    int efd = epoll_create(1);
    if (efd == -1){
        err_quit("epoll_create");
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = ssock;
    if(epoll_ctl(efd,EPOLL_CTL_ADD,ssock,&event)==-1){
        err_quit("epoll_ctl");
    }

    struct epoll_event events[128];
    char buf[BUFSIZ];
    while (1) {

        int nEvent = epoll_wait(efd, events, 128,-1);
        if (nEvent < 0){
            err_quit("epoll_wait");
            break;
        } else if (nEvent == 0){
            continue;
        }

        for (int j = 0; j < nEvent; ++j) {
            if (events[j].data.fd == ssock){
                struct sockaddr_in caddr = {0,};
                int caddr_len = sizeof(caddr);
                int csock = accept(ssock, (struct sockaddr *)&caddr, &caddr_len);
                if (csock < 0)
                    err_quit("accept");
                printf("[server] %s is connected...\n", inet_ntoa(caddr.sin_addr));

                // 새로운 클라이언트를 등록합니다.
                event.events = EPOLLIN;
                event.data.fd = csock;
                if (epoll_ctl(efd, EPOLL_CTL_ADD, csock, &event)==-1){
                    err_quit("epoll ctr");
                    break;
                } else{
                    continue;
                }
            }

            int nRead = read(events[j].data.fd, buf, sizeof(buf));
            if (nRead < 0){
                err_quit("read");
                break;
            } else if (nRead == 0){
                close(events[j].data.fd);
                if (epoll_ctl(efd, EPOLL_CTL_DEL, events[j].data.fd, NULL) == -1){
                    err_quit("epoll ctl");
                }
            } else{
                write(events[j].data.fd, buf, nRead);
                if (epoll_ctl(efd, EPOLL_CTL_DEL, events[j].data.fd, NULL)==-1){
                    err_quit("epoll ctl");
                }
            }

        }
    }

    close(ssock);
    return 0;
}

