#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <cstddef>
#include <iterator>

namespace ft {
	template<typename T>
	class iterator {
		public:
			typedef T														value_type;
			typedef ptrdiff_t										difference_type;
			typedef ft::random_access_iterator	iterator_category;
			typedef T*													pointer;
			typedef T&													reference;

			iterator() : ptr(NULL) {}
			iterator(T* pt) : ptr(pt) {}
			iterator(const iterator& copy) : ptr(copy.ptr) {}
			virtual ~iterator() {}

			operator iterator<const value_type>() const {
				return iterator<const value_type>(ptr);
			}

			iterator& operator=(const iterator& copy) {
				if(this != &copy)
					ptr = copy.ptr;
				return (*this);
			}
		private:
			T* ptr;

		public:
			bool operator!=(const iterator& x) const 	{ return (ptr != 	x.ptr);}
			bool operator==(const iterator& x) const 	{ return (ptr == 	x.ptr);}
			bool operator>(const iterator& x) const 	{ return (ptr > 	x.ptr);	}
			bool operator>=(const iterator& x) const 	{ return (ptr >= 	x.ptr);}
			bool operator<(const iterator& x) const 	{ return (ptr < 	x.ptr); }
			bool operator<=(const iterator& x) const 	{ return (ptr <= 	x.ptr);}

			iterator operator-(const iterator& x) const { return(ptr - x.ptr);}
			iterator operator+(const iterator& x) const { return(ptr + x.ptr);}


			iterator operator++() { ++ptr; return *this; }
			iterator operator++(int) { iterator it(*this); ++ptr; return it; }
			iterator operator--() { --ptr; return *this; }
			iterator operator--(int) { iterator it(*this); --ptr; return it; }
			reference operator*() const { return *ptr; }
	};
}

#endif