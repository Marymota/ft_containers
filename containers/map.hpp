#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <functional>
#include <iterator>
#include <iostream>
#include <memory>		// add allocator<T>
#include <cstddef> 	// add ptrdiff_t
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"
#include "../inc/random_access_iterator.hpp"
#include "../inc/iterator_traits.hpp"
#include "../inc/enable_if.hpp"
#include "../inc/is_integral.hpp"
#include "../inc/distance.hpp"
#include "../inc/uninitialized_copy.hpp"
#include "../inc/lex_compare.hpp"
#include "../inc/pair.hpp"

namespace ft {

									 /*-------*/
									/**	MAP: */
								 /*-------*/

template <class Key,																									// map::key_type
					class T,																										// map::mapped
					class Compare = std::less<Key>, 														// map::key_compare
					class Allocator = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
class map {

	public:

	 /*----------------*/
	/**	MEMBER:TYPES: */
 /*----------------*/

		typedef Key																						key_type;
		typedef T																							mapped_type;
		typedef ft::pair<const Key, T>												value_type;
		typedef size_t																				size_type;
		typedef ptrdiff_t																			difference_type;
		typedef Compare																				key_compare;
		typedef Allocator																			allocator_type;
		typedef value_type&																		reference;
		typedef const value_type&															const_reference;
		typedef typename Allocator::pointer										pointer;
		typedef typename Allocator::const_pointer							const_pointer;
		typedef ft::bidirectional_iterator<value_type>				iterator;
		typedef ft::bidirectional_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<value_type>							reverse_iterator;
		typedef ft::reverse_iterator<const value_type>				const_reverse_iterator;

	protected:
		allocator_type	_allocator;				//	Allocator object
		pointer					_data;						//	First element
		pointer 				_finish;					//	Last element in the vector 
		pointer					_capacity;				//	Las allocated piece of memory
		key_compare			_compare;

	public:
		// DEFAULT CONSTRUCTOR
		explicit map (const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :
			_allocator(alloc),
			_data(),
			_finish(),
			_capacity(),
			_compare(comp)
		{}

		template <class InputIterator>
		map (InputIterator first, InputIterator last,
		const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :
			_allocator(alloc),
			_data(0),
			_finish(0),
			_capacity(0),
			_compare(comp)
		{
			const size_type n = std::distance(first, last);
			_data = _allocator.allocate(n);
			_finish = _data;
			_capacity = _data + n;
			for(; first != last; ++first, _finish++)
					_allocator.construct(_finish, *first);			
		}

		map (const map& other) {
			_data = _allocator.allocate(other.capacity());
			_finish = ft::uninitialized_copy(other.begin(), other.end(), _data);
			_capacity = _finish;
		}

		map& operator= (const map& other) {
			_data = _allocator.allocate(other.capacity());
			_finish = ft::uninitialized_copy(other.begin(), other.end(), _data);
			_capacity = _finish;
		}

		iterator begin() { return _data;	}
		const_iterator begin() const {return _data; }
		iterator end() { return _finish;	}
		const_iterator end() const {return _finish; }

	//	mapped_type& operator[] (const key_type& k) {
	//		return insert(ft::make_pair(key, T())).first->second;
	//	}

		size_type capacity() const{
			return _capacity - _data;
		}
};
}

#endif