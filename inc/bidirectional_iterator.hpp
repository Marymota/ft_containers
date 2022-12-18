#ifndef _BIDIRECTIONAL_ITERATOR_HPP_
#define _BIDIRECTIONAL_ITERATOR_HPP_

#include <iterator>
#include <cstddef>
#include "iterator_traits.hpp"

namespace ft {

	template<typename T>
	class bidirectional_iterator : public std::iterator<std::bidirectional_iterator_tag, T> {

		public:

			typedef T																value_type;
			typedef ptrdiff_t												difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef value_type*											pointer;
			typedef value_type&											reference;
			typedef const value_type*								const_pointer;
			typedef const value_type&								const_reference;

			bidirectional_iterator() : ptr(NULL) {}
			bidirectional_iterator(pointer ptr) : ptr(ptr) {}
			bidirectional_iterator(const bidirectional_iterator& ref) : ptr(ref.ptr) {}
			~bidirectional_iterator() {}

			// Overload to copy construct a const_iterator
			operator bidirectional_iterator<const value_type>() const {
				return bidirectional_iterator<const value_type>(ptr);
			}

			bidirectional_iterator& operator=(const bidirectional_iterator& copy) {
				if(this != &copy)
					ptr = copy.ptr;
				return (*this);
			}

		private:
			T* ptr;

		public:
			bool operator!=(const bidirectional_iterator& x) const 	{ return (ptr != 	x.ptr);}
			bool operator==(const bidirectional_iterator& x) const 	{ return (ptr == 	x.ptr);}

			bidirectional_iterator operator-(difference_type val) const { return bidirectional_iterator<T>(ptr - val);}
			difference_type operator-(bidirectional_iterator const& rhs) const { return ptr - rhs.ptr;}

			bidirectional_iterator operator+(difference_type val) const { return bidirectional_iterator<T>(ptr + val);}
			difference_type operator+(bidirectional_iterator const& rhs) const { return ptr + rhs.ptr;}

			bidirectional_iterator operator++() { ++ptr; return *this; }
			bidirectional_iterator operator++(int) { bidirectional_iterator it(*this); ++ptr; return it; }
			bidirectional_iterator operator--() { --ptr; return *this; }
			bidirectional_iterator operator--(int) { bidirectional_iterator it(*this); --ptr; return it; }
			reference operator*() const { return *ptr; }
			reference operator->() const { return *ptr; }
	};
}

#endif