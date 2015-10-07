#include <atomic>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

template <typename T> 
class BoundedSizeKFifo 
{
public:
    BoundedSizeKFifo(uint64_t k, uint64_t num_segments);
    ~BoundedSizeKFifo();
	bool advance_head(uint64_t head_old);
	bool advance_tail(uint64_t tail_old);
	bool queue_full(uint64_t head_old, uint64_t tail_old);
	bool segment_not_empty(uint64_t head_old);
	bool in_valid_region(uint64_t tail_old_pointer, uint64_t tail_current_pointer, uint64_t head_current_pointer);
	bool not_in_valid_region(uint64_t tail_old_pointer, uint64_t tail_current_pointer, uint64_t head_current_pointer);
	bool find_index(uint64_t start_index, bool empty, uint64_t *item_index, T* old);
	bool committed(uint64_t tail_old, T new_item, uint64_t item_index);
    bool enqueue(T x);
    //bool dequeue(T *item);
	T dequeue();

private:

	uint64_t queue_size_;
	size_t k_;
	std::atomic<uint64_t> *head_;
	std::atomic<uint64_t> *tail_;
	std::atomic<T> *queue_;
};

template<typename T>
BoundedSizeKFifo<T>::BoundedSizeKFifo(uint64_t k, uint64_t num_segments)
{
	queue_size_ = k * num_segments;
	k_ = k;
	head_ = new std::atomic<uint64_t>();
	tail_ = new std::atomic<uint64_t>();
    head_->store(0);
	tail_->store(0);
	queue_ = (std::atomic<T> *) malloc(queue_size_ * sizeof(std::atomic<T>));

    for(uint64_t i = 0; i < queue_size_; i++)
    {
        queue_[i].store((T) NULL);  
    }
    
    //Linearizability
    std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    
    
    //Sequential Consistency
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");

	//Quiescent
    //std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");

	//K-Linearizability
    //std::string expression("k=2; for(n=h.length - 1; n > 0; n--){ i = 0; for(m=n-1;m>=0;m--){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION) && (method_name(m, h.s[m].get_tid()) == method_name(n, h.s[n].get_tid()))){i = i + 1; if(i > k) {method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } } }");    

	correctness_condition(expression);
    
}

template<typename T>
BoundedSizeKFifo<T>::~BoundedSizeKFifo()
{


}

template<typename T>
bool BoundedSizeKFifo<T>::advance_head(uint64_t head_old) {
  return head_->compare_exchange_strong(head_old, (head_old + k_) % queue_size_);
}


template<typename T>
bool BoundedSizeKFifo<T>::advance_tail(uint64_t tail_old) {
  return tail_->compare_exchange_strong(tail_old,(tail_old + k_) % queue_size_);
}


template<typename T>
bool BoundedSizeKFifo<T>::queue_full(uint64_t head_old, uint64_t tail_old) {
  if (((tail_old + k_) % queue_size_) == head_old && (head_old == head_->load())) {
    return true;
  }
  return false;
}

template<typename T>
bool BoundedSizeKFifo<T>::segment_not_empty(uint64_t head_old) {
  uint64_t start = head_old;
  for (size_t i = 0; i < k_; i++) {
    if (queue_[(start + i) % queue_size_].load() != (T)NULL) {
      return true;
    }
  }
  return false;
}

template<typename T>
bool BoundedSizeKFifo<T>::in_valid_region(uint64_t tail_old_pointer,
                                          uint64_t tail_current_pointer,
                                          uint64_t head_current_pointer) {
  bool wrap_around = (tail_current_pointer < head_current_pointer)
                     ? true : false;
  if (!wrap_around) {
    return (head_current_pointer < tail_old_pointer
            && tail_old_pointer <= tail_current_pointer) ? true : false;
  }
  return (head_current_pointer < tail_old_pointer
          || tail_old_pointer <= tail_current_pointer) ? true : false;
}


template<typename T>
bool BoundedSizeKFifo<T>::not_in_valid_region(uint64_t tail_old_pointer,
                                              uint64_t tail_current_pointer,
                                              uint64_t head_current_pointer) {
  bool wrap_around = (tail_current_pointer < head_current_pointer)
                     ? true : false;
  if (!wrap_around) {
    return (tail_old_pointer < tail_current_pointer
            || head_current_pointer < tail_old_pointer) ? true : false;
  }
  return (tail_old_pointer < tail_current_pointer
          && head_current_pointer < tail_old_pointer) ? true : false;
}

template<typename T>
bool BoundedSizeKFifo<T>::find_index(uint64_t start_index, bool empty, uint64_t *item_index, T* old) {
  uint64_t index;
  for (size_t i = 0; i < k_; i++) {
    index = (start_index + i ) % queue_size_;
    *old = queue_[index].load();
    if ((empty && *old == (T)NULL)
        || (!empty && *old != (T)NULL)) {
      *item_index = index;
      return true;
    }
  }
  return false;
}

template<typename T>
bool BoundedSizeKFifo<T>::committed(uint64_t tail_old,
                                    //uint64_t tail_old_pointer,
                                    //AtomicValue<T> *new_item,
                                    T new_item,
                                    uint64_t item_index) {
  if (queue_[item_index].load() != new_item)  {
    return true;
  }

  uint64_t tail_current = tail_->load();
  uint64_t head_current = head_->load();
  if (in_valid_region(tail_old, tail_current,
                      head_current)) {
    return true;
  } else if (not_in_valid_region(tail_old, tail_current,
                                 head_current)) {
    if (!queue_[item_index].compare_exchange_strong(new_item, (T)NULL)) {
      return true;
    }
  } else {
    if (head_->compare_exchange_strong(head_current, head_current)) {
      return true;
    }
    if (!queue_[item_index].compare_exchange_strong(new_item, (T)NULL)) { 
      return true;
    }
  }
  return false;
}


template<typename T>
bool BoundedSizeKFifo<T>::enqueue(T new_item)
{  
  std::string str1("enqueue");
  function_call(str1, INVOCATION, new_item);

  uint64_t tail_old;
  uint64_t head_old;

  uint64_t item_index;
  T old_item;
  bool found_idx;

  while (true) {
    tail_old = tail_->load();
    head_old = head_->load();
    found_idx = find_index(tail_old, true, &item_index, &old_item);

    if (tail_old == tail_->load()) {
      if (found_idx) {
		
        if (queue_[item_index].compare_exchange_strong(old_item, new_item)) {
	
          if (committed(tail_old, new_item, item_index)) {
            function_call(str1, RESPONSE);
            return true;
          }

        }
		
      } else {
	
        if (queue_full(head_old, tail_old)) {
          if (segment_not_empty(head_old) &&
              (head_old == head_->load())) {
            function_call(str1, RESPONSE);
            return false;
          }
          advance_head(head_old);
        }
        advance_tail(tail_old);

        function_call(str1, RESPONSE);
		return false;
		
      }
		
    }
	
  }
}

template<typename T>
T BoundedSizeKFifo<T>::dequeue() {
//bool BoundedSizeKFifo<T>::dequeue(T *item) {

  std::string str1("dequeue");
  function_call(str1, INVOCATION);

  uint64_t tail_old;
  uint64_t head_old;

  uint64_t item_index;
  T old_item;
  bool found_idx;
  while (true) {
    head_old = head_->load();
    tail_old = tail_->load();
    found_idx = find_index(head_old, false, &item_index, &old_item);
    if (head_old == head_->load()) {
      if (found_idx) {
        if (head_old == tail_old) {
          advance_tail(tail_old);
        }
        if (queue_[item_index].compare_exchange_strong(old_item, (T)NULL)) {
          //*item = old_item;
          //return true;
          function_call(str1, RESPONSE, old_item);
		  return old_item;
        }
      } else {
        if ((head_old == tail_old) && (tail_old == tail_->load())) {
          //return false;
          function_call(str1, RESPONSE);
		  return (T) NULL;
        }
        advance_head(head_old);
      }
    }
  }
}

