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
#ifndef TERVEL_CONTAINERS_WF_RINGBUFFER_RINGBUFFER_HELPER_H_
#define TERVEL_CONTAINERS_WF_RINGBUFFER_RINGBUFFER_HELPER_H_

#include <tervel/util/memory/hp/hp_element.h>
#include <tervel/util/memory/hp/hazard_pointer.h>

namespace tervel {
namespace containers {
namespace wf {

template<typename T>
class RingBuffer<T>::Helper : public tervel::util::memory::hp::Element {
 public:
  Helper(BufferOp *op, uintptr_t old_value)
   : op_(op)
   , old_value_(old_value) {}
  ~Helper() {}

  bool on_watch(std::atomic<void *> *address, void *expected);
  void * associate();
  bool valid();

  /**
   * @brief Returns a uintptr_t for the passed helper object
   * @details Returns a uintptr_t for the passed helper object by performing
   * a bitwise OR with h and oprec_lsb
   *
   * @param h the pointer to OR
   * @return the result of the bitwise or.
   */
  static inline uintptr_t HelperType(Helper *h);

  static inline bool isHelperType(uintptr_t val);

  static inline Helper *getHelperType(uintptr_t val);

  BufferOp *op_;
  const uintptr_t old_value_;

};


}  // namespace wf
}  // namespace containers
}  // namespace tervel

#endif  // TERVEL_CONTAINERS_WF_RINGBUFFER_RINGBUFFER_HELPER_H_
