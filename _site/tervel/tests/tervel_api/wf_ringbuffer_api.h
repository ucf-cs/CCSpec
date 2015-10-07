/*
#The MIT License (MIT)
#
#Copyright (c) 2015 University of Central Florida's Computer Software Engineering
#Scalable & Secure Systems (CSE - S3) Lab
#
#Permission is hereby granted, free of charge, to any person obtaining a copy
#of this software and associated documentation files (the "Software"), to deal
#in the Software without restriction, including without limitation the rights
#to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#copies of the Software, and to permit persons to whom the Software is
#furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in
#all copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#THE SOFTWARE.
#
*/

#ifndef DS_API_H_
#define DS_API_H_


#include <string>
#include <tervel/util/info.h>
#include <tervel/util/thread_context.h>
#include <tervel/util/tervel.h>

#include <tervel/containers/wf/ring-buffer/ring_buffer.h>


typedef unsigned char Value_o;

class WrapperType;

typedef tervel::containers::wf::RingBuffer<WrapperType *> container_t;

class WrapperType : public container_t::Value {
 public:
  WrapperType(Value_o x) : x_(x) {};
  Value_o value() { return x_; };
  // std::string toString() {
  //   // uint64_t x = (thread_id << 56) | loop_count;
  //   uint64_t loop = x_ & 0x00FFFFFFFFFFFFFF;
  //   uint64_t tid = x_ >> 56;
  //   return "TID: " + std::to_string(tid) + " LC: " + std::to_string(loop);
  // }
 private:
  const Value_o x_;
};


#include "../src/main.h"

DEFINE_int32(prefill, 0, "The number elements to place in the buffer on init.");
DEFINE_int32(capacity, 0, "The capacity of the buffer.");

#define DS_DECLARE_CODE \
  tervel::Tervel* tervel_obj; \
  container_t *container;

#define DS_DESTORY_CODE

#define DS_ATTACH_THREAD \
tervel::ThreadContext* thread_context __attribute__((unused)); \
thread_context = new tervel::ThreadContext(tervel_obj);

#define DS_DETACH_THREAD

#define DS_INIT_CODE \
tervel_obj = new tervel::Tervel(FLAGS_num_threads+1); \
DS_ATTACH_THREAD \
container = new container_t(FLAGS_capacity); \
\
Value_o x = 1; \
for (int i = 0; i < FLAGS_prefill; i++) { \
  WrapperType *temp = new WrapperType(x); \
  container->enqueue(temp); \
  if (x == 0) x = 1; \
} \

#define DS_NAME "WF Ring Buffer"

#define DS_CONFIG_STR \
   "\n" _DS_CONFIG_INDENT "prefill : " + std::to_string(FLAGS_prefill) +"" + \
   "\n" _DS_CONFIG_INDENT "capacity : " + std::to_string(FLAGS_capacity) +"" + tervel_obj->get_config_str() + ""

#define DS_STATE_STR " "

#define OP_RAND \
  /* std::uniform_int_distribution<Value_o> random(1, UINT_MAX); */ \
  int ecount = 0;


#define OP_CODE \
  MACRO_OP_MAKER(0, { \
    /* Value_o value = random(); */ \
    Value_o value = ecount++;\
    if (ecount == 0) ecount++; \
    WrapperType *temp = new WrapperType(value); \
    opRes = container->enqueue(temp); \
  } \
  ) \
 MACRO_OP_MAKER(1, { \
      WrapperType *value; \
      opRes = container->dequeue(value); \
    } \
  )

#define DS_OP_NAMES "enqueue", "dequeue"

#define DS_OP_COUNT 2


inline void sanity_check(container_t *container) {};

#endif  // DS_API_H_

