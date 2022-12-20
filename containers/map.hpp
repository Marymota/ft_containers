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
// Class template
template <class Key,																									// map::key_type
					class T,																										// map::mapped
					class Compare = std::less<Key>, 														// map::key_compare
					class Alloc = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
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
		typedef Alloc																					allocator_type;
		typedef value_type&																		reference;
		typedef const value_type&															const_reference;
		typedef typename Alloc::pointer												pointer;
		typedef typename Alloc::const_pointer									const_pointer;
		typedef ft::bidirectional_iterator<value_type>				iterator;
		typedef ft::bidirectional_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<value_type>							reverse_iterator;
		typedef ft::reverse_iterator<const value_type>				const_reverse_iterator;

	private:
		Alloc _alloc;
		Compare _compare;

	public:
		// DEFAULT CONSTRUCTOR
		explicit map (const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_compare(comp)
		{}


	//	map (const map& other) {}

	//	map& operator= (const map& other) {}

	//	mapped_type& operator[] (const key_type& k) {
	//		return insert(ft::make_pair(key, T())).first->second;
	//	}

};
}

#endif