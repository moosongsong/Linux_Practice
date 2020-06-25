
#if 0
#include <stdio.h>

int main() {
	unsigned int x = 0x1;	// 00 00 00 01
	unsigned char *p = (unsigned char *)&x;
	if (*p == 1)
		printf("little endian\n");
	else
		printf("big endian\n");

	return 0;
}
#endif

#if 0
#include <stdio.h>

int is_bigendian() {
	unsigned int x = 0x1;	// 00 00 00 01
	unsigned char *p = (unsigned char *)&x;
	return (*p == 0);
}

// 리터럴에 대하여 주소 연산자를 사용할 수 없습니다.
// #define IS_BIGENDIAN()	(*((unsigned char*)&0x1) == 0)

static const unsigned int __ENDIAN_VALUE = 0x1;
#define IS_BIGENDIAN()	(*((unsigned char*)&__ENDIAN_VALUE) == 0)

// C99: compond literal

int main() {
	if (IS_BIGENDIAN()) // if (is_bigendian())
		printf("big endian\n");
	else
		printf("little endian\n");

	return 0;
}
#endif


#if 0
#include <stdio.h>
// C99: compound literal(이름이 없는 임시 객체)

struct Point {
	int x, y;
};

int main() {
	// 1;					// OK
	// { 1, 2 };	// ERROR

	(int[]){ 1, 2 };
	(struct Point){ 1, 2 };

	return 0;
}
#endif

#if 0
#include <stdio.h>
#define IS_BIGENDIAN()	\
	(((union {unsigned int i; unsigned char c; }){1}).c == 0)

int main() {
	if (IS_BIGENDIAN())
		printf("big endina\n");
	else
		printf("little endian\n");
}
#endif


#if 0
#include <stdio.h>

int main() {
#if __BYTE_ORDER == __LITTLE_ENDIAN
	printf("littlen endian\n");
#else
	printf("big endian\n");
#endif

	return 0;
}
#endif



#if 0

#include <stdio.h>
#define IS_BIGENDIAN()	\
	(((union {unsigned int i; unsigned char c; }){1}).c == 0)

void printMemory(void *value, size_t size) {
	unsigned char *p = (unsigned char *)value;
	for (size_t i = 0; i < size; i++)
		printf("[%X]", p[i]);
	printf("\n");
}

// unsigned int toBigEndian(unsigned int value) {
// 	if (IS_BIGENDIAN())
// 		return value;
// 	unsigned char *src = (unsigned char *)&value;
// 
// 	unsigned int data = 0;
// 	unsigned char *dst = (unsigned char *)&data;
// 	dst[0] = src[3];
// 	dst[1] = src[2];
// 	dst[2] = src[1];
// 	dst[3] = src[0];
// 
// 	return data;
// }

unsigned int toBigEndian(unsigned int value) {
	if (IS_BIGENDIAN())
		return value;
	return (value & 0xff000000) >> 24 |
			   (value & 0xff0000) >> 8 |
			   (value & 0xff00) << 8 |
			   (value & 0xff) << 24;
}

int main() {
	unsigned int data = 0x12345678;
	printMemory(&data, sizeof(data));	// [78][56][34][12]

	// 아래의 함수를 구현해 보세요 :D
	data = toBigEndian(data);
	printMemory(&data, sizeof(data));	// [12][34][56][78]

	return 0;
}

#endif



#if 1

#include <arpa/inet.h>	// htons, htonl
#include <stdio.h>
#define IS_BIGENDIAN()	\
	(((union {unsigned int i; unsigned char c; }){1}).c == 0)

void printMemory(void *value, size_t size) {
	unsigned char *p = (unsigned char *)value;
	for (size_t i = 0; i < size; i++)
		printf("[%X]", p[i]);
	printf("\n");
}

int main() {
	unsigned int data = 0x12345678;
	printMemory(&data, sizeof(data));	// [78][56][34][12]

	// 아래의 함수를 구현해 보세요 :D
	data = htonl(data);	// data = toBigEndian(data);
	//       ^--- host to network long(4byte)
	
	// htons: host to network short(2byte)
	// ntohs, ntohl, ...

	printMemory(&data, sizeof(data));	// [12][34][56][78]

	return 0;
}

#endif
