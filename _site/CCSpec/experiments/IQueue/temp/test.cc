#include <atomic>
#include <threads.h>
#include <stdio.h>

#include "IQueue.h"

std::atomic<int> y;

static void a(void *obj)
{
    const char my_str[] = "a\0";
    //str[0] = 'a';
    //str[1] = '\0';
    const char *str = my_str;
    function_call(str, BEGIN, &y);
    int r1 = y.load();
    
    IQueue<int> *q =(IQueue<int> *) obj;
    //char str[10];
    //strcpy(str, "enq");
    //char str[] = "enq";
    /*
    char str[4];
    str[0] = 'e';
    str[1] = 'n';
    str[2] = 'q';
    str[3] = '\0';
    */
    
    
    q->enq(1);
	//linearization_point(STORE, &x);


	//function_call(str, END, &x);
	
}

static void b(void *obj)
{
    IQueue<int> *q =(IQueue<int> *) obj;
    char str[2];
    str[0] = 'b';
    str[1] = '\0';
    //function_call(str, BEGIN, &x);
    //q->enq(2);
	//linearization_point(STORE, &y);


	//function_call(str, END, &y);
}

int user_main(int argc, char **argv)
{
	thrd_t t1, t2;
	
	y.store(0);
	
	IQueue<int> q;
	
	printf("Main thread: creating 2 threads\n");
	thrd_create(&t1, (thrd_start_t)&a, &q);
	thrd_create(&t2, (thrd_start_t)&b, &q);

	thrd_join(t1);
	thrd_join(t2);
	printf("Main thread is finished\n");

	return 0;
}

