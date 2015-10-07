#include <threads.h>
#include <stdlib.h>
#include "librace.h"
#include "model-assert.h"

#include "my_stack.h"

#define MAX_FREELIST 4 /* Each thread can own up to MAX_FREELIST free nodes */
#define INITIAL_FREE 2 /* Each thread starts with INITIAL_FREE free nodes */

#define POISON_IDX 0x666

static unsigned int (*free_lists)[MAX_FREELIST];

/* Search this thread's free list for a "new" node */
static unsigned int new_node()
{
	int i;
	int t = get_thread_num();
	for (i = 0; i < MAX_FREELIST; i++) {
		//unsigned int node = load_32(&free_lists[t][i]);
		unsigned int node = free_lists[t][i];
		if (node) {
			//store_32(&free_lists[t][i], 0);
			free_lists[t][i] = 0;
			return node;
		}
	}
	/* free_list is empty? */
	MODEL_ASSERT(0);
	return 0;
}

/* Place this node index back on this thread's free list */
static void reclaim(unsigned int node)
{
	int i;
	int t = get_thread_num();

	/* Don't reclaim NULL node */
	//MODEL_ASSERT(node);

	for (i = 0; i < MAX_FREELIST; i++) {
		/* Should never race with our own thread here */
		//unsigned int idx = load_32(&free_lists[t][i]);
		unsigned int idx = free_lists[t][i];

		/* Found empty spot in free list */
		if (idx == 0) {
			//store_32(&free_lists[t][i], node);
			free_lists[t][i] = node;
			return;
		}
	}
	/* free list is full? */
	MODEL_ASSERT(0);
}

void init_stack(stack_t *s, int num_threads)
{
	int i, j;

	/* Initialize each thread's free list with INITIAL_FREE pointers */
	/* The actual nodes are initialized with poison indexes */
	free_lists = (unsigned int (*)[MAX_FREELIST]) malloc(num_threads * sizeof(*free_lists));
	for (i = 0; i < num_threads; i++) {
		for (j = 0; j < INITIAL_FREE; j++) {
			free_lists[i][j] = 1 + i * MAX_FREELIST + j;
			atomic_init(&s->nodes[free_lists[i][j]].next, MAKE_POINTER(POISON_IDX, 0));
		}
	}

	/* initialize stack */
	atomic_init(&s->top, MAKE_POINTER(0, 0));
	
	//ANNOTATION
	//Linearizability
    std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    
	//Sequential Consistency
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
	//Quiescent
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
	correctness_condition(expression);
}

void push(stack_t *s, unsigned int val) {

    std::string str1("push"); //ANNOTATION
	function_call(str1, INVOCATION, val); //ANNOTATION
	    
	unsigned int nodeIdx = new_node();
	node_t *node = &s->nodes[nodeIdx];
	node->value = val;
	pointer oldTop, newTop;
	bool success;
	while (true) {
		// memory_order_seq_cst
		oldTop = atomic_load_explicit(&s->top, memory_order_seq_cst);
		newTop = MAKE_POINTER(nodeIdx, get_count(oldTop) + 1);
		// memory_order_seq_cst
		atomic_store_explicit(&node->next, oldTop, memory_order_seq_cst);

		// memory_order_seq_cst & memory_order_seq_cst
		success = atomic_compare_exchange_strong_explicit(&s->top, &oldTop,
			newTop, memory_order_seq_cst, memory_order_seq_cst);
		if (success)
			break;
	} 
	function_call(str1, RESPONSE); //ANNOTATION
}

unsigned int pop(stack_t *s) 
{
    std::string str1("pop"); //ANNOTATION
	function_call(str1, INVOCATION); //ANNOTATION
	    
	pointer oldTop, newTop, next;
	node_t *node;
	bool success;
	int val;
	while (true) {
		// memory_order_seq_cst
		oldTop = atomic_load_explicit(&s->top, memory_order_seq_cst);
		if (get_ptr(oldTop) == 0)
		{
		    function_call(str1, RESPONSE, 0); //ANNOTATION
			return 0;
		}
		node = &s->nodes[get_ptr(oldTop)];
		// memory_order_seq_cst
		next = atomic_load_explicit(&node->next, memory_order_seq_cst);
		newTop = MAKE_POINTER(get_ptr(next), get_count(oldTop) + 1);
		// memory_order_seq_cst & memory_order_seq_cst
		success = atomic_compare_exchange_strong_explicit(&s->top, &oldTop,
			newTop, memory_order_seq_cst, memory_order_seq_cst);
		if (success)
			break;
	}
	val = node->value;
	/* Reclaim the used slot */
	reclaim(get_ptr(oldTop));
	function_call(str1, RESPONSE, val); //ANNOTATION
	return val;
}
