#ifndef __UNRELACY_H__
#define __UNRELACY_H__

#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <mutex>
#include <condition_variable>

#include <model-assert.h>
#include <librace.h>

#define $

#define ASSERT(expr) MODEL_ASSERT(expr)
#define RL_ASSERT(expr) MODEL_ASSERT(expr)

#define RL_NEW new
#define RL_DELETE(expr) delete expr

#define mo_seqcst memory_order_relaxed
#define mo_release memory_order_release
#define mo_acquire memory_order_acquire
#define mo_acq_rel memory_order_acq_rel
#define mo_relaxed memory_order_relaxed

namespace rl {

	/* This 'useless' struct is declared just so we can use partial template
	 * specialization in our store and load functions. */
	template <typename T, size_t n>
	struct useless {
		static void store(void *addr, T val);
		static T load(const void *addr);
	};

	template <typename T>
	struct useless<T, 1> {
		static void store(void *addr, T val) { store_8(addr, (uint8_t)val); }
		static T load(const void *addr) { return (T)load_8(addr); }
	};

	template <typename T>
	struct useless<T, 2> {
		static void store(void *addr, T val) { store_16(addr, (uint16_t)val); }
		static T load(const void *addr) { return (T)load_16(addr); }
	};

	template <typename T>
	struct useless<T, 4> {
		static void store(void *addr, T val) { store_32(addr, (uint32_t)val); }
		static T load(const void *addr) { return (T)load_32(addr); }
	};

	template <typename T>
	struct useless<T, 8> {
		static void store(void *addr, T val) { store_64(addr, (uint64_t)val); }
		static T load(const void *addr) { return (T)load_64(addr); }
	};

	template <typename T>
	struct var {
		var() { useless<T, sizeof(T)>::store(&value, 0); }
		var(T v) { useless<T, sizeof(T)>::store(&value, v); }
		var(var const& r) {
			value = r.value;
		}
		~var() { }

		void operator = (T v) { useless<T, sizeof(T)>::store(&value, v); }
		T operator () () { return useless<T, sizeof(T)>::load(&value); }
		void operator += (T v) {
			useless<T, sizeof(T)>::store(&value,
					useless<T, sizeof(T)>::load(&value) + v);
		}
		bool operator == (const struct var<T> v) const { return useless<T, sizeof(T)>::load(&value) == useless<T, sizeof(T)>::load(&v.value); }

		T value;
	};

	class backoff_t
	{
	 public:
		typedef int debug_info_param;
		void yield(debug_info_param info) { }
		void yield() { }
	};


	typedef backoff_t backoff;
	typedef backoff_t linear_backoff;
	typedef backoff_t exp_backoff;

}

#endif /* __UNRELACY_H__ */
