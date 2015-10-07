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
#ifndef TERVEL_CONTAINER_WF_HASH_MAP_WFHM_HASHMAP_H
#define TERVEL_CONTAINER_WF_HASH_MAP_WFHM_HASHMAP_H

#include <assert.h>
#include <atomic>
#include <cmath>
#include <stdlib.h>

#include <tervel/util/util.h>
// TODO(Steven):
//
// Document code
//
// Implement Progress Assurance.
//
// Test get_position function on keys > 64 bits
// Stronger Correctness Tests
//
namespace tervel {
namespace containers {
namespace wf {
/**
 * A default Functor implementation
 *
 */
template<class Key, class Value>
struct default_functor {
  Key hash(Key k) {
    return k;
  }

  bool key_equals(Key a, Key b) {
    return a == b;
  }
};



/**
 * A wait-free hash map implementation.
 *
 * TODO(steven): Provide general overview
 *
 * Functor should have the following functions:
 *   -Key hash(Key k) (where hash(a) == (hash(b) implies a == b
 *   -bool key_equals (Key a, Key b)
 *       Important Note: the hashed value of keys will be passed in.
 *
 */
template< class Key, class Value, class Functor = default_functor<Key, Value> >
class HashMapNoDelete {
 public:
  class ValueAccessor;

  HashMapNoDelete(uint64_t capacity, uint64_t expansion_rate = 3)
    : primary_array_size_(tervel::util::round_to_next_power_of_two(capacity))
    , primary_array_pow_(std::log2(primary_array_size_))
    , secondary_array_size_(std::pow(2, expansion_rate))
    , secondary_array_pow_(expansion_rate)
    , primary_array_(new Location[primary_array_size_]()) {

      size_.store(0);
      for (size_t i = 0; i < primary_array_size_; i++) {
	       primary_array_[i].store(nullptr);
      }

   }

  /**
   * Not Thread Safe!
   *   If it is a node type then the node will be freed
   *   If it is an array node then the destructor of the array node will free
   *     any nodes that are referenced it. This may cause more array node's to
   *     be freed. Stack can reach max_depth() in size.
   */
  ~HashMapNoDelete() {
    for (size_t i = 0; i < primary_array_size_; i++) {
      Node * temp = primary_array_[i].load();
      if (temp != nullptr) {
        delete temp;
      }
    }
  }  // ~ HashMap



  /**
   * This function returns true and initializes the passed ValueAccessor if the
   * key exists in the hash map. Initializing the ValueAccessor consists of
   * assigning storing a reference to the associated value and a reference to
   * the access counter. The access counter will have been increased by one.
   * Upon the destruction or re-initialization of the ValueAccessor, the access
   * counter will be decremented.
   *
   * The sequential complexity of this operation is O(max_depth()).
   *
   * @param key: the key to look up
   * @param va: the location to store the address of the value/access_counter
   * @return whether or not the key is present
   */
  bool at(Key key, ValueAccessor &va);

  /**
   * This function returns true if the key value pair was successfully inserted.
   * Otherwise it returns false.
   *
   * A key can fail to insert in the event the key is already present.
   *
   * The sequential complexity of this operation is O(max_depth()).
   *
   * @param key: The key to insert
   * @param value: The key's associated value
   * @return whether or not the the key/value was inserted
   */
  bool insert(Key key, Value value);


  /**
   * @return the number of keys in the hash map
   */
  size_t size() {
    return size_.load();
  };


  /**
   * This class is used to safe guard access to values.
   */
  class ValueAccessor {
   public:
    friend class HashMapNoDelete;
    ValueAccessor()
      : value_(nullptr) {}

    ~ValueAccessor() {}

    /**
     * @return the address of the value in the data_node.
     */
    Value* value() {
      return value_;
    };

    /**
     * @return whether or not this was initialized.
     */
    bool valid() {
      return (value_ != nullptr);
    };

    /**
     * Resets this value accessors,clearing the variables.
     */
    void reset() {
      value_ = nullptr;
    };

   private:
    /**
     * Initializes the value accessors.
     * @param value: the address of the value
     */
    void init(Value * value) {
      value_ = value;
    };

    Value * value_;
  };


  /**
   * @param key: The key
   * @param depth: The depth
   * @return the position this key belongs in at the specified depth.
   */
  uint64_t get_position(Key &key, size_t depth);

  /**
   * @return the maximum depth of the hash map, any depth beyond this would
   * not produce any non-zero positions.
   */
  uint64_t max_depth();

  /**
   * Outputs the positions a key belongs in at each depth.
   * Used for Debugging
   * @param key: The Key
   */
  void print_key(Key &key);

 private:
  class Node;
  friend class Node;
  typedef std::atomic<Node *> Location;


  /**
   * This class is used to differentiate between data_nodes and array_nodes/
   */
  class Node {
   public:
    Node() {}
    virtual ~Node() {}

    /**
     * @return whether or not this instance is an ArrayNode sub type
     */
    virtual bool is_array() = 0;

    /**
     * @return whether or not this instance is an DataNode sub type
     */
    virtual bool is_data() = 0;
  };

  /**
   * This class is used to hold the secondary array structure
   */
  class ArrayNode : public Node {
   public:
    explicit ArrayNode(uint64_t len)
      : len_(len)
      , internal_array_(new Location[len]()) {
        for (size_t i = 0; i < len_; i++) {
          internal_array_[i].store(nullptr);
        }
      }

    /**
     * See Notes on hash map destructor.
     */
    ~ArrayNode() {
      for (size_t i = 0; i < len_; i++) {
        Node * temp = internal_array_[i].load();
        if (temp != nullptr) {
          delete temp;
        }
      }
    }  // ~ArrayNode


    /**
     * @param pos: The position to get the address of.
     * @return the address of a position on the internal array
     */
    Location *access(uint64_t pos) {
      assert(pos < len_ && pos >=0);
      return &(internal_array_[pos]);
    }

    /**
     * @return whether or not this instance is an ArrayNode sub type
     */
    bool is_array() {
      return true;
    }

    /**
     * @return whether or not this instance is an DataNode sub type
     */
    bool is_data() {
      return false;
    }

   private:
    uint64_t len_;
    std::unique_ptr<Location[]> internal_array_;
  };

  /**
   * This class is used to hold a key and value pair.
   * It is hazard pointer protected.
   */
  class DataNode : public Node {
   public:
    explicit DataNode(Key k, Value v)
      : key_(k)
      , value_(v) {}

    ~DataNode() { }

    /**
     * @return whether or not this instance is an ArrayType sub type
     */
    bool is_array() {
      return false;
    }

    /**
     * @return whether or not this instance is an DataNode sub type
     */
    bool is_data() {
      return true;
    }

    Key key_;
    Value value_;
  };

  /**
   * Increases the capacity of the hash map by replacing a data node reference
   * with a reference to an array node containing a reference to that data node
   * @param loc: The location to expand at
   * @param curr_value: The current value  (data node) at the location
   * @param next_position: The position the data node belongs at the next depth.
   */
  void expand_map(Location * loc, Node * &curr_value, uint64_t next_position);



  const size_t primary_array_size_;
  const size_t primary_array_pow_;
  const size_t secondary_array_size_;
  const size_t secondary_array_pow_;

  std::atomic<uint64_t> size_;

  std::unique_ptr<Location[]> primary_array_;
};  // class wf hash map


template<class Key, class Value, class Functor>
bool HashMapNoDelete<Key, Value, Functor>::
at(Key key, ValueAccessor &va) {
  Functor functor;
  key = functor.hash(key);

  size_t depth = 0;
  uint64_t position = get_position(key, depth);
  Location *loc = &(primary_array_[position]);
  Node *curr_value;

  bool op_res = false;
  while (true) {
    curr_value = loc->load();

    if (curr_value == nullptr) {
      break;
    } else if (curr_value->is_array()) {
      ArrayNode * array_node = reinterpret_cast<ArrayNode *>(curr_value);
      depth++;
      position = get_position(key, depth);
      loc = array_node->access(position);
      continue;
    } else {
      assert(curr_value->is_data());
      DataNode * data_node = reinterpret_cast<DataNode *>(curr_value);

      if (functor.key_equals(data_node->key_, key)) {
        va.init(&(data_node->value_));
        op_res = true;
      }
      break;
    }
  }  // while true

  return op_res;
}  // at


template<class Key, class Value, class Functor>
bool HashMapNoDelete<Key, Value, Functor>::
insert(Key key, Value value) {
  Functor functor;
  key = functor.hash(key);

  DataNode * new_node = new DataNode(key, value);

  size_t depth = 0;
  uint64_t position = get_position(key, depth);
  Location *loc = &(primary_array_[position]);
  Node *curr_value = loc->load();

  bool op_res;
  while (true) {

    if (curr_value == nullptr) {
      if (loc->compare_exchange_strong(curr_value, new_node)) {
        size_.fetch_add(1);
        op_res = true;
        break;
      }
    } else if (curr_value->is_array()) {
      ArrayNode * array_node = reinterpret_cast<ArrayNode *>(curr_value);
      depth++;
      position = get_position(key, depth);
      loc = array_node->access(position);
      curr_value = loc->load();
    } else {  // it is a data node
      assert(curr_value->is_data());
      DataNode * data_node = reinterpret_cast<DataNode *>(curr_value);

      if (functor.key_equals(data_node->key_, key)) {
        op_res = false;
        break;
      } else {
        // Key differs, needs to expand...
        const uint64_t next_position =  get_position(data_node->key_, depth+1);
        expand_map(loc, curr_value, next_position);
      }   // else key differs
    }  // else it is a data node
  }  // while true

  if (!op_res) {
    assert(loc->load() != new_node);
    delete new_node;
  }
  return op_res;
}  // insert


template<class Key, class Value, class Functor>
void  HashMapNoDelete<Key, Value, Functor>::
expand_map(Location * loc, Node * &curr_value, uint64_t next_position) {
  assert(curr_value->is_data());

  ArrayNode * array_node = new ArrayNode(secondary_array_size_);
  array_node->access(next_position)->store(curr_value);
  assert(array_node->is_array());

  if (loc->compare_exchange_strong(curr_value, array_node)) {
    return;
  } else {
    assert(loc->load() != array_node);
    array_node->access(next_position)->store(nullptr);
    delete array_node;
  }
}  // expand

template<class Key, class Value, class Functor>
uint64_t HashMapNoDelete<Key, Value, Functor>::
get_position(Key &key, size_t depth) {
  const uint64_t *long_array = reinterpret_cast<uint64_t *>(&key);
  const size_t max_length = sizeof(Key) / (64 / 8);

  assert(depth <= max_depth());
  if (depth == 0) {
    // We need the first 'primary_array_pow_' bits
    assert(primary_array_pow_ < 64);

    uint64_t position = long_array[0] >> (64 - primary_array_pow_);

    assert(position < primary_array_size_);
    return position;
  } else {
    const int start_bit_offset = (depth-1)*secondary_array_pow_ +
        primary_array_pow_;  // Inclusive
    const int end_bit_offset = (depth)*secondary_array_pow_ +
        primary_array_pow_;   // Not inclusive

    const size_t start_idx = start_bit_offset / 64;
    const size_t start_idx_offset = start_bit_offset % 64;
    const size_t end_idx = end_bit_offset / 64;
    const size_t end_idx_offset = end_bit_offset % 64;

    assert(start_idx == end_idx || start_idx + 1 == end_idx);
    assert(end_idx <= max_length);

    // TODO(steven): add 0 padding to fill extra bits if the bits don't
    // divide evenly.
    if (start_idx == end_idx) {
      uint64_t value = long_array[start_idx];
      value = value << start_idx_offset;
      value = value >> (64 - secondary_array_pow_);

      assert(value < secondary_array_size_);
      return value;
    } else {
      uint64_t value = long_array[start_idx];
      value = value << start_idx_offset;
      value = value >> (64 - secondary_array_pow_ + end_idx_offset);
      value = value << (end_idx_offset);


      uint64_t value2;
      if (end_idx == max_length) {
        value2 = 0;
      } else {
        value2 = long_array[end_idx];
      }
      value2 = value2 >> (64 - end_idx_offset);

      uint64_t position = (value | value2);
      assert(position < secondary_array_size_);
      return position;
    }
  }
}  // get_position

template<class Key, class Value, class Functor>
uint64_t HashMapNoDelete<Key, Value, Functor>::
max_depth() {
  uint64_t max_depth = sizeof(Key)*8;
  max_depth -= primary_array_pow_;
  max_depth = std::ceil(max_depth / secondary_array_pow_);
  max_depth++;

  return max_depth;
}

template<class Key, class Value, class Functor>
void HashMapNoDelete<Key, Value, Functor>::
print_key(Key &key) {
  size_t max_depth_ = max_depth();
  std::cout << "K(" << key << ") :";
  for (size_t i = 0; i <= max_depth_; i++) {
    uint64_t temp = get_position(key, i);
    std::cout << temp << "-";
  }
  std::cout << "\n" << std::endl;
}  // print_key

}  // namespace wf
}  // namespace containers
}  // namespace tervel

#endif  // TERVEL_CONTAINER_WF_HASH_MAP_WFHM_HASHMAP_H