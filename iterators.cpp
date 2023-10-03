
#include<iostream>
#include<iterator>

namespace boilerplate
{
// The idea is to create valid boilerplate iterators for every C++20 iterator type concept
// Since iterator types are built-up one on the other we start with the easiest one and work through...
//
// Note that the code in the methods is not meant to be correct nor even useful, it is just minimum code to
// compile correctly.

class dummy_value_type
{

};

//////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief Top-level virtual iterator only used to check against the top-level (input_or_output_iterator)
///        iterator concept
class input_or_output_iterator
{
public:
  using iterator_t = input_or_output_iterator;
  using difference_type = long; //  MUST BE signed !
  using value_type = dummy_value_type;
  using reference = value_type&;
  using pointer = value_type*; // LegacyIterator
  using rvalue_reference = value_type&&;

  input_or_output_iterator() = default; // NOTE: Not required, but used for testing
  input_or_output_iterator(const iterator_t& other) = default; // LegacyIterator
  input_or_output_iterator(iterator_t&& other) = default; // Required (movable)
  ~input_or_output_iterator() = default; // LegacyIterator

  iterator_t& operator=(const iterator_t& rh) { return *this; }

  void swap(iterator_t& other) {} // LegacyIterator

  value_type& operator*() const { static value_type ret{}; return ret; } // NOTE: const not requires by concept here

  iterator_t& operator++() { return *this; }
  iterator_t  operator++(int) { return iterator_t{}; } // NOTE: return type not enforced until forward_iterator
};

void swap(input_or_output_iterator& a, input_or_output_iterator& b) { a.swap(b); } // LegacyIterator

//////////////////////////////////////////////////////////////////////////////////////////////////
class output_iterator
{
public:
  using iterator_category = std::output_iterator_tag; // Legacy iterator
  using iterator_t = output_iterator;
  using difference_type = long; //  MUST BE signed !
  using value_type = dummy_value_type;
  using reference = value_type&;
  using pointer = value_type*; // LegacyIterator
  using rvalue_reference = value_type&&;

  output_iterator() = default; // NOTE: Not required, but used for testing
  output_iterator(const iterator_t& other) = default; // LegacyIterator
  output_iterator(iterator_t&& other) = default; // Required (movable)
  ~output_iterator() = default; // LegacyIterator

  iterator_t& operator=(const iterator_t& rh) { return *this; }

  void swap(iterator_t& other) {} // LegacyIterator

  value_type& operator*() { static value_type ret{}; return ret; }

  iterator_t& operator++() { return *this; }
  iterator_t  operator++(int) { return iterator_t{}; } // NOTE: return type not enforced until forward_iterator
};

void swap(output_iterator& a, output_iterator& b) { a.swap(b); } // LegacyIterator

//////////////////////////////////////////////////////////////////////////////////////////////////
class input_iterator
{
public:
  using iterator_category = std::input_iterator_tag; // Legacy iterator
  using iterator_t = input_iterator;
  using difference_type = long; //  MUST BE signed !
  using value_type = dummy_value_type;
  using reference = value_type&; // NEW
  using pointer = value_type*; // LegacyIterator
  using rvalue_reference = value_type&&; // NEW

  input_iterator() = default; // NOTE: Not required, but used for testing
  input_iterator(const input_iterator& other) = default; // LegacyIterator
  input_iterator(iterator_t&& other) = default; // Required (movable)

  iterator_t& operator=(const iterator_t& rh) { return *this; }

  void swap(iterator_t& other) {} // LegacyIterator

  value_type& operator*() const { static value_type ret{}; return ret; } // NEW: operator* must be const
  pointer operator->() const { static value_type ret{}; return &ret; } // LegacyInputIterator

  iterator_t& operator++() { return *this; }
  iterator_t  operator++(int) { return iterator_t{}; } // NOTE: return type not enforced until forward_iterator

  bool operator==(const iterator_t& rh) { return true; } // LegacyInputIterator
};

void swap(input_iterator& a, input_iterator& b) { a.swap(b); } // LegacyIterator

//////////////////////////////////////////////////////////////////////////////////////////////////
// Forward iterator compatible with std::forward_iteratro concept and LegacyForwwardConstuctor
//
// NOTE: LegacyForwardIterator: Forward iterators hast to provide multipass guarantee
//       - f a and b compare equal (a == b is contextually convertible to true) then either they are both non-dereferenceable or *a and *b are references bound to the same object.
//       - f *a and *b refer to the same object, then a == b
//       - Assignment through a mutable ForwardIterator iterator cannot invalidate the iterator (implicit due to reference defined as a true reference)
//       - Incrementing a copy of a does not change the value read from a (formally, either It is a raw pointer type or the expression (void)++It(a), *a is equivalent to the expression *a)
//       - a == b implies ++a == ++b
class forward_iterator
{
public:
  using iterator_category = std::forward_iterator_tag; // Legacy iterator
  using iterator_t = forward_iterator;
  using difference_type = long; //  MUST BE signed !
  using value_type = dummy_value_type;
  using reference = value_type&;
  using pointer = value_type*; // LegacyIterator
  using rvalue_reference = value_type&&;

  forward_iterator() = default; // LegacyForwardIterator
  forward_iterator(const forward_iterator& other) = default; // NEW: required
  forward_iterator(forward_iterator&& other) = default; // Required (movable)

  iterator_t& operator=(const iterator_t& rh) { return *this; }

  void swap(iterator_t& other) {} // LegacyIterator

  value_type& operator*() const { static value_type ret{}; return ret; }
  pointer operator->() const { static value_type ret{}; return &ret; } // LegacyInputIterator

  iterator_t& operator++() { return *this; }
  iterator_t  operator++(int) { return iterator_t{}; }

  bool operator==(const iterator_t& rh) const { return true; } // NEW
  bool operator!=(const iterator_t& rh) const { return true; } // NEW (not required in C++20, implicit)
};

void swap(forward_iterator& a, forward_iterator& b) { a.swap(b); } // LegacyIterator

//////////////////////////////////////////////////////////////////////////////////////////////////
class bidirectional_iterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag; // Legacy iterator
  using iterator_t = bidirectional_iterator;
  using difference_type = long; //  MUST BE signed !
  using value_type = dummy_value_type;
  using reference = value_type&;
  using pointer = value_type*; // LegacyIterator
  using rvalue_reference = value_type&&;

  bidirectional_iterator() = default; // LegacyForwardIterator
  bidirectional_iterator(const bidirectional_iterator& other) = default;
  bidirectional_iterator(bidirectional_iterator&& other) = default;

  iterator_t& operator=(const iterator_t& rh) { return *this; }

  void swap(iterator_t& other) {} // LegacyIterator

  value_type& operator*() const { static value_type ret{}; return ret; }
  pointer operator->() const { static value_type ret{}; return &ret; } // LegacyInputIterator

  iterator_t& operator++() { return *this; }
  iterator_t  operator++(int) { return iterator_t{}; }
  iterator_t& operator--() { return *this; }           // NEW
  iterator_t  operator--(int) { return iterator_t{}; } // NEW

  bool operator==(const iterator_t& rh) const { return true; }
  bool operator!=(const iterator_t& rh) const { return true; }
};

void swap(bidirectional_iterator& a, bidirectional_iterator& b) { a.swap(b); } // LegacyIterator

//////////////////////////////////////////////////////////////////////////////////////////////////
class random_access_iterator
{
public:
  using iterator_category = std::random_access_iterator_tag; // Legacy iterator
  using iterator_t = random_access_iterator;
  using difference_type = long; //  MUST BE signed !
  using value_type = dummy_value_type;
  using reference = value_type&;
  using pointer = value_type*; // LegacyIterator
  using rvalue_reference = value_type&&;

  random_access_iterator() = default; // LegacyForwardIterator
  random_access_iterator(const random_access_iterator& other) = default;
  random_access_iterator(random_access_iterator&& other) = default;

  iterator_t& operator=(const iterator_t& rh) { return *this; }

  value_type& operator*() const { static value_type ret{}; return ret; }
  pointer operator->() const { static value_type ret{}; return &ret; } // LegacyInputIterator

  void swap(iterator_t& other) {} // LegacyIterator

  iterator_t& operator++() { return *this; }
  iterator_t  operator++(int) { return iterator_t{}; }
  iterator_t& operator--() { return *this; }
  iterator_t  operator--(int) { return iterator_t{}; }

  bool operator==(const iterator_t& rh) const { return true; }
  bool operator!=(const iterator_t& rh) const { return true; }
  std::strong_ordering operator<=>(const iterator_t& rhs) const = default;

  difference_type operator-(const iterator_t& rh) const { return 0; }
  reference operator[](size_t index) const { static value_type ret{}; return ret; }

  // Movements
  iterator_t& operator+=(difference_type n) { return *this; }; // NEW
  iterator_t& operator-=(difference_type n) { return *this; }; // NEW
};

void swap(random_access_iterator& a, random_access_iterator& b) { a.swap(b); } // LegacyIterator

// NEW
random_access_iterator::iterator_t  operator+(const random_access_iterator::iterator_t& lh, random_access_iterator::difference_type rh) { return random_access_iterator::iterator_t{}; };
random_access_iterator::iterator_t  operator+(random_access_iterator::difference_type lh, const random_access_iterator::iterator_t& rh) { return rh + lh; };
random_access_iterator::iterator_t  operator-(const random_access_iterator::iterator_t& lh, random_access_iterator::difference_type rh) { return random_access_iterator::iterator_t{}; };

}

int main()
{
  boilerplate::input_or_output_iterator input_or_output_itr{};
  boilerplate::output_iterator output_itr{};
  boilerplate::input_iterator input_itr{};
  boilerplate::forward_iterator forward_itr{};
  boilerplate::bidirectional_iterator bidirectional_itr{};
  boilerplate::random_access_iterator random_access_itr{};

  static_assert( std::input_or_output_iterator<boilerplate::input_or_output_iterator>, "input_output_iterator concept failed" );

  static_assert( std::output_iterator<boilerplate::output_iterator, boilerplate::dummy_value_type>, "output_iterator concept failed" );

  static_assert( std::input_iterator<boilerplate::input_iterator>, "input_iterator concept failed" );

  static_assert( std::forward_iterator<boilerplate::forward_iterator>, "forward_iterator concept failed" );

  static_assert( std::bidirectional_iterator<boilerplate::bidirectional_iterator>, "bidirectional_iterator concept failed" );

  static_assert( std::random_access_iterator<boilerplate::random_access_iterator>, "bidirectional_iterator concept failed" );

  static_assert( std::contiguous_iterator<int*>, "contiguous_iterator concept failed" );

  return 0;
}
