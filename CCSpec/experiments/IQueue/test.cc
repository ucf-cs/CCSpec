#include <atomic>
#include <threads.h>
#include <stdio.h>
#include <string>

#include "IQueue.h"

static void a(void *obj)
{
    IQueue<int> *q =(IQueue<int> *) obj;
	q->enq(100); 
}

static void b(void *obj)
{
    IQueue<int> *q =(IQueue<int> *) obj;
	q->enq(200);
	q->deq();
}

int user_main(int argc, char **argv)
{
	thrd_t t1, t2;

	IQueue<int> q;
	
	printf("Main thread: creating 2 threads\n");
	thrd_create(&t1, (thrd_start_t)&a, &q);
	thrd_create(&t2, (thrd_start_t)&b, &q);

	thrd_join(t1);
	thrd_join(t2);
	printf("Main thread is finished\n");

	return 0;
}
