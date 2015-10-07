#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

#include "model-assert.h"

#include "deque.h"

Deque *q;
int a;
int b;
int c;

static void task(void * param) {
	push(q, 200);
	take(q);
	//a=steal(q);
}

static void task2(void * param) {
	push(q, 400);
	b=take(q);
}


int user_main(int argc, char **argv)
{
	thrd_t t, t2;
	q=create();
	push(q, 100);
	thrd_create(&t, task, 0);
	thrd_create(&t2, task2, 0);
	//push(q, 100);
	//c=take(q);
	thrd_join(t);
	thrd_join(t2);
/*
	bool correct=true;
	if (a!=1 && a!=2 && a!=4 && a!= EMPTY)
		correct=false;
	if (b!=1 && b!=2 && b!=4 && b!= EMPTY)
		correct=false;
	if (c!=1 && c!=2 && c!=4 && a!= EMPTY)
		correct=false;
	if (a!=EMPTY && b!=EMPTY && c!=EMPTY && (a+b+c)!=7)
		correct=false;
	if (!correct)
		printf("a=%d b=%d c=%d\n",a,b,c);
	MODEL_ASSERT(correct);
*/
	return 0;
}
