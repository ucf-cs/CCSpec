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
        items[i].store((int) NULL);  
    }
    //Linearizability
    std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    
    
    //Sequential Consistency
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");

	//Quiescent
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
	correctness_condition(expression);
}

template<typename T>
HWQueue<T>::~HWQueue()
{


}

template<typename T>
void HWQueue<T>::enq(T x)
{  
	std::string str1("enqueue");
	std::string str2("dequeue");

    function_call(str1, INVOCATION, x);
   
    int i = tail.fetch_add(1);
	
    items[i].store(x);

	function_call(str1, RESPONSE);
    return;
}

template<typename T>
T HWQueue<T>::deq()
{
	std::string str1("dequeue");
    function_call(str1, INVOCATION);
    //while(true) {
        int range = tail.load();
        for(int i = 0; i < range; i++) 
        {
            T value = items[i].exchange((int) NULL);
            if(value != (int) NULL) {
				function_call(str1, RESPONSE, value);
                return value;           
            }     
        }
        
    //}
	function_call(str1, RESPONSE);
    return (int) NULL;
}



