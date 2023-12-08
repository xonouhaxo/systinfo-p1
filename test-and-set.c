#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int *lock;
}my_Lock;


int test_and_set(my_Lock *my_Lock){
	int result;
	asm(
		"movl $1, %%eax;"
		"xchg %%eax, (%1);"
		"movl %%eax, %0;"
		
		:"=&r"(result)
		:"r"(my_Lock->lock)
		:"%eax"
	);
	return result;
}

void unlock	(my_Lock *my_Lock){
	my_Lock->lock = 0;
}

void main(){ //pas sure de ça c'est copilot qui l'a écrit 
	my_Lock *my_Lock = malloc(sizeof(my_Lock));
	my_Lock->lock = 0;
	
	printf("lock = %d\n", my_Lock->lock);
	test_and_set(my_Lock);
	printf("lock = %d\n", my_Lock->lock);
	unlock(my_Lock);
	printf("lock = %d\n", my_Lock->lock);
}
