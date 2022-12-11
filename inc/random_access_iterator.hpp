#ifndef _RANDOM_ACCESS_ITERATOR_HPP_
#define _RANDOM_ACCESS_ITERATOR_HPP_

#include <cstddef>
#include <iterator>
#include "iterator_traits.hpp"

namespace ft {

	template<typename T>
	class random_access_iterator : public std::iterator<std::random_access_iterator_tag, T> {

		public:

			typedef T																value_type;
			typedef ptrdiff_t												difference_type;
			typedef std::random_access_iterator_tag	iterator_category;
			typedef value_type*											pointer;
			typedef value_type&											reference;
			typedef const value_type*								const_pointer;
			typedef const value_type&								const_reference;

			random_access_iterator() : ptr(NULL) {}
			random_access_iterator(pointer ptr) : ptr(ptr) {}
			random_access_iterator(const random_access_iterator& ref) : ptr(ref.ptr) {}
			~random_access_iterator() {}

			// Overload to copy construct a const_iterator
			operator random_access_iterator<const value_type>() const {
				return random_access_iterator<const value_type>(ptr);
			}

			random_access_iterator& operator=(const random_access_iterator& copy) {
				if(this != &copy)
					ptr = copy.ptr;
				return (*this);
			}

		private:
			T* ptr;

		public:
			bool operator!=(const random_access_iterator& x) const 	{ return (ptr != 	x.ptr);}
			bool operator==(const random_access_iterator& x) const 	{ return (ptr == 	x.ptr);}
			bool operator>(const random_access_iterator& x) const 	{ return (ptr > 	x.ptr);	}
			bool operator>=(const random_access_iterator& x) const 	{ return (ptr >= 	x.ptr);}
			bool operator<(const random_access_iterator& x) const 	{ return (ptr < 	x.ptr); }
			bool operator<=(const random_access_iterator& x) const 	{ return (ptr <= 	x.ptr);}

			random_access_iterator operator-(difference_type val) const { return random_access_iterator<T>(ptr - val);}
			difference_type operator-(random_access_iterator const& rhs) const { return ptr - rhs.ptr;}

			random_access_iterator operator+(difference_type val) const { return random_access_iterator<T>(ptr + val);}
			difference_type operator+(random_access_iterator const& rhs) const { return ptr + rhs.ptr;}

			random_access_iterator operator++() { ++ptr; return *this; }
			random_access_iterator operator++(int) { random_access_iterator it(*this); ++ptr; return it; }
			random_access_iterator operator--() { --ptr; return *this; }
			random_access_iterator operator--(int) { random_access_iterator it(*this); --ptr; return it; }
			reference operator*() const { return *ptr; }
			reference operator->() const { return *ptr; }
			reference operator[] (difference_type n) const { return ptr + n; }
	};
}

#endif