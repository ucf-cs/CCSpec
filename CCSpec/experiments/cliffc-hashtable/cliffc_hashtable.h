#ifndef CLIFFC_HASHTABLE_H
#define CLIFFC_HASHTABLE_H

#include <iostream>
#include <atomic>
#include "stdio.h" 
//#include <common.h>
#ifdef STANDALONE
#include <assert.h>
#define MODEL_ASSERT assert 
#else
#include <model-assert.h>
#endif
#include <stdlib.h>

using namespace std;

/**
	This header file declares and defines a simplified version of Cliff Click's
	NonblockingHashMap. It contains all the necessary structrues and main
	functions. In simplified_cliffc_hashtable.cc file, it has the definition for
	the static fields.
*/

template<typename TypeK, typename TypeV>
class cliffc_hashtable;

/**
	Corresponding the the Object[] array in Cliff Click's Java implementation.
	It keeps the first two slots for CHM (Hashtable control unit) and the hash
	records (an array of hash used for fast negative key-equality check).
*/
struct kvs_data {
	int _size;
	atomic<void*> *_data;
	
	kvs_data(int sz) {
		_size = sz;
		int real_size = sz * 2 + 2;
		_data = new atomic<void*>[real_size];
		// The control block should be initialized in resize()
		// Init the hash record array
		int *hashes = new int[_size];
		int i;
		for (i = 0; i < _size; i++) {
			hashes[i] = 0;
		}
		// Init the data to Null slot
		for (i = 2; i < real_size; i++) {
			_data[i].store(NULL, memory_order_seq_cst);
		}
		_data[1].store(hashes, memory_order_seq_cst);
	}

	~kvs_data() {
		int *hashes = (int*) _data[1].load(memory_order_seq_cst);
		delete hashes;
		delete[] _data;
	}
};

struct slot {
	bool _prime;
	void *_ptr;

	slot(bool prime, void *ptr) {
		_prime = prime;
		_ptr = ptr;
	}
};


/**
	TypeK must have defined function "int hashCode()" which return the hash
	code for the its object, and "int equals(TypeK anotherKey)" which is
	used to judge equality.
	TypeK and TypeV should define their own copy constructor.
*/
/**
	@Begin
	@Class_begin
	@End
*/
template<typename TypeK, typename TypeV>
class cliffc_hashtable {
	/**
		# The synchronization we have for the hashtable gives us the property of
		# serializability, so we should have a sequential hashtable when we check the
		# correctness. The key thing is to identify all the commit point.
	
		@Begin
		@Options:
			LANG = CPP;
			CLASS = cliffc_hashtable;
		@Global_define:
			@DeclareVar:
			spec_table *map;
			spec_table *id_map;
			id_tag_t *tag;
			@InitVar:
				map = new_spec_table_default(equals_key);
				id_map = new_spec_table_default(equals_id);
				tag = new_id_tag();

			@DefineFunc:
			bool equals_key(void *ptr1, void *ptr2) {
				TypeK *key1 = (TypeK*) ptr1,
					*key2 = (TypeK*) ptr2;
				if (key1 == NULL || key2 == NULL)
					return false;
				return key1->equals(key2);
			}
			
			@DefineFunc:
			bool equals_val(void *ptr1, void *ptr2) {
				if (ptr1 == ptr2)
					return true;
				TypeV *val1 = (TypeV*) ptr1,
					*val2 = (TypeV*) ptr2;
				if (val1 == NULL || val2 == NULL)
					return false;
				return val1->equals(val2);
			}

			@DefineFunc:
			bool equals_id(void *ptr1, void *ptr2) {
				id_tag_t *id1 = (id_tag_t*) ptr1,
					*id2 = (id_tag_t*) ptr2;
				if (id1 == NULL || id2 == NULL)
					return false;
				return (*id1).tag == (*id2).tag;
			}

			@DefineFunc:
			# Update the tag for the current key slot if the corresponding tag
			# is NULL, otherwise just return that tag. It will update the next
			# available tag too if it requires a new tag for that key slot.
			call_id_t getKeyTag(TypeK *key) {
				if (!spec_table_contains(id_map, key)) {
					call_id_t cur_id = current(tag);
					spec_table_put(id_map, key, (void*) cur_id);
					next(tag);
					return cur_id;
				} else {
					call_id_t res = (call_id_t) spec_table_get(id_map, key);
					return res;
				}
			}
		@Happens_before:
			Put->Get
			Put->Put
		@End
	*/

friend class CHM;
	/**
		The control structure for the hashtable
	*/
	private:
	class CHM {
		friend class cliffc_hashtable;
		private:
		atomic<kvs_data*> _newkvs;
		
		// Size of active K,V pairs
		atomic_int _size;
	
		// Count of used slots
		atomic_int _slots;
		
		// The next part of the table to copy
		atomic_int _copy_idx;
		
		// Work-done reporting
		atomic_int _copy_done;
	
		public:
		CHM(int size) {
			_newkvs.store(NULL, memory_order_seq_cst);
			_size.store(size, memory_order_seq_cst);
			_slots.store(0, memory_order_seq_cst);
	
			_copy_idx.store(0, memory_order_seq_cst);
			_copy_done.store(0, memory_order_seq_cst);
		}
	
		~CHM() {}
		
		private:
			
		// Heuristic to decide if the table is too full
		bool table_full(int reprobe_cnt, int len) {
			return
				reprobe_cnt >= REPROBE_LIMIT &&
				_slots.load(memory_order_seq_cst) >= reprobe_limit(len);
		}
	
		kvs_data* resize(cliffc_hashtable *topmap, kvs_data *kvs) {
			//model_print("resizing...\n");
			/**** FIXME: miss ****/
			kvs_data *newkvs = _newkvs.load(memory_order_seq_cst);
			if (newkvs != NULL)
				return newkvs;
	
			// No copy in-progress, start one; Only double the table size
			int oldlen = kvs->_size;
			int sz = _size.load(memory_order_seq_cst);
			int newsz = sz;
			
			// Just follow Cliff Click's heuristic to decide the new size
			if (sz >= (oldlen >> 2)) { // If we are 25% full
				newsz = oldlen << 1; // Double size
				if (sz >= (oldlen >> 1))
					newsz = oldlen << 2; // Double double size
			}
	
			// We do not record the record timestamp
			if (newsz <= oldlen) newsz = oldlen << 1;
			// Do not shrink ever
			if (newsz < oldlen) newsz = oldlen;
	
			// Last check cause the 'new' below is expensive
			/**** FIXME: miss ****/
			newkvs = _newkvs.load(memory_order_seq_cst);
			//model_print("hey1\n");
			if (newkvs != NULL) return newkvs;
	
			newkvs = new kvs_data(newsz);
			void *chm = (void*) new CHM(sz);
			//model_print("hey2\n");
			newkvs->_data[0].store(chm, memory_order_seq_cst);
	
			kvs_data *cur_newkvs; 
			// Another check after the slow allocation
			/**** FIXME: miss ****/
			if ((cur_newkvs = _newkvs.load(memory_order_seq_cst)) != NULL)
				return cur_newkvs;
			// CAS the _newkvs to the allocated table
			kvs_data *desired = (kvs_data*) NULL;
			kvs_data *expected = (kvs_data*) newkvs; 
			/**** FIXME: miss ****/
			//model_print("release in resize!\n"); 
			if (!_newkvs.compare_exchange_strong(desired, expected, memory_order_seq_cst,
					memory_order_seq_cst)) {
				// Should clean the allocated area
				delete newkvs;
				/**** FIXME: miss ****/
				newkvs = _newkvs.load(memory_order_seq_cst);
			}
			return newkvs;
		}
	
		void help_copy_impl(cliffc_hashtable *topmap, kvs_data *oldkvs,
			bool copy_all) {
			MODEL_ASSERT (get_chm(oldkvs) == this);
			/**** FIXME: miss ****/
			kvs_data *newkvs = _newkvs.load(memory_order_seq_cst);
			int oldlen = oldkvs->_size;
			int min_copy_work = oldlen > 1024 ? 1024 : oldlen;
		
			// Just follow Cliff Click's code here
			int panic_start = -1;
			int copyidx;
			while (_copy_done.load(memory_order_seq_cst) < oldlen) {
				copyidx = _copy_idx.load(memory_order_seq_cst);
				if (panic_start == -1) { // No painc
					copyidx = _copy_idx.load(memory_order_seq_cst);
					while (copyidx < (oldlen << 1) &&
						!_copy_idx.compare_exchange_strong(copyidx, copyidx +
							min_copy_work, memory_order_seq_cst, memory_order_seq_cst))
						copyidx = _copy_idx.load(memory_order_seq_cst);
					if (!(copyidx < (oldlen << 1)))
						panic_start = copyidx;
				}
	
				// Now copy the chunk of work we claimed
				int workdone = 0;
				for (int i = 0; i < min_copy_work; i++)
					if (copy_slot(topmap, (copyidx + i) & (oldlen - 1), oldkvs,
						newkvs))
						workdone++;
				if (workdone > 0)
					copy_check_and_promote(topmap, oldkvs, workdone);
	
				copyidx += min_copy_work;
				if (!copy_all && panic_start == -1)
					return; // We are done with the work we claim
			}
			copy_check_and_promote(topmap, oldkvs, 0); // See if we can promote
		}
	
		kvs_data* copy_slot_and_check(cliffc_hashtable *topmap, kvs_data
			*oldkvs, int idx, void *should_help) {
			/**** FIXME: miss ****/
			kvs_data *newkvs = _newkvs.load(memory_order_seq_cst);
			// We're only here cause the caller saw a Prime
			if (copy_slot(topmap, idx, oldkvs, newkvs))
				copy_check_and_promote(topmap, oldkvs, 1); // Record the slot copied
			return (should_help == NULL) ? newkvs : topmap->help_copy(newkvs);
		}
	
		void copy_check_and_promote(cliffc_hashtable *topmap, kvs_data*
			oldkvs, int workdone) {
			int oldlen = oldkvs->_size;
			int copyDone = _copy_done.load(memory_order_seq_cst);
			if (workdone > 0) {
				while (true) {
					copyDone = _copy_done.load(memory_order_seq_cst);
					if (_copy_done.compare_exchange_weak(copyDone, copyDone +
						workdone, memory_order_seq_cst, memory_order_seq_cst))
						break;
				}
			}
	
			// Promote the new table to the current table
			if (copyDone + workdone == oldlen &&
				topmap->_kvs.load(memory_order_seq_cst) == oldkvs) {
				/**** FIXME: miss ****/
				kvs_data *newkvs = _newkvs.load(memory_order_seq_cst);
				/**** CDSChecker error ****/
				topmap->_kvs.compare_exchange_strong(oldkvs, newkvs, memory_order_seq_cst,
					memory_order_seq_cst);
			}
		}
	
		bool copy_slot(cliffc_hashtable *topmap, int idx, kvs_data *oldkvs,
			kvs_data *newkvs) {
			slot *key_slot;
			while ((key_slot = key(oldkvs, idx)) == NULL)
				CAS_key(oldkvs, idx, NULL, TOMBSTONE);
	
			// First CAS old to Prime
			slot *oldval = val(oldkvs, idx);
			while (!is_prime(oldval)) {
				slot *box = (oldval == NULL || oldval == TOMBSTONE)
					? TOMBPRIME : new slot(true, oldval->_ptr);
				if (CAS_val(oldkvs, idx, oldval, box)) {
					if (box == TOMBPRIME)
						return 1; // Copy done
					// Otherwise we CAS'd the box
					oldval = box; // Record updated oldval
					break;
				}
				oldval = val(oldkvs, idx); // Else re-try
			}
	
			if (oldval == TOMBPRIME) return false; // Copy already completed here
	
			slot *old_unboxed = new slot(false, oldval->_ptr);
			int copied_into_new = (putIfMatch(topmap, newkvs, key_slot, old_unboxed,
				NULL) == NULL);
	
			// Old value is exposed in the new table
			while (!CAS_val(oldkvs, idx, oldval, TOMBPRIME))
				oldval = val(oldkvs, idx);
	
			return copied_into_new;
		}
	};

	

	private:
	static const int Default_Init_Size = 4; // Intial table size

	static slot* const MATCH_ANY;
	static slot* const NO_MATCH_OLD;

	static slot* const TOMBPRIME;
	static slot* const TOMBSTONE;

	static const int REPROBE_LIMIT = 10; // Forces a table-resize

	atomic<kvs_data*> _kvs;

	public:
	cliffc_hashtable() {
		// Should initialize the CHM for the construction of the table
		// For other CHM in kvs_data, they should be initialzed in resize()
		// because the size is determined dynamically
		/**
			@Begin
			@Entry_point
			@End
		*/
		kvs_data *kvs = new kvs_data(Default_Init_Size);
		void *chm = (void*) new CHM(0);
		kvs->_data[0].store(chm, memory_order_seq_cst);
		_kvs.store(kvs, memory_order_seq_cst);
		
		//ANNOTATION
		//Linearizability
		std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    
		//Sequential Consistency
		//std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
		//Quiescent
		//std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
		correctness_condition(expression);
	}

	cliffc_hashtable(int init_size) {
		// Should initialize the CHM for the construction of the table
		// For other CHM in kvs_data, they should be initialzed in resize()
		// because the size is determined dynamically

		/**
			@Begin
			@Entry_point
			@End
		*/
		kvs_data *kvs = new kvs_data(init_size);
		void *chm = (void*) new CHM(0);
		kvs->_data[0].store(chm, memory_order_seq_cst);
		_kvs.store(kvs, memory_order_seq_cst);

		//ANNOTATION
		//Linearizability
		//std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");    
		//Sequential Consistency
		//std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_tid() == h.s[n].get_tid()) && (h.s[m].get_type() == RESPONSE) &&  (h.s[n].get_type() == INVOCATION)){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
		//Quiescent
		std::string expression("for(n=0;n<h.length;n++){ for(m=0;m<n;m++){ if((h.s[m].get_type() == RESPONSE) && (h.s[n].get_type() == INVOCATION) && Exists k: m <= k < n (Forall j: 0 <= j < h.p (is_active(k, j) == false))){method_id(m, h.s[m].get_tid()) happens_before method_id(n, h.s[n].get_tid());} } }");
		correctness_condition(expression);
	}

	/**
		@Begin
		@Interface: Get
		//@Commit_point_set: Get_Point1 | Get_Point2 | Get_ReadKVS | Get_ReadNewKVS | Get_Clear
		@Commit_point_set: Get_Point1 | Get_Point2 | Get_Clear
		//@Commit_point_set: Get_Point1 | Get_Point2 | Get_Point3
		@ID: getKeyTag(key)
		@Action:
			TypeV *_Old_Val = (TypeV*) spec_table_get(map, key);
			//bool passed = equals_val(_Old_Val, __RET__);
			bool passed = false;
			if (!passed) {
				int old = _Old_Val == NULL ? 0 : _Old_Val->_val;
				int ret = __RET__ == NULL ? 0 : __RET__->_val;
				//model_print("Get: key: %d, _Old_Val: %d, RET: %d\n",
				//key->_val, old, ret);
			}
		@Post_check:
			//__RET__ == NULL ? true : equals_val(_Old_Val, __RET__)
			equals_val(_Old_Val, __RET__)
		@End
	*/
	TypeV* get(TypeK *key) {
		std::string str1("get"); //ANNOTATION
		function_call(str1, INVOCATION, (uint64_t) key); //ANNOTATION

		slot *key_slot = new slot(false, key);
		int fullhash = hash(key_slot);
		/**** CDSChecker error ****/
		kvs_data *kvs = _kvs.load(memory_order_seq_cst);
		/**
			//@Begin
			@Commit_point_define_check: true
			@Label: Get_ReadKVS
			@End
		*/
		slot *V = get_impl(this, kvs, key_slot, fullhash);
		if (V == NULL) 
		{
			function_call(str1, RESPONSE, (uint64_t) NULL); //ANNOTATION
			return NULL;
		}
		MODEL_ASSERT (!is_prime(V));

		function_call(str1, RESPONSE, (uint64_t) V->_ptr); //ANNOTATION
		return (TypeV*) V->_ptr;
	}

	/**
		@Begin
		@Interface: Put
		//@Commit_point_set: Put_Point | Put_ReadKVS | Put_ReadNewKVS | Put_WriteKey
		@Commit_point_set: Put_Point | Put_WriteKey
		@ID: getKeyTag(key)
		@Action:
			# Remember this old value at checking point
			TypeV *_Old_Val = (TypeV*) spec_table_get(map, key);
			spec_table_put(map, key, val);
			//bool passed = equals_val(__RET__, _Old_Val);
			bool passed = false;
			if (!passed) {
				int old = _Old_Val == NULL ? 0 : _Old_Val->_val;
				int ret = __RET__ == NULL ? 0 : __RET__->_val;
				//model_print("Put: key: %d, val: %d, _Old_Val: %d, RET: %d\n",
				//	key->_val, val->_val, old, ret);
			}
		@Post_check:
			equals_val(__RET__, _Old_Val)
		@End
	*/
	TypeV* put(TypeK *key, TypeV *val) {

		std::string str1("put"); //ANNOTATION
		function_call(str1, INVOCATION, (uint64_t) key, (uint64_t) val); //ANNOTATION

		TypeV *res = putIfMatch(key, val, NO_MATCH_OLD);
		function_call(str1, RESPONSE, (uint64_t) res); //ANNOTATION

		//return putIfMatch(key, val, NO_MATCH_OLD);
		return res;
	}

	/**
//		@Begin
		@Interface: PutIfAbsent
		@Commit_point_set:
			Write_Success_Point | PutIfAbsent_Fail_Point
		@Condition: !spec_table_contains(map, key)
		@HB_condition:
			COND_PutIfAbsentSucc :: __RET__ == NULL
		@ID: getKeyTag(key)
		@Action:
			void *_Old_Val = spec_table_get(map, key);
			if (__COND_SAT__)
				spec_table_put(map, key, value);
		@Post_check:
			__COND_SAT__ ? __RET__ == NULL : equals_val(_Old_Val, __RET__) 
		@End
	*/
	TypeV* putIfAbsent(TypeK *key, TypeV *value) {
		std::string str1("put"); //ANNOTATION
		function_call(str1, INVOCATION, (uint64_t) key, (uint64_t) value); //ANNOTATION

		TypeV *res = putIfMatch(key, val, TOMBSTONE);
		function_call(str1, RESPONSE, (uint64_t) res); //ANNOTATION

		//return putIfMatch(key, val, TOMBSTONE);
		return res;
	}

	/**
//		@Begin
		@Interface: RemoveAny
		@Commit_point_set: Write_Success_Point
		@ID: getKeyTag(key)
		@Action:
			void *_Old_Val = spec_table_get(map, key);
			spec_table_put(map, key, NULL);
		@Post_check:
			equals_val(__RET__, _Old_Val)
		@End
	*/
	TypeV* remove(TypeK *key) {
		std::string str1("remove"); //ANNOTATION
		function_call(str1, INVOCATION, (uint64_t) key); //ANNOTATION

		TypeV* res = putIfMatch(key, TOMBSTONE, NO_MATCH_OLD);
		function_call(str1, RESPONSE, (uint64_t) res); //ANNOTATION

		//return putIfMatch(key, TOMBSTONE, NO_MATCH_OLD);	
		return res;
	}

	/**
//		@Begin
		@Interface: RemoveIfMatch
		@Commit_point_set:
			Write_Success_Point | RemoveIfMatch_Fail_Point
		@Condition:
			equals_val(spec_table_get(map, key), val)
		@HB_condition:
			COND_RemoveIfMatchSucc :: __RET__ == true
		@ID: getKeyTag(key)
		@Action:
			if (__COND_SAT__)
				spec_table_put(map, key, NULL);
		@Post_check:
			__COND_SAT__ ? __RET__ : !__RET__
		@End
	*/
	bool remove(TypeK *key, TypeV *val) {
		std::string str1("remove"); //ANNOTATION
		function_call(str1, INVOCATION, (uint64_t) key); //ANNOTATION

		slot *val_slot = val == NULL ? NULL : new slot(false, val);

		bool res = putIfMatch(key, TOMBSTONE, val) == val;

		if(res)
			function_call(str1, RESPONSE, (uint64_t) val); //ANNOTATION
		else
			function_call(str1, RESPONSE, (uint64_t) NULL); //ANNOTATION

		//return putIfMatch(key, TOMBSTONE, val) == val;
		return res;
	}

	/**
//		@Begin
		@Interface: ReplaceAny
		@Commit_point_set:
			Write_Success_Point
		@ID: getKeyTag(key)
		@Action:
			void *_Old_Val = spec_table_get(map, key);
		@Post_check:
			equals_val(__RET__, _Old_Val)
		@End
	*/
	TypeV* replace(TypeK *key, TypeV *val) {
		return putIfMatch(key, val, MATCH_ANY);
	}

	/**
//		@Begin
		@Interface: ReplaceIfMatch
		@Commit_point_set:
			Write_Success_Point | ReplaceIfMatch_Fail_Point
		@Condition:
			equals_val(spec_table_get(map, key), oldval)
		@HB_condition:
			COND_ReplaceIfMatchSucc :: __RET__ == true
		@ID: getKeyTag(key)
		@Action:
			if (__COND_SAT__)
				spec_table_put(map, key, newval);
		@Post_check:
			__COND_SAT__ ? __RET__ : !__RET__
		@End
	*/
	bool replace(TypeK *key, TypeV *oldval, TypeV *newval) {
		return putIfMatch(key, newval, oldval) == oldval;
	}

	private:
	static CHM* get_chm(kvs_data* kvs) {
		CHM *res = (CHM*) kvs->_data[0].load(memory_order_seq_cst);
		return res;
	}

	static int* get_hashes(kvs_data *kvs) {
		return (int *) kvs->_data[1].load(memory_order_seq_cst);
	}
	
	// Preserve happens-before semantics on newly inserted keys
	static inline slot* key(kvs_data *kvs, int idx) {
		MODEL_ASSERT (idx >= 0 && idx < kvs->_size);
		// Corresponding to the volatile read in get_impl() and putIfMatch in
		// Cliff Click's Java implementation
		slot *res = (slot*) kvs->_data[idx * 2 + 2].load(memory_order_seq_cst);
		/**
			@Begin
			# This is a complicated potential commit point since many many functions are
			# calling val().
			@Potential_commit_point_define: true
			@Label: Read_Key_Point
			@End
		*/
		return res;
	}

	/**
		The atomic operation in val() function is a "potential" commit point,
		which means in some case it is a real commit point while it is not for
		some other cases. This so happens because the val() function is such a
		fundamental function that many internal operation will call. Our
		strategy is that we label any potential commit points and check if they
		really are the commit points later.
	*/
	// Preserve happens-before semantics on newly inserted values
	static inline slot* val(kvs_data *kvs, int idx) {
		MODEL_ASSERT (idx >= 0 && idx < kvs->_size);
		// Corresponding to the volatile read in get_impl() and putIfMatch in
		// Cliff Click's Java implementation
		/**** CDSChecker error & hb violation ****/
		slot *res = (slot*) kvs->_data[idx * 2 + 3].load(memory_order_seq_cst);
		/**
			@Begin
			# This is a complicated potential commit point since many many functions are
			# calling val().
			@Potential_commit_point_define: true
			@Label: Read_Val_Point
			@End
		*/
		return res;


	}

	static int hash(slot *key_slot) {
		MODEL_ASSERT(key_slot != NULL && key_slot->_ptr != NULL);
		TypeK* key = (TypeK*) key_slot->_ptr;
		int h = key->hashCode();
		// Spread bits according to Cliff Click's code
		h += (h << 15) ^ 0xffffcd7d;
		h ^= (h >> 10);
		h += (h << 3);
		h ^= (h >> 6);
		h += (h << 2) + (h << 14);
		return h ^ (h >> 16);
	}
	
	// Heuristic to decide if reprobed too many times. 
	// Be careful here: Running over the limit on a 'get' acts as a 'miss'; on a
	// put it triggers a table resize. Several places MUST have exact agreement.
	static int reprobe_limit(int len) {
		return REPROBE_LIMIT + (len >> 2);
	}
	
	static inline bool is_prime(slot *val) {
		return (val != NULL) && val->_prime;
	}

	// Check for key equality. Try direct pointer comparison first (fast
	// negative teset) and then the full 'equals' call
	static bool keyeq(slot *K, slot *key_slot, int *hashes, int hash,
		int fullhash) {
		// Caller should've checked this.
		MODEL_ASSERT (K != NULL);
		TypeK* key_ptr = (TypeK*) key_slot->_ptr;
		return
			K == key_slot ||
				((hashes[hash] == 0 || hashes[hash] == fullhash) &&
				K != TOMBSTONE &&
				key_ptr->equals(K->_ptr));
	}

	static bool valeq(slot *val_slot1, slot *val_slot2) {
		MODEL_ASSERT (val_slot1 != NULL);
		TypeK* ptr1 = (TypeV*) val_slot1->_ptr;
		if (val_slot2 == NULL || ptr1 == NULL) return false;
		return ptr1->equals(val_slot2->_ptr);
	}
	
	// Together with key() preserve the happens-before relationship on newly
	// inserted keys
	static inline bool CAS_key(kvs_data *kvs, int idx, void *expected, void *desired) {
		bool res = kvs->_data[2 * idx + 2].compare_exchange_strong(expected,
			desired, memory_order_seq_cst, memory_order_seq_cst);
		/**
			# If it is a successful put instead of a copy or any other internal
			# operantions, expected != NULL
			@Begin
			@Potential_commit_point_define: res
			@Label: Write_Key_Point
			@End
		*/
		return res;
	}

	/**
		Same as the val() function, we only label the CAS operation as the
		potential commit point.
	*/
	// Together with val() preserve the happens-before relationship on newly
	// inserted values
	static inline bool CAS_val(kvs_data *kvs, int idx, void *expected, void
		*desired) {
		/**** CDSChecker error & HB violation ****/
		bool res =  kvs->_data[2 * idx + 3].compare_exchange_strong(expected,
			desired, memory_order_seq_cst, memory_order_seq_cst);
		/**
			# If it is a successful put instead of a copy or any other internal
			# operantions, expected != NULL
			@Begin
			@Potential_commit_point_define: res
			@Label: Write_Val_Point
			@End
		*/
		return res;
	}

	slot* get_impl(cliffc_hashtable *topmap, kvs_data *kvs, slot* key_slot, int
		fullhash) {
		int len = kvs->_size;
		CHM *chm = get_chm(kvs);
		int *hashes = get_hashes(kvs);

		int idx = fullhash & (len - 1);
		int reprobe_cnt = 0;
		while (true) {
			slot *K = key(kvs, idx);
			/**
				@Begin
				@Commit_point_define: K == NULL
				@Potential_commit_point_label: Read_Key_Point
				@Label: Get_Point1
				@End
			*/
			slot *V = val(kvs, idx);
			
			if (K == NULL) {
				//model_print("Key is null\n");
				return NULL; // A miss
			}
			
			if (keyeq(K, key_slot, hashes, idx, fullhash)) {
				// Key hit! Check if table-resize in progress
				if (!is_prime(V)) {
					/**
						@Begin
						@Commit_point_clear: true
						@Label: Get_Clear
						@End
					*/

					/**
						@Begin
						@Commit_point_define: true
						@Potential_commit_point_label: Read_Val_Point
						@Label: Get_Point2
						@End
					*/
					return (V == TOMBSTONE) ? NULL : V; // Return this value
				}
				// Otherwise, finish the copy & retry in the new table
				return get_impl(topmap, chm->copy_slot_and_check(topmap, kvs,
					idx, key_slot), key_slot, fullhash);
			}

			if (++reprobe_cnt >= REPROBE_LIMIT ||
				key_slot == TOMBSTONE) {
				// Retry in new table
				// Atomic read can be here 
				/**** FIXME: miss ****/
				kvs_data *newkvs = chm->_newkvs.load(memory_order_seq_cst);
				/**
					//@Begin
					@Commit_point_define_check: true
					@Label: Get_ReadNewKVS
					@End
				*/
				return newkvs == NULL ? NULL : get_impl(topmap,
					topmap->help_copy(newkvs), key_slot, fullhash);
			}

			idx = (idx + 1) & (len - 1); // Reprobe by 1
		}
	}

	// A wrapper of the essential function putIfMatch()
	TypeV* putIfMatch(TypeK *key, TypeV *value, slot *old_val) {
		
		// TODO: Should throw an exception rather return NULL
		if (old_val == NULL) {
			return NULL;
		}
		slot *key_slot = new slot(false, key);

		slot *value_slot = new slot(false, value);
		/**** FIXME: miss ****/
		kvs_data *kvs = _kvs.load(memory_order_seq_cst);
		/**
			//@Begin
			@Commit_point_define_check: true
			@Label: Put_ReadKVS
			@End
		*/
		slot *res = putIfMatch(this, kvs, key_slot, value_slot, old_val);
		// Only when copy_slot() call putIfMatch() will it return NULL
		MODEL_ASSERT (res != NULL); 
		MODEL_ASSERT (!is_prime(res));

		return res == TOMBSTONE ? NULL : (TypeV*) res->_ptr;
	}

	/**
		Put, Remove, PutIfAbsent, etc will call this function. Return the old
		value. If the returned value is equals to the expVal (or expVal is
		NO_MATCH_OLD), then this function puts the val_slot to the table 'kvs'.
		Only copy_slot will pass a NULL expVal, and putIfMatch only returns a
		NULL if passed a NULL expVal.
	*/
	static slot* putIfMatch(cliffc_hashtable *topmap, kvs_data *kvs, slot
		*key_slot, slot *val_slot, slot *expVal) {
		MODEL_ASSERT (val_slot != NULL);
		MODEL_ASSERT (!is_prime(val_slot));
		MODEL_ASSERT (!is_prime(expVal));

		int fullhash = hash(key_slot);
		int len = kvs->_size;
		CHM *chm = get_chm(kvs);
		int *hashes = get_hashes(kvs);
		int idx = fullhash & (len - 1);

		// Claim a key slot
		int reprobe_cnt = 0;
		slot *K;
		slot *V;
		kvs_data *newkvs;
		
		while (true) { // Spin till we get a key slot
			K = key(kvs, idx);
			V = val(kvs, idx);
			if (K == NULL) { // Get a free slot
				if (val_slot == TOMBSTONE) return val_slot;
				// Claim the null key-slot
				if (CAS_key(kvs, idx, NULL, key_slot)) {
					/**
						@Begin
						@Commit_point_define: true
						@Potential_commit_point_label: Write_Key_Point
						@Label: Put_WriteKey
						@End
					*/
					chm->_slots.fetch_add(1, memory_order_seq_cst); // Inc key-slots-used count
					hashes[idx] = fullhash; // Memorize full hash
					break;
				}
				K = key(kvs, idx); // CAS failed, get updated value
				MODEL_ASSERT (K != NULL);
			}

			// Key slot not null, there exists a Key here
			if (keyeq(K, key_slot, hashes, idx, fullhash))
				break; // Got it
			
			// Notice that the logic here should be consistent with that of get.
			// The first predicate means too many reprobes means nothing in the
			// old table.
			if (++reprobe_cnt >= reprobe_limit(len) ||
				K == TOMBSTONE) { // Found a Tombstone key, no more keys
				newkvs = chm->resize(topmap, kvs);
				//model_print("resize1\n");
				// Help along an existing copy
				if (expVal != NULL) topmap->help_copy(newkvs);
				return putIfMatch(topmap, newkvs, key_slot, val_slot, expVal);
			}

			idx = (idx + 1) & (len - 1); // Reprobe
		} // End of spinning till we get a Key slot

		if (val_slot == V) return V; // Fast cutout for no-change
	
		// Here it tries to resize cause it doesn't want other threads to stop
		// its progress (eagerly try to resize soon)
		/**** FIXME: miss ****/
		newkvs = chm->_newkvs.load(memory_order_seq_cst);
		/**
			//@Begin
			@Commit_point_define_check: true
			@Label: Put_ReadNewKVS
			@End
		*/
		if (newkvs == NULL &&
			((V == NULL && chm->table_full(reprobe_cnt, len)) || is_prime(V))) {
			//model_print("resize2\n");
			newkvs = chm->resize(topmap, kvs); // Force the copy to start
		}
		
		// Finish the copy and then put it in the new table
		if (newkvs != NULL)
			return putIfMatch(topmap, chm->copy_slot_and_check(topmap, kvs, idx,
				expVal), key_slot, val_slot, expVal);
		
		// Decided to update the existing table
		while (true) {
			MODEL_ASSERT (!is_prime(V));

			if (expVal != NO_MATCH_OLD &&
				V != expVal &&
				(expVal != MATCH_ANY || V == TOMBSTONE || V == NULL) &&
				!(V == NULL && expVal == TOMBSTONE) &&
				(expVal == NULL || !valeq(expVal, V))) {
				/**
					//@Begin
					@Commit_point_define: expVal == TOMBSTONE
					@Potential_commit_point_label: Read_Val_Point
					@Label: PutIfAbsent_Fail_Point
						# This is a check for the PutIfAbsent() when the value
						# is not absent
					@End
				*/
				/**
					//@Begin
					@Commit_point_define: expVal != NULL && val_slot == TOMBSTONE
					@Potential_commit_point_label: Read_Val_Point
					@Label: RemoveIfMatch_Fail_Point
					@End
				*/
				/**
					//@Begin
					@Commit_point_define: expVal != NULL && !valeq(expVal, V)
					@Potential_commit_point_label: Read_Val_Point
					@Label: ReplaceIfMatch_Fail_Point
					@End
				*/
				return V; // Do not update!
			}

			if (CAS_val(kvs, idx, V, val_slot)) {
				/**
					@Begin
					# The only point where a successful put happens
					@Commit_point_define: true
					@Potential_commit_point_label: Write_Val_Point
					@Label: Put_Point
					@End
				*/
				if (expVal != NULL) { // Not called by a table-copy
					// CAS succeeded, should adjust size
					// Both normal put's and table-copy calls putIfMatch, but
					// table-copy does not increase the number of live K/V pairs
					if ((V == NULL || V == TOMBSTONE) &&
						val_slot != TOMBSTONE)
						chm->_size.fetch_add(1, memory_order_seq_cst);
					if (!(V == NULL || V == TOMBSTONE) &&
						val_slot == TOMBSTONE)
						chm->_size.fetch_add(-1, memory_order_seq_cst);
				}
				return (V == NULL && expVal != NULL) ? TOMBSTONE : V;
			}
			// Else CAS failed
			V = val(kvs, idx);
			if (is_prime(V))
				return putIfMatch(topmap, chm->copy_slot_and_check(topmap, kvs,
					idx, expVal), key_slot, val_slot, expVal);
		}
	}

	// Help along an existing table-resize. This is a fast cut-out wrapper.
	kvs_data* help_copy(kvs_data *helper) {
		/**** FIXME: miss ****/
		kvs_data *topkvs = _kvs.load(memory_order_seq_cst);
		CHM *topchm = get_chm(topkvs);
		// No cpy in progress
		if (topchm->_newkvs.load(memory_order_seq_cst) == NULL) return helper;
		topchm->help_copy_impl(this, topkvs, false);
		return helper;
	}
};
/**
	@Begin
	@Class_end
	@End
*/

#endif
