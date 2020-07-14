// 3_msgq.c
#if 0
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

// step 1. 큐를 생성
int main() {
	int qid = msgget((key_t)7777, IPC_CREAT | 0666);
	if (qid == -1) {
		perror("msgget");
		return -1;
	}

	return 0;
}
#endif

#if 0
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

// step 2. 큐를 제거
int main() {
	int qid = msgget((key_t)7777, IPC_CREAT | 0666);
	if (qid == -1) {
		perror("msgget");
		return -1;
	}

	if (msgctl(qid, IPC_RMID, 0) == -1) {
		perror("msgctl");
		return -1;
	}
	return 0;
}
#endif

#if 1
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
// step 3. 메시지 수신

#define TEXT_SIZE	(128)
typedef struct {
	long mtype;
	long from;
	char text[TEXT_SIZE];
} msg_t;

int main() {
	int qid = msgget((key_t)7777, IPC_CREAT | 0666);
	if (qid == -1) {
		perror("msgget");
		return -1;
	}
	// ------------------------------------
	msg_t msg;
	while (1) {
		int nRcv = msgrcv(qid, &msg, sizeof(msg_t) - sizeof(long), 1, 0);
		if (nRcv == -1) {
			perror("msgrcv");
			return -1;
		}

		printf("%s\n", msg.text);
		msg.mtype = msg.from;
		if (msgsnd(qid, &msg, sizeof(msg_t) - sizeof(long), 0) == -1) {
			perror("msgsnd");
			return -1;
		}
	}
	// ------------------------------------
	if (msgctl(qid, IPC_RMID, 0) == -1) {
		perror("msgctl");
		return -1;
	}
	return 0;
}
#endif
