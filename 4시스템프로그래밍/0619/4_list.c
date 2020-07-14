// 4_list.c
#if 0
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

// ./a.out 0619
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		return -1;
	}
	--argc, ++argv;

	// 1. 디렉터리 열기
	DIR *dir = opendir(*argv);	// int fd = open(*argv, O_RDONLY);
	if (dir == NULL) {				 	// if (fd < 0) {
		perror("opendir");				//   perror("open");
		return -1;								//   return -1;
	}														// }

	// 2. 디렉터리 내용 읽기
																		// char buf[BUFSIZ];
	struct dirent *p = readdir(dir);	// read(buf, sizeof(buf), fd);
	if (p) printf("%s\n", p->d_name);

	// 3. 디렉터리 닫기
	if (closedir(dir) == -1) {				// close(fd);
		perror("closedir");
		return -1;
	}

	return 0;
}

#endif

#if 0
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>

// ./a.out 0619
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		return -1;
	}
	--argc, ++argv;

	DIR *dir = opendir(*argv);
	if (dir == NULL) {				 	
		perror("opendir");		
		return -1;								
	}											

	// ----------------------------------------------------
	while (1) {
		errno = 0;
		struct dirent *p = readdir(dir);	
		if (p == NULL) {	// EOF or ERROR
			if (errno != 0) {
				perror("readdir");
				return -1;
			}
			break;
		}

		printf("%s\n", p->d_name);
	}
	// ----------------------------------------------------


	if (closedir(dir) == -1) {		
		perror("closedir");
		return -1;
	}

	return 0;
}

#endif

#if 0
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// 하위 디렉터리 탐색을 위한 함수를 구현합니다.
int listDir(const char *dname) {
	if (dname == NULL || strlen(dname) == 0) {
		fprintf(stderr, "listDir: argument is wrong\n");
		return -1;
	}

	// 1. 해당 디렉터리로 이동
	if (chdir(dname) == -1) {
		perror("chdir");
		return -1;
	}

	// 2. 해당 디렉터리 경로 출력
	char curPath[256];
	if (getcwd(curPath, sizeof(curPath)) == NULL) {
		perror("getcwd");
		return -1;
	}
	printf("\n%s:\n", curPath);

	// 3. 해당 디렉터리를 오픈
	DIR *dir = opendir(".");
	if (dir == NULL) {				 	
		perror("opendir");		
		return -1;								
	}											

	// 4. 디렉터리 안의 내용을 출력
	while (1) {
		errno = 0;
		struct dirent *p = readdir(dir);	
		if (p == NULL) {	// EOF or ERROR
			if (errno != 0) {
				perror("readdir");
				return -1;
			}
			break;
		}

		if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
			printf("%s\n", p->d_name);

			if (p->d_type == DT_DIR) {	// 현재 파일이 디렉터리인 경우, 재귀 호출
				if (listDir(p->d_name) == -1) 
					break;
			}
		}
	}

	// 5. 현재 디렉터리를 닫고 상위 디렉터리로 이동
	if (closedir(dir) == -1) {		
		perror("closedir");
		return -1;
	}

	if (chdir("..") == -1) {
		perror("chdir");
		exit(1);
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		return -1;
	}
	--argc, ++argv;
	listDir(*argv);
	return 0;
}

#endif

#if 0
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

typedef struct Node {
	char dname[256];
	struct Node *next;
} Node;

int insert(Node *head, const char *dname) {
	if (head == NULL || dname == NULL) {
		fprintf(stderr, "insert: argument is null\n");
		return -1;
	}
	
	Node *node = calloc(1, sizeof(Node));
	if (node == NULL) {
		perror("insert");
		return -1;
	}
	strcpy(node->dname, dname);

	node->next = head->next;
	head->next = node;
	return 0;
}

int listDir(const char *dname) {
	if (dname == NULL || strlen(dname) == 0) {
		fprintf(stderr, "listDir: argument is wrong\n");
		return -1;
	}

	// 1. 해당 디렉터리로 이동
	if (chdir(dname) == -1) {
		perror("chdir");
		return -1;
	}

	// 2. 해당 디렉터리 경로 출력
	char curPath[256];
	if (getcwd(curPath, sizeof(curPath)) == NULL) {
		perror("getcwd");
		return -1;
	}
	printf("\n%s:\n", curPath);

	// 3. 해당 디렉터리를 오픈
	DIR *dir = opendir(".");
	if (dir == NULL) {				 	
		perror("opendir");		
		return -1;								
	}											

	// 4. 디렉터리 안의 내용을 출력
	Node head = {0,};	// 단순 연결 리스트의 더미 헤드
	while (1) {
		errno = 0;
		struct dirent *p = readdir(dir);	
		if (p == NULL) {	// EOF or ERROR
			if (errno != 0) {
				perror("readdir");
				return -1;
			}
			break;
		}

		if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
			printf("%s\n", p->d_name);

			if (p->d_type == DT_DIR) {	// 현재 파일이 디렉터리인 경우, 재귀 호출
				insert(&head, p->d_name);	// if (listDir(p->d_name) == -1) break;
			}
		}
	}

	// 5. 하위 디렉터리 순회
	while (head.next != NULL) {
		Node *target = head.next;
		head.next = target->next;
		
		if (listDir(target->dname) == -1)
			exit(1);
		free(target);
	}


	// 6. 현재 디렉터리를 닫고 상위 디렉터리로 이동
	if (closedir(dir) == -1) {		
		perror("closedir");
		return -1;
	}

	if (chdir("..") == -1) {
		perror("chdir");
		exit(1);
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		return -1;
	}
	--argc, ++argv;
	listDir(*argv);
	return 0;
}

#endif

#if 1
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int listDir(const char *dname) {
	if (dname == NULL || strlen(dname) == 0) {
		fprintf(stderr, "listDir: argument is wrong\n");
		return -1;
	}

	// 1. 해당 디렉터리로 이동
	if (chdir(dname) == -1) {
		perror("chdir");
		return -1;
	}

	// 2. 해당 디렉터리 경로 출력
	char curPath[256];
	if (getcwd(curPath, sizeof(curPath)) == NULL) {
		perror("getcwd");
		return -1;
	}
	printf("\n%s:\n", curPath);

	// 3. 해당 디렉터리를 오픈
	DIR *dir = opendir(".");
	if (dir == NULL) {				 	
		perror("opendir");		
		return -1;								
	}											

	// 4. 디렉터리 안의 내용을 출력
	while (1) {
		errno = 0;
		struct dirent *p = readdir(dir);	
		if (p == NULL) {	// EOF or ERROR
			if (errno != 0) {
				perror("readdir");
				return -1;
			}
			break;
		}

		if (strcmp(p->d_name, ".") && strcmp(p->d_name, ".."))
			printf("%s\n", p->d_name);
	}

	// 5. 하위 디렉터리 순회
	rewinddir(dir);
	while (1) {
		struct dirent *p = readdir(dir);	
		if (p == NULL) {	// EOF or ERROR
			if (errno != 0) {
				perror("readdir");
				return -1;
			}
			break;
		}

		if (p->d_type ==DT_DIR) {
			if (strcmp(p->d_name, ".") && strcmp(p->d_name, "..")) {
				if (listDir(p->d_name) == -1) 
					exit(1);
			}
		}
	}

	// 6. 현재 디렉터리를 닫고 상위 디렉터리로 이동
	if (closedir(dir) == -1) {		
		perror("closedir");
		return -1;
	}

	if (chdir("..") == -1) {
		perror("chdir");
		exit(1);
	}

	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s DIRECTORY\n", *argv);
		return -1;
	}
	--argc, ++argv;
	listDir(*argv);
	return 0;
}

#endif
