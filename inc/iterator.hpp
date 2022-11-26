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
			typedef value_type*									pointer;
			typedef value_type&									reference;
			typedef const value_type*						const_pointer;
			typedef const value_type&						const_reference;

			iterator() : ptr(NULL) {}
			iterator(pointer pt) : ptr(pt) {}
			iterator(const iterator& copy) : ptr(copy.ptr) {}
			~iterator() {}

			// Overload to copy construct a const_iterator
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

			iterator operator-(difference_type val) const { return iterator<T>(ptr - val);}
			difference_type operator-(iterator const& rhs) const { return ptr - rhs.ptr;}


			iterator operator+(difference_type val) const { return iterator<T>(ptr + val);}
			difference_type operator+(iterator const& rhs) const { return ptr + rhs.ptr;}

			iterator operator++() { ++ptr; return *this; }
			iterator operator++(int) { iterator it(*this); ++ptr; return it; }
			iterator operator--() { --ptr; return *this; }
			iterator operator--(int) { iterator it(*this); --ptr; return it; }
			reference operator*() const { return *ptr; }
	};

	template<class T>
	ft::iterator<T>
	operator+(typename ft::iterator<T>::difference_type n,
											ft::iterator<T> const& rhs)
	{
		return rhs + n;
	}
}

#endif