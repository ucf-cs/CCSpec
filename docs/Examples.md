---
layout: tervel_documentation
---

# CCSpec Examples
We demonstrate the usage of Scylla and CCSpec on the Herlihy-Wing Queue [^0].

[^0]: Herlihy, Maurice P., and Jeannette M. Wing. "Linearizability: A correctness condition for concurrent objects." ACM Transactions on Programming Languages and Systems (TOPLAS) 12, no. 3 (1990): 463-492.

## Scylla Annotations

{% highlight bash %}
#define N 3
template <typename T> 
class HWQueue {
public:
  HWQueue();
  ~HWQueue();
  void enq(T x);
  T deq();
private:
  std::atomic<int> tail;
  std::atomic<T> items[N];
};
template<typename T>
HWQueue<T>::HWQueue(){
  //#correctness_condition{...};
  tail.store(0);
  for(int i=0; i<N; i++)
  { items[i].store(NULL); }
}
template<typename T>
void HWQueue<T>::enq(T x){  
  //#begin{enq}; 
  //#input{x};
  int i=tail.fetch_add(1);
  items[i].store(x);
  //#end{enq};
  //#result{void};
}
{% endhighlight %}

## Correctness Condition Specifications

### Linearizability
{% highlight bash %}
//#correctness_condition {
  for(n=0; n < h.length; n++)
	  for(m=0; m < n; m++) 
	  {
		if(h.s[m].get_type() == RESPONSE && h.s[n].get_type() == INVOCATION)
		{
			method_id(m, h.s[m].get_tid()) happens_before
			method_id(n, h.s[n].get_tid());
		}
	}
}	
{% endhighlight %}