// 3_client.c
#if 0
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

int main() {
	// 플래그가 0인 경우, 해당 큐의 아이디가
	// 반환됩니다.
	int qid = msgget((key_t)7777, 0);
	if (qid == -1) {
		perror("msgget");
		return -1;
	}

	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define TEXT_SIZE	(128)
typedef struct {
	long mtype;
	long from;
	char text[TEXT_SIZE];
} msg_t;

int main() {
	int qid = msgget((key_t)7777, 0);
	if (qid == -1) {
		perror("msgget");
		return -1;
	}

	// 메시지 전송
	msg_t msg;
	while (1) {
		msg.mtype = 1;	// 서버 식별자
		msg.from = getpid();
		int nRead = read(0, msg.text, sizeof(msg.text));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		msg.text[nRead-1] = 0;	// delete new line
		if (msgsnd(qid, &msg, sizeof(msg_t) - sizeof(long), 0) == -1) {
			perror("msgsnd");
			return -1;
		}

		memset(msg.text, '\0', sizeof(msg.text));
		int nRcv = msgrcv(qid, &msg, sizeof(msg_t) - sizeof(long), getpid(), 0);
		if (nRcv == -1) {
			perror("msgrcv");
			return -1;
		}
		printf("%s\n", msg.text);
	}
	return 0;
}
#endif
