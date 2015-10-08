---
layout: tervel_documentation
---

# CDSChecker

CCSpec is built on top of the model checker CDSChecker [^0]. 

[^0]: Norris, Brian, and Brian Demsky. "CDSchecker: Checking concurrent data structures written with C/C++ atomics." ACM SIGPLAN Notices 48, no. 10 (2013): 131-150.

## Designing the Concurrent Data Structure
The concurrent data structure must use atomic instructions from the [C++ Atomic Operations Library](http://en.cppreference.com/w/cpp/atomic).  

## Creating a Unit Test

The unit test must be created following the specifications described in the `Running your own code' section on CDSChecker's website: 
[http://plrg.eecs.uci.edu/software_page/42-2/](http://plrg.eecs.uci.edu/software_page/42-2/). For your convenience, the guidance for creating the unit test is listed below:

*	Include the CDSChecker threads library <threads.h>
*	Instead of using the standard main method main(int argc, char *argv[]), you must use the CDSChecker main method user_main(int argc, char *argv[]).
*	Declare a thread using the data type thrd_t.
*	Spawn a thread using thrd_create. Note the following signature: thrd_create(&t, (thrd_start_t) &work, (void *) arg)
	*	t = reference to thread t of type thrd_t
    *	work = the code that the thread will run
    *	arg = the argument that is passed to the thread
*	Wait for a thread to finish using thrd_join. Note the following signature: thrd_join(t)
    *	t = reference to thread t of type thrd_t
*	Define the thread code using static void work(void *obj){*code to be performed by thread*}
 

