#include <stdlib.h>
#include <stdio.h>
#include <threads.h>

#include "my_stack.h"
#include "model-assert.h"

static int procs = 4;
static stack_t *stack;
static thrd_t *threads;
static int num_threads;

unsigned int idx1, idx2;
unsigned int a, b;


atomic_int x[3];

int get_thread_num()
{
	thrd_t curr = thrd_current();
	int i;
	for (i = 0; i < num_threads; i++)
		if (curr.priv == threads[i].priv)
			return i;
	MODEL_ASSERT(0);
	return -1;
}

static void main_task(void *param)
{
	unsigned int val;
	int pid = *((int *)param);

	idx2 = pop(stack);
	if (idx2 != 0) {
		b = atomic_load_explicit(&x[idx2], relaxed);
		printf("b: %d\n", b);
	}

	if (pid % 4 == 0) {
		atomic_store_explicit(&x[1], 17, relaxed);
		push(stack, 1);
	} else if (pid % 4 == 1) {
		atomic_store_explicit(&x[2], 37, relaxed);
		push(stack, 2);
	} else if (pid % 4 == 2) {/*
		idx1 = pop(stack);
		if (idx1 != 0) {
			a = atomic_load_explicit(&x[idx1], relaxed);
			printf("a: %d\n", a);
		}*/
	} else {/*
		idx2 = pop(stack);
		if (idx2 != 0) {
			b = atomic_load_explicit(&x[idx2], relaxed);
			printf("b: %d\n", b);
		}*/
	}
}

int user_main(int argc, char **argv)
{
	int i;
	int *param;
	unsigned int in_sum = 0, out_sum = 0;

	atomic_init(&x[1], 0);
	atomic_init(&x[2], 0);

	stack = (stack_t*) calloc(1, sizeof(*stack));

	num_threads = procs;
	threads = (thrd_t*) malloc(num_threads * sizeof(thrd_t));
	param = (int*) malloc(num_threads * sizeof(*param));

	init_stack(stack, num_threads);
	
	for (i = 0; i < num_threads; i++) {
		param[i] = i;
		thrd_create(&threads[i], main_task, &param[i]);
	}
	for (i = 0; i < num_threads; i++)
		thrd_join(threads[i]);

	bool correct = false;
	//correct |= (a == 17 || a == 37 || a == 0);
	//MODEL_ASSERT(correct);

	free(param);
	free(threads);
	free(stack);
	
	return 0;
}
