// A_mmap.c
// 사람의 이름과 나이를 저장하는 코드를 구현해 봅시다.
#if 0
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

typedef struct Person {
	char name[32];
	int age;
} Person;

int writePerson(const char *fname, Person *person) {
	if (fname == NULL || person == NULL) {
		fprintf(stderr, "writePerson: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	int nWritten = write(fd, person, sizeof(Person));
	if (nWritten < 0) {
		perror("write");
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}

int dumpFile(const char *fname) {
	if (fname == NULL) {
		fprintf(stderr, "dumpFile: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	Person buf;
	while (1) {
		ssize_t nRead = read(fd, &buf, sizeof(buf));
		if (nRead < 0) {
			perror("read");
			return -1;
		}
		else if (nRead == 0) {
			break;
		}
		else {
			printf("name: %s, age: %d\n", buf.name, buf.age);
		}
	}
	close(fd);
	return 0;

}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	Person arr[] = {
		{"daniel", 20}, {"susan", 30}, {"andrew", 40}, {"monica", 50}
	};

	for (int i = 0; i < 4; i++)
		writePerson(*argv, &arr[i]);
	dumpFile(*argv);

	return 0;
}
#endif


#if 1
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>

// 이전 코드의 단점은 파일 입출력에 대하여 버퍼 입출력과 빈번한 함수 호출로 인해
// 성능이 떨어진다는 단점이 있습니다. 이를 해결하기 위해 메모리 매핑을 도입합니다.
// mmap

typedef struct Person {
	char name[32];
	int age;
} Person;

long getFileSize(int fd) {
	if (fd < 0) {
		fprintf(stderr, "getFileSize: fd is wrong\n");
		return -1;
	}

	off_t oldPos = lseek(fd, 0, SEEK_CUR);
	if (oldPos == -1) {
		perror("lseek");
		return -1;
	}

	off_t fsize = lseek(fd, 0, SEEK_END);
	if (fsize == -1) {
		perror("fseek");
		return -1;
	}

	if (lseek(fd, oldPos, SEEK_SET) == -1) {
		perror("lseek");
		exit(-1);
	}
	return fsize;
}

int writePerson(const char *fname, Person *person) {
	if (fname == NULL || person == NULL) {
		fprintf(stderr, "writePerson: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	int nWritten = write(fd, person, sizeof(Person));
	if (nWritten < 0) {
		perror("write");
		close(fd);
		return -1;
	}

	close(fd);
	return 0;
}

int dumpFile(const char *fname) {
	if (fname == NULL) {
		fprintf(stderr, "dumpFile: argument is null\n");
		return -1;
	}

	int fd = open(fname, O_RDONLY);
	if (fd < 0) {
		perror("open");
		return -1;
	}

	long fsize = getFileSize(fd);
	if (fsize < 0) {
		close(fd);
		return -1;
	}
	
	// void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
	Person* p = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -1;
	}

	for (int i = 0; i < (fsize/sizeof(Person)); i++) {
		printf("name: %s, age: %d\n", p[i].name, p[i].age);
	}

	if (munmap(p, fsize) == -1) {
		perror("munmap");
		exit(-1);
	}

	close(fd);
	return 0;

}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s FILE\n", *argv);
		return -1;
	}
	--argc, ++argv;

	Person arr[] = {
		{"daniel", 20}, {"susan", 30}, {"andrew", 40}, {"monica", 50}
	};

	for (int i = 0; i < 4; i++)
		writePerson(*argv, &arr[i]);
	dumpFile(*argv);

	return 0;
}
#endif












