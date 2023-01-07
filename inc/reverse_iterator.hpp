#ifndef _REVERSE_ITERATOR_HPP_
#define _REVERSE_ITERATOR_HPP_

#include "iterator_traits.hpp"

namespace ft
{
	template< class Iter >
	class reverse_iterator {

		public:

			typedef Iter																							iterator_type;
			typedef typename iterator_traits<Iter>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iter>::value_type				value_type;
			typedef typename iterator_traits<Iter>::difference_type		difference_type;
			typedef typename iterator_traits<Iter>::pointer						pointer;
			typedef typename iterator_traits<Iter>::reference					reference;

		private:
			iterator_type _iter;

		public:

		// MEMBER FUNCTIONS
			// Default constructor
			reverse_iterator() : _iter(iterator_type()) {}

			// Initialization constructor
			explicit reverse_iterator(const iterator_type& other) : _iter(other) {}
			
			// copy / type-cast constructor 
			template <class U>
			reverse_iterator(const reverse_iterator<U>& other) : _iter(other._it) {}

			virtual	~reverse_iterator() {}

		
			// base: Returns a copy of the base iterator 
			iterator_type base() const { return _iter; }

			// Assignment
			template< class U>
			reverse_iterator& operator=( const reverse_iterator<U>& other) { 
				if (this == &other)
					return *this; 
				_iter = other._iter; 
				return *this;
			}

			// Dereference iterator: Returns a reference to the element previous to current 
			reference operator*() const { 
				Iter tmp = _iter;	return *--tmp; }
			pointer operator->() const { 
				Iter tmp = _iter;	return *--tmp; }

			// Dereference iterator with offset: Returns a reference to the element at specified relative location
			reference operator[]( difference_type n ) const { return _iter[-n-1]; }

			// Advances or decrements the iterator
			reverse_iterator	operator++() { --_iter; return *this; }
			reverse_iterator	operator--() { ++_iter; return *this; }
			reverse_iterator	operator++(int) { reverse_iterator iter_copy(*this); --_iter; return iter_copy; }
			reverse_iterator	operator--(int) { reverse_iterator iter_copy(*this); ++_iter; return iter_copy; }
			reverse_iterator 	operator-(difference_type n) const { return reverse_iterator(_iter + n);}
			reverse_iterator 	operator+(difference_type n) const { return reverse_iterator(_iter - n);}
			reverse_iterator& operator-=(difference_type n) const { _iter += n; return *this; }
			reverse_iterator& operator+=(difference_type n) const { _iter -= n; return *this; }
	};

	// NON-MEMBER FUNCTIONS
	// Compares the underlying iterators
	template< class Iterator1, class Iterator2>
	bool operator==(	const ft::reverse_iterator<Iterator1>& lhs,
										const ft::reverse_iterator<Iterator2>& rhs )
	{	return lhs.base() == rhs.base(); }

	template< class Iterator>
	bool operator!=(	const ft::reverse_iterator<Iterator>& lhs,
										const ft::reverse_iterator<Iterator>& rhs )
	{	return lhs.base() != rhs.base(); }

	template< class Iterator1, class Iterator2>
	bool operator<(	const ft::reverse_iterator<Iterator1>& lhs,
										const ft::reverse_iterator<Iterator2>& rhs )
	{	return lhs.base() < rhs.base(); }

	template< class Iterator1, class Iterator2>
	bool operator<=(	const ft::reverse_iterator<Iterator1>& lhs,
										const ft::reverse_iterator<Iterator2>& rhs )
	{	return lhs.base() <= rhs.base(); }

	template< class Iterator1, class Iterator2>
	bool operator>(	const ft::reverse_iterator<Iterator1>& lhs,
										const ft::reverse_iterator<Iterator2>& rhs )
	{	return lhs.base() > rhs.base(); }

	template< class Iterator1, class Iterator2>
	bool operator>=(	const ft::reverse_iterator<Iterator1>& lhs,
										const ft::reverse_iterator<Iterator2>& rhs )
	{	return lhs.base() >= rhs.base(); }			
}

#endif