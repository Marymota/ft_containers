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
#include "../algorithms/rb_tree.hpp"
#include "../inc/pair.hpp"

namespace ft {

			 /*-------*/
			/**	MAP: */
		 /*-------*/
// Class template
template <class Key,	class T,	class Compare = std::less<Key>,	class Alloc = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
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

		typedef Rb_tree<value_type,	key_compare, allocator_type> tree_type;
		
		Alloc			_alloc;
		Compare		_compare;
		tree_type _tree;


	//	typedef Rb_tree<value_type, key_compare, allocator_type> _tree;
	//	typedef typename _tree::iterator iterator;
	//	typedef typename _tree::iterator const_iterator;
	//	typedef typename _tree::iterator reverse_iterator;
	//	typedef typename _tree::iterator const_reverse_iterator;

	public:

		map() : _tree() {}
		// DEFAULT CONSTRUCTOR
		explicit map (const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) : _tree()
		{}

		virtual
		~map() {}

//	/** ITERATORS:	***/
//		iterator begin(){												return } 	
//		const_iterator begin() const{						return _root ;}						
//		iterator end(){													return _finish ;}									
//		const_iterator end() const{							return _finish ;}						
//		reverse_iterator rbegin(){							return reverse_iterator(end()) ;}	 				// end() of _finish? is it different?			
//		const_reverse_iterator rbegin() const{ 	return const_reverse_iterator(end()) ;}	
//		reverse_iterator rend(){								return reverse_iterator(begin());}			
//		const_reverse_iterator rend() const{		return const_reverse_iterator(begin()) ;}


	bool pair_compare(const value_type& x, const value_type& y) const {
		return x->first, y->first;
	}

};
}

#endif