
#if 0
#include <pthread.h>
#include <stdio.h>

int lock = 0;	// key

int cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		while (lock != 0);
		lock = 1;
		//----------------------
		++cnt;
		//----------------------
		lock = 0;
	}
	return NULL;
}

int main() {
	pthread_t tid[2];
	for (int i = 0; i < 2; i++)
		pthread_create(&tid[i], NULL, thread_main, NULL);

	for (int i = 0; i < 2; i++)
		pthread_join(tid[i], NULL);

	printf("%d\n", cnt);
	return 0;
}
#endif


#if 1
#include <pthread.h>
#include <stdio.h>
#include <stdint.h>

// old_value와 *ptr의 값이 같다면 *ptr의 값을 new_value로 설정하고
// 0(성공)을 반환한다. 그렇지 않으면 1(실패)을 반환
int __bionic_cmpxchg(int32_t old_value, int32_t new_value, volatile int32_t* ptr) {
	int32_t prev;
	__asm__ __volatile__("lock; cmpxchgl %1, %2"
			: "=a" (prev)
			: "q" (new_value), "m" (*ptr), "0" (old_value)
			: "memory");
	return prev != old_value;
}

int32_t __bionic_atomic_dec(volatile int32_t* ptr) {
	int increment = -1;
	__asm__ __volatile__("lock; xaddl %0, %1"
			: "+r" (increment), "+m" (*ptr)
			: : "memory");
	return increment;
}

void spin_lock(int32_t *lock) { while(__bionic_cmpxchg(0, 1, lock)); }
void spin_unlock(int32_t *lock) { __bionic_atomic_dec(lock);	}

int lock = 0;	
int cnt = 0;
void *thread_main(void *arg) {
	for (int i = 0; i < 50000000; i++) {
		// while (lock != 0);
		// lock = 1;
		spin_lock(&lock);	// while(__bionic_cmpxchg(0, 1, &lock));
		//----------------------
		++cnt;
		//----------------------
		spin_unlock(&lock);	// __bionic_atomic_dec(&lock);	// lock = 0;
	}
	return NULL;
}

int main() {
	pthread_t tid[2];
	for (int i = 0; i < 2; i++)
		pthread_create(&tid[i], NULL, thread_main, NULL);

	for (int i = 0; i < 2; i++)
		pthread_join(tid[i], NULL);

	printf("%d\n", cnt);
	return 0;
}
#endif
