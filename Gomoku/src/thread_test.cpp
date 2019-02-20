#include <iostream>

#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>


void * fun(void * i) {
	std::cout << "Hello in function" << std::endl;
	int a = 0;
	while (true) {
		a++;
	}
	return NULL;
}


int main_test() {

	const int thread_num = 4;
	pthread_t t[thread_num];

	for (int i = 0; i < thread_num; i++) {
		if (pthread_create(t + i, NULL, fun, NULL)) {
			std::cout << "Create p_thread failed" << std::endl;
		}
	}

	std::cout << "In main thread" << std::endl;

	for (int i = 0; i < thread_num; i++) {
		if (pthread_join(t[i], NULL)) {
			std::cout << "Pthread join failed" << std::endl;
		}
	}
	std::cout << "Exit" << std::endl;

	getchar();
	return 0;
}