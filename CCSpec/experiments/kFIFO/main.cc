#include <stdlib.h>
#include <stdio.h>
#include <threads.h>

#include "boundedsize_kfifo.h"

#define k 1
#define num_segments 1

static void a(void *arg)
{
	uint64_t *item;
	BoundedSizeKFifo<uint64_t> *myqueue = (BoundedSizeKFifo<uint64_t> *) arg;
	myqueue->enqueue(100);
	myqueue->enqueue(300);
	//myqueue->dequeue(item);
	myqueue->dequeue();
	
}

static void b(void *arg)
{
	uint64_t *item;
	BoundedSizeKFifo<uint64_t> *myqueue = (BoundedSizeKFifo<uint64_t> *) arg;
	myqueue->enqueue(200);
	//myqueue->dequeue(item);
	myqueue->dequeue();
}

int user_main(int argc, char **argv)
{
	int i;
	thrd_t t1, t2;
	
	BoundedSizeKFifo<uint64_t> myqueue((uint64_t) k, (uint64_t) num_segments);
	
	thrd_create(&t1, a, &myqueue);
	thrd_create(&t2, b, &myqueue);

	thrd_join(t1);
	thrd_join(t2);

	return 0;
}
