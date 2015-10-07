#include <atomic>
#include <stdio.h>
#include <string.h>

#define LENGTH 3

template <typename T> 
class IQueue 
{
public:
    IQueue();
    ~IQueue();
    void enq(T x);
    T deq();

private:
    std::atomic<int> head;
    std::atomic<int> tail;
    std::atomic<T> items[LENGTH];


};

template<typename T>
IQueue<T>::IQueue()
{
    head.store(0);
    tail.store(0);
    
    for(int i = 0; i < LENGTH; i++)
    {
        items[i].store(0);  
    }
    
}

template<typename T>
IQueue<T>::~IQueue()
{


}

template<typename T>
void IQueue<T>::enq(T x)
{
 
    int slot; 		
    do {
        slot = tail.load();
        if(slot == LENGTH)
            return; 
	
    } while (!tail.compare_exchange_strong(slot, slot+1));

    items[slot].store(x);
    return;
}

template<typename T>
T IQueue<T>::deq()
{
    T value;
    int slot;
		
    do {
		
        slot = head.load();
        value = items[slot].load();
        //if(value == NULL)
            //return NULL;
        if(value == 0)
		{	
            return 0;
		}    
    } while (!head.compare_exchange_strong(slot, slot+1));
    return value;
}



