/*
The MIT License (MIT)

Copyright (c) 2015 University of Central Florida's Computer Software Engineering
Scalable & Secure Systems (CSE - S3) Lab

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#ifndef TERVEL_MEMORY_RC_DESCRIPTOR_POOL_H_
#define TERVEL_MEMORY_RC_DESCRIPTOR_POOL_H_

#include <tervel/util/info.h>
#include <tervel/util/util.h>
#include <tervel/util/system.h>
#include <tervel/util/descriptor.h>
#include <tervel/util/memory/rc/pool_element.h>
#include <tervel/util/memory/rc/pool_manager.h>

namespace tervel {
namespace util {
namespace memory {
namespace rc {

class PoolManager;
/**
 * Defines a pool of descriptor objects which is used to allocate descriptors
 * and to store them while they are not safe to delete.
 *
 * The pool is represented as two linked lists of descriptors: one for safe
 * elements and one for unsafe elements. The safe pool is known to only contain
 * items owned by the thread owning the DescriptorPool object, and the unsafe
 * pool contains items where other threads may still hold references to them.
 *
 * Further, the pool object has a parent who is shared amongst other threads.
 * When a pool is to be destroyed, it sends its remaining elements to the
 * parent, relinquishing ownership of said elements. A top-level pool has a null
 * parent. At the moment, it only makes sense to have a single top-level parent
 * representing the central pool for all threads, and several local pools for
 * each thread.
 */
class DescriptorPool {
 public:
  DescriptorPool(PoolManager *manager, uint64_t pool_id, int prefill = TERVEL_MEM_RC_MIN_NODES)
      : manager_(manager)
      , pool_id_(pool_id)
      , safe_pool_{nullptr}
      , unsafe_pool_{nullptr}
      , safe_pool_count_(0)
      , unsafe_pool_count_(0) {
    this->reserve(prefill);
  }
  ~DescriptorPool() {
    this->send_unsafe_to_manager();
    this->send_safe_to_manager();
  }

  /**
   * Allocates an extra `num_descriptors` elements to the pool.
   */
  void reserve(size_t num_descriptors = TERVEL_MEM_RC_MIN_NODES);

  /**
   * Constructs and returns a descriptor. Arguments are forwarded to the
   * constructor of the given descriptor type. User should call free_descriptor
   * on the returned pointer when they are done with it to avoid memory leaks.
   */
  template<typename DescrType, typename... Args>
  DescrType * get_descriptor(Args&&... args);

  /**
   * Once a user is done with a descriptor, they should free it with this
   * method.
   *
   * @param descr The descriptor to free.
   * @param dont_check Don't check if the descriptor is being watched before
   *   freeing it. Use this flag if you know that no other thread has had access
   *   to this descriptor.
   * @param pool the pool to use when freeing the descriptor.
   */
  void free_descriptor(tervel::util::Descriptor *descr, bool dont_check=false);


 private:
  // -------------------------
  // FOR DEALING WITH ELEMENTS
  // -------------------------

  /**
   * Gets a free element. The local pool is checked for one first, then the
   * manager if there are no local ones, and if all else fails, a new one is
   * allocated using new.
   *
   * @param allocate_new If true and there are no free elements to retrieve from
   *   the pool, a new one is allocated. Otherwise, nullptr is returned.
   */
  PoolElement * get_from_pool(bool allocate_new = true);



  // -------------------------
  // FOR DEALING WITH MANAGERS
  // -------------------------

  /**
   * Sends the elements from the safe pool to the corresponding safe pool in
   * this pool's manager.
   */
  void send_safe_to_manager();

  /**
   * Sends the elements from the unsafe pool to the corresponding unsafe pool in
   * this pool's manager.
   */
  void send_unsafe_to_manager();

  /**
   * Sends a subset of the elements to the managers pool
   */
  void offload();

  // --------------------------------
  // DEALS WITH SAFE AND UNSAFE LISTS
  // --------------------------------

  /**
   * Releases the descriptor back to the safe pool. Caller relinquishes
   * ownership of descriptor. It's expected that the given descriptor was taken
   * from this pool to begin with.
   *
   * Adding a descriptor to the safe pool calls its 'on_return_to_pool'
   * method and its destructor.
   */
  void add_to_safe(tervel::util::Descriptor* descr);

  /**
   * Releases the descriptor back to the unsafe pool. Caller relinquishes
   * ownership of descriptor. It's expected that the given descriptor was taken
   * from this pool to begin with.
   *
   * See notes on add_to_safe()
   */
  void add_to_unsafe(tervel::util::Descriptor* descr);

  /**
   * Try to move elements from the unsafe pool to the safe pool.
   */
  void try_clear_unsafe_pool(bool dont_check = false);

  /** verifies that the length of the linked list matches the count
  */
  bool verify_pool_count(PoolElement *pool, uint64_t count);
  // -------
  // MEMBERS
  // -------

  /**
   * This pool's manager.
   */
  PoolManager *manager_;

  /**
   * The pool where excess elements are placed
   */
  uint64_t pool_id_;

  /**
   * A linked list of pool elements.  One can be assured that no thread will try
   * to access the descriptor of any element in this pool. They can't be freed
   * as some threads may still have access to the element itself and may try to
   * increment the refrence count.
   */
  PoolElement *safe_pool_ {nullptr};

  /**
   * A linked list of pool elements. Elements get released to this pool when
   * they're no longer needed, but some threads may still try to access the
   * descriptor in the element. After some time has passed, items generally move
   * from this pool to the safe_pool_
   */
  PoolElement *unsafe_pool_ {nullptr};

  /**
   * Two counters used to track the number of elements in the linked list.
   * this facilitates the detection of when there are too many elements.
   */
  uint64_t safe_pool_count_ {0};
  uint64_t unsafe_pool_count_ {0};

  DISALLOW_COPY_AND_ASSIGN(DescriptorPool);
};

// IMPLEMENTATIONS
// ===============

template<typename DescrType, typename... Args>
DescrType * DescriptorPool::get_descriptor(Args&&... args) {
  PoolElement *elem = this->get_from_pool();
  if (elem == nullptr) {
    return nullptr;
  } else {
    elem->init_descriptor<DescrType>(std::forward<Args>(args)...);
    DescrType * descr = reinterpret_cast<DescrType *>(elem->descriptor());
    return descr;
  }
}

}  // namespace rc
}  // namespace memory
}  // namespace util
}  // namespace tervel

#endif  // TERVEL_MEMORY_RC_DESCRIPTOR_POOL_H_

