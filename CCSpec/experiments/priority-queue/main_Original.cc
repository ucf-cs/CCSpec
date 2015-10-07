//------------------------------------------------------------------------------
// 
//     Testing different priority queues
//
//------------------------------------------------------------------------------

#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <set>
//#include <thread>
#include <mutex>
#include <boost/random.hpp>
#include <sched.h>
#include "common/timehelper.h"
#include "common/threadbarrier.h"
#include "priorityqueue/queueadaptor.h"

#include <threads.h>

//ThreadBarrier ba(4);

template<typename T>
struct thread_data
{
    //thread_data(ThreadBarrier& _barrier, T& _pq) : barrier(_barrier), pq(_pq) {}
    //thread_data() : barrier(NULL), pq(NULL) {}
	uint32_t numThread;
	int threadId;
 	uint32_t testSize;
 	uint32_t portion; 
	//ThreadBarrier& barrier;  
	//ThreadBarrier *barrier;
	std::reference_wrapper<ThreadBarrier> barrier;
	//T& pq;
	//T *pq;
	std::reference_wrapper<T> pq;
};

//template<typename T>
//void LockThread(uint32_t numThread, int threadId, uint32_t testSize, uint32_t portion, ThreadBarrier& barrier,  T& pq)
template<typename T>
static void LockThread(void * arg)
{
	struct thread_data<T> *param = (struct thread_data<T> *) arg;
	uint32_t numThread = param->numThread;
	int threadId = param->threadId;
	uint32_t testSize = param->testSize;
	uint32_t portion = param->portion;
	//ThreadBarrier& barrier = param->barrier;
	//ThreadBarrier barrier = *(param->barrier);
	ThreadBarrier barrier = param->barrier;
	//T& pq = param->pq;
	//T pq = *(param->pq);
	T pq = param->pq;

    //set affinity for each thread
  
    cpu_set_t cpu = {{0}};
    CPU_SET(threadId, &cpu);
    sched_setaffinity(0, sizeof(cpu_set_t), &cpu);
   

    double startTime = Time::GetWallTime();
    boost::mt19937 randomGen;
    boost::mt19937 randomGenOp;
    randomGen.seed(startTime + threadId);
    randomGenOp.seed(startTime + threadId + 1000);
    boost::uniform_int<uint32_t> randomDist(1, 0xfffffffa);
    boost::uniform_int<uint32_t> randomDistOp(1, 100);
    
    pq.Init();

    barrier.Wait();

    //This is used to test deletemin only
    //for(unsigned int i = 0; i < testSize / numThread; ++i)
    for(unsigned int i = 0; i < testSize; ++i)
    {
        if(randomDistOp(randomGenOp) <= portion)
        {
            pq.Insert(randomDist(randomGen));
        }
        else
        {
            pq.DeleteMin();
        }
    }

    //for(unsigned int i = 0; i < testSize; ++i)
    //{
        //pq.Insert(randomDist(randomGen));
    //}    

    //ba.Wait();

    //for(unsigned int i = 0; i < testSize; ++i)
    //{
        //pq.DeleteMin();
    //}

    pq.Uninit();
 
}


template<typename T>
void Tester(uint32_t numThread, uint32_t testSize, uint32_t portion,  QueueAdaptor<T>& pq)
{
	
	//std::vector<std::thread> thread(numThread);
	std::vector<thrd_t> thread(numThread);

    ThreadBarrier barrier(numThread + 1);
    
    //struct thread_data<T> param(std::ref(barrier), std::ref(pq))[numThread];
    
    struct thread_data<QueueAdaptor<T>> *param = (struct thread_data<QueueAdaptor<T>> *) malloc(numThread*sizeof(thread_data<QueueAdaptor<T>>));     

    double startTime = Time::GetWallTime();
    boost::mt19937 randomGen;
    randomGen.seed(startTime - 10);
    boost::uniform_int<uint32_t> randomDist(1, 0xfffffffa);

    pq.Init();

    for(unsigned int i = 0; i < testSize; ++i)
    {
        pq.Insert(randomDist(randomGen));
    }

    //Create joinable threads
    for (unsigned i = 0; i < numThread; i++) 
    {
		param[i].numThread = numThread;
		param[i].threadId = i;
		param[i].testSize = testSize;
		param[i].portion = portion;
		//param[i].barrier = std::ref(barrier);
		//param[i].pq = std::ref(pq);
		param[i].barrier = std::ref(barrier);
		//param[i].barrier = &barrier;
		param[i].pq = std::ref(pq);
		//param[i].pq = &pq;
		
        //thread[i] = std::thread(LockThread<QueueAdaptor<T> >, numThread, i, testSize, portion, std::ref(barrier), std::ref(pq));
		
		thrd_create(&thread[i], LockThread<QueueAdaptor<T> >, &param[i]);
    }

    barrier.Wait();

    {
        ScopedTimer timer(true);
     
        //Wait for the threads to finish
        for (unsigned i = 0; i < thread.size(); i++) 
        {
            //thread[i].join();
			thrd_join(thread[i]);
        }
      
    }

    pq.Uninit();
    free(param);
}

//int main(int argc, const char *argv[])
int user_main(int argc, char **argv)
{
    uint32_t queueType = 0;
    uint32_t numThread = 4;
    //uint32_t testSize = 100000;
    uint32_t testSize = 2;
    uint32_t portion = 50;

    if(argc > 1) queueType = atoi(argv[1]);
    if(argc > 2) numThread = atoi(argv[2]);
    if(argc > 3) testSize = atoi(argv[3]);
    if(argc > 4) portion = atoi(argv[4]);

    assert(queueType < 4);

    const char* queueName[] = {"MDPQ", "LJPQ", "TBBPQ", "HSPQ", "STDPD"};

    printf("Start testing %s with %d threads %d iterations %d%% insert.\n", queueName[queueType], numThread, testSize, portion);

    switch(queueType)
    {
    case 0:
        { QueueAdaptor<MDList> pq(testSize, numThread + 1); Tester(numThread, testSize, portion, pq); }
        break;
	/*
    case 1:
        { QueueAdaptor<LINDENPQ> pq; Tester(numThread, testSize, portion, pq); }
        break;
    case 2:
        { QueueAdaptor<TBBPQ> pq; Tester(numThread, testSize, portion, pq); }
        break;
    case 3:
        { QueueAdaptor<SHAVITPQ> pq; Tester(numThread, testSize, portion, pq); }
        break;
    case 4:
        { QueueAdaptor<STDPQ> pq; Tester(numThread, testSize, portion, pq); }
        break;
	*/
    default:
        break;
    }

    return 0;
}
