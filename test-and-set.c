#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct
{
	int *lock;
} my_Lock;

// 2.1

int test_and_set(my_Lock my_lock)
{
	int result;
	asm(
			"movl $1, %%eax;"
			"xchg %%eax, (%1);"
			"movl %%eax, %0;"
			:"=&r"(result)
			:"r"(my_lock.lock)
			:"%eax");
	return result;
}

void my_init_function(my_Lock *my_lock_ptr)
{
	my_lock_ptr->lock = (int *)malloc(sizeof(int));
	*(my_lock_ptr->lock) = 0;
}

void my_lock_function(my_Lock *my_lock_ptr)
{
	while (test_and_set(*my_lock_ptr))
	{
		// wait
	}
}

void my_unlock_function(my_Lock *my_lock_ptr)
{
	asm(
		"movl $0, %%eax;"
		"xchg %%eax, (%0);"
		:
		: "r"(my_lock_ptr->lock)
		: "%eax");
}

void my_destroy_function(my_Lock *my_lock_ptr)
{
	free(my_lock_ptr->lock);
}

// 2.4

typedef struct
{
	my_Lock *lock_ptr;
	int *pointer;
} my_Sem;

void my_sem_init_function(my_Sem *my_sem_ptr, int value)
{
	my_sem_ptr->pointer = (int *)malloc(sizeof(int));
	*(my_sem_ptr->pointer) = value;

	my_sem_ptr->lock_ptr = (my_Lock *)malloc(sizeof(my_Lock));
}

void my_sem_wait_function(my_Sem *my_sem_ptr)
{
	bool loop = true;
	while (loop)
	{
		my_lock_function(my_sem_ptr->lock_ptr);
		if (*(my_sem_ptr->pointer) > 0)
		{
			loop = false;
			*(my_sem_ptr->pointer) -= 1;
		}
		my_unlock_function(my_sem_ptr->lock_ptr);
	}
}

void my_sem_post_function(my_Sem *my_sem_ptr)
{
	my_lock_function(my_sem_ptr->lock_ptr);
	*(my_sem_ptr->pointer) += 1;
	my_unlock_function(my_sem_ptr->lock_ptr);
}

void my_sem_destroy_function(my_Sem *my_sem_ptr)
{
	my_destroy_function(my_sem_ptr->lock_ptr);
	free(my_sem_ptr->lock_ptr);
	free(my_sem_ptr->pointer);
}
