#include <stdatomic.h>
#include <inttypes.h>
#include "deque.h"
#include <stdlib.h>
#include <stdio.h>

//CLP ADDED
#include "linearizable_NEW.h"

Deque * create() {
	Deque * q = (Deque *) calloc(1, sizeof(Deque));
	Array * a = (Array *) calloc(1, sizeof(Array)+2*sizeof(atomic_int));
	atomic_store_explicit(&q->array, (long unsigned int) a, memory_order_seq_cst);
	atomic_store_explicit(&q->top, 0, memory_order_seq_cst);
	atomic_store_explicit(&q->bottom, 0, memory_order_seq_cst);
	atomic_store_explicit(&a->size, 2, memory_order_seq_cst);

	//ANNOTATION
	//Linearizability
	std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    
	//Sequential Consistency
	//std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
	//Quiescent
	//std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
	correctness_condition(expression);

	return q;
}

int take(Deque *q) {
	std::string str1("pop_back"); //ANNOTATION
	function_call(str1, INVOCATION); //ANNOTATION

	size_t b = atomic_load_explicit(&q->bottom, memory_order_seq_cst) - 1;
	Array *a = (Array *) atomic_load_explicit(&q->array, memory_order_seq_cst);
	atomic_store_explicit(&q->bottom, b, memory_order_seq_cst); //relaxed
	atomic_thread_fence(memory_order_seq_cst);
	size_t t = atomic_load_explicit(&q->top, memory_order_seq_cst);
	int x;
	if (t <= b) {
		/* Non-empty queue. */
		x = atomic_load_explicit(&a->buffer[b % atomic_load_explicit(&a->size,memory_order_seq_cst)], memory_order_seq_cst);
		if (t == b) {
			/* Single last element in queue. */
			if (!atomic_compare_exchange_strong_explicit(&q->top, &t, t + 1, memory_order_seq_cst, memory_order_seq_cst))
				/* Failed race. */
				x = EMPTY;
			atomic_store_explicit(&q->bottom, b + 1, memory_order_seq_cst); //relaxed
		}
	} else { /* Empty queue. */
		x = EMPTY;
		atomic_store_explicit(&q->bottom, b + 1, memory_order_seq_cst); // relaxed
	}
	//if(x == EMPTY)
		//function_call(str1, RESPONSE, (uint64_t) NULL); //ANNOTATION
	//else
		function_call(str1, RESPONSE, (uint64_t) x); //ANNOTATION
	return x;
}

void resize(Deque *q) {
	Array *a = (Array *) atomic_load_explicit(&q->array, memory_order_seq_cst);
	size_t size=atomic_load_explicit(&a->size, memory_order_seq_cst);
	size_t new_size=size << 1;
	Array *new_a = (Array *) calloc(1, new_size * sizeof(atomic_int) + sizeof(Array));
	size_t top=atomic_load_explicit(&q->top, memory_order_seq_cst);
	size_t bottom=atomic_load_explicit(&q->bottom, memory_order_seq_cst);
	atomic_store_explicit(&new_a->size, new_size, memory_order_seq_cst);
	size_t i;
	for(i=top; i < bottom; i++) {
		atomic_store_explicit(&new_a->buffer[i % new_size], atomic_load_explicit(&a->buffer[i % size], memory_order_seq_cst), memory_order_seq_cst);
	}
	atomic_store_explicit(&q->array, (long unsigned int) new_a, memory_order_seq_cst);
	printf("resize\n");
}

void push(Deque *q, int x) {
	std::string str1("push_back"); //ANNOTATION
	function_call(str1, INVOCATION, (uint64_t) x); //ANNOTATION

	size_t b = atomic_load_explicit(&q->bottom, memory_order_seq_cst);
	size_t t = atomic_load_explicit(&q->top, memory_order_seq_cst);
	Array *a = (Array *) atomic_load_explicit(&q->array, memory_order_seq_cst);
	if (b - t > atomic_load_explicit(&a->size, memory_order_seq_cst) - 1) /* Full queue. */ {
		resize(q);
		//Bug in paper...should have next line...
		a = (Array *) atomic_load_explicit(&q->array, memory_order_seq_cst);
	}
	atomic_store_explicit(&a->buffer[b % atomic_load_explicit(&a->size, memory_order_seq_cst)], x,memory_order_seq_cst);
	atomic_thread_fence(memory_order_seq_cst);
	atomic_store_explicit(&q->bottom, b + 1, memory_order_seq_cst); //relaxed
	function_call(str1, RESPONSE); //ANNOTATION
}

int steal(Deque *q) {
	std::string str1("pop_front"); //ANNOTATION
	function_call(str1, INVOCATION); //ANNOTATION
	size_t t = atomic_load_explicit(&q->top, memory_order_seq_cst); //acquire
	atomic_thread_fence(memory_order_seq_cst);
	size_t b = atomic_load_explicit(&q->bottom, memory_order_seq_cst); //acquire
	int x = EMPTY;
	if (t < b) {
		/* Non-empty queue. */
		Array *a = (Array *) atomic_load_explicit(&q->array, memory_order_seq_cst);
		x = atomic_load_explicit(&a->buffer[t % atomic_load_explicit(&a->size, memory_order_seq_cst)], memory_order_seq_cst);
		if (!atomic_compare_exchange_strong_explicit(&q->top, &t, t + 1, memory_order_seq_cst, memory_order_seq_cst))
		{
			function_call(str1, RESPONSE, (uint64_t) ABORT); //ANNOTATION
			/* Failed race. */
			return ABORT;
		}
	}
	//if(x == EMPTY)
		//function_call(str1, RESPONSE, (uint64_t) NULL); //ANNOTATION
	//else
		function_call(str1, RESPONSE, (uint64_t) x); //ANNOTATION
	return x;
}
