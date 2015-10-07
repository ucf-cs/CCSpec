#ifndef DEQUE_H
#define DEQUE_H

using namespace std;

typedef struct {
	atomic_size_t size;
	atomic_int buffer[];
} Array;

typedef struct {
	atomic_size_t top, bottom;
	atomic_uintptr_t array; /* Atomic(Array *) */
} Deque;

Deque * create();
int take(Deque *q);
void resize(Deque *q);
void push(Deque *q, int x);
int steal(Deque *q);

#define EMPTY 0xffffffff
#define ABORT 0xfffffffe

#endif
