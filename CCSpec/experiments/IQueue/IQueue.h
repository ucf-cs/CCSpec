#include <atomic>
#include <stdio.h>
#include <string>

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
    
	//Linearizability
    std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    

    //Sequential Consistency
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
	//std::string expression("x = 0; for(n=0;n<5;n++){ for(m=0;m<n;m++){ x = x + 1; fprintf x; } }");
	
	//Quiescent
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");

	//K-Linearizability
    //std::string expression("k=2; for(n=h.length - 1; n > 0; n--){ i = 0; for(m=n-1;m>=0;m--){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION) && (method_name(m, h.s[m].get_tid()) == method_name(n, h.s[n].get_tid()))){i = i + 1; if(i > k) {method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } } }");    

	correctness_condition(expression);
}

template<typename T>
IQueue<T>::~IQueue()
{


}

template<typename T>
void IQueue<T>::enq(T x)
{
    std::string str1("enqueue");
	std::string str2("dequeue");
    function_call(str1, INVOCATION, x);   
    int slot; 		
    do {
        slot = tail.load();
        if(slot == LENGTH)
            return; 
    } while (!tail.compare_exchange_strong(slot, slot+1));
    items[slot].store(x);
    function_call(str1, RESPONSE);
    return;
}

template<typename T>
T IQueue<T>::deq()
{
    std::string str1("dequeue");
	std::string str2("enqueue");
    function_call(str1, INVOCATION);
    T value;
    int slot;
		
    do {
		
        slot = head.load();

        value = items[slot].load();
        //if(value == NULL)
            //return NULL;
        if(value == 0)
		{	
			function_call(str1, RESPONSE, value);
            return 0;
		}
    
    } while (!head.compare_exchange_strong(slot, slot+1));
    function_call(str1, RESPONSE, value);
    return value;
}



