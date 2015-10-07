#include "IQueue.h"

template<typename T>
IQueue<T>::IQueue()
{
    head.store(0);
    tail.store(0);

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
    items[slot] = x;
    return;
}

template<typename T>
T IQueue<T>::deq()
{
    T value;
    int slot;
    do {
        slot = head.load();
        value = items[slot];
        if(value == NULL)
            return NULL;
    
    
    } while (!head.compare_exchange_strong(slot, slot+1));
    return value;
}

