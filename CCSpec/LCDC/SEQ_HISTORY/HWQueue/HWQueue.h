#include <atomic>
#include <stdio.h>
#include <string.h>

#define CAPACITY 3

template <typename T> 
class HWQueue 
{
public:
    HWQueue();
    ~HWQueue();
    void enq(T x);
    T deq();

private:
    std::atomic<int> tail;
    std::atomic<T> items[CAPACITY];
};

template<typename T>
HWQueue<T>::HWQueue()
{
    tail.store(0);
    for(int i = 0; i < CAPACITY; i++)
    {
        items[i].store(NULL);  
    }
    
}

template<typename T>
HWQueue<T>::~HWQueue()
{


}

template<typename T>
void HWQueue<T>::enq(T x)
{  
	
    int i = tail.fetch_add(1);
    items[i].store(x);

    return;
}

template<typename T>
T HWQueue<T>::deq()
{

    //while(true) {
        int range = tail.load();
        for(int i = 0; i < range; i++) 
        {
            T value = items[i].exchange(NULL);
            if(value != NULL) {
                return value;           
            }     
        }
        
    //}
    return NULL;
}



