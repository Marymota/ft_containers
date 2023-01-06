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
template <class Key,	class T,	class Compare = std::less<Key>,
					class Alloc = std::allocator<ft::pair<const Key, T> > >	// map::allocator_type
class map {

	public:

	 /*----------------*/
	/**	MEMBER:TYPES: */
 /*----------------*/

		// Template parameters
		typedef Key				key_type;
		typedef T					mapped_type;
		typedef Compare		key_compare;
		typedef Alloc			allocator_type;

		typedef ft::pair<const Key, T>												value_type;
		typedef size_t																				size_type;
		typedef ptrdiff_t																			difference_type;
		typedef value_type&																		reference;
		typedef const value_type&															const_reference;
		typedef typename Alloc::pointer												pointer;
		typedef typename Alloc::const_pointer									const_pointer;
		typedef ft::bidirectional_iterator<value_type>				iterator;
		typedef ft::bidirectional_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator<value_type>							reverse_iterator;
		typedef ft::reverse_iterator<const value_type>				const_reverse_iterator;


		typedef typename	allocator_type::template rebind<value_type>::other Pair_alloc_type;
		typedef Rb_tree<key_type, value_type, std::_Select1st<value_type>, key_compare> tree_type;


/** @value_compare: std::map::value_compare is a function object that compares 
 * objects of type std::map::value_type (key-value pairs) by comparing of the
 * first components of the pairs.
 * 
 * Member types obtained via publicly inheriting from:
 * std::binary_function<value_type, value_type, bool>
 * 		value_type -> first and second argument type, bool -> result type
 * Protected member functions:
 * 		Compare comp -> the stored comparator
 * Member functions:
 * 		constructor -> new value_compare object
 * 		operator() -> compares two values of type value_type
 * */
		class value_compare : public std::binary_function<value_type, value_type, bool> {
			friend class map<Key, T, Compare, Alloc>;
			// Initializes the internal instance of the comparator to c
			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) { }
			public:
				// Compares the given values by calling the stored comparator 'comp'
				bool operator()( const value_type& lhs, const value_type& rhs ) const {
					return comp(lhs.first, rhs.first); }
		};

private:
		allocator_type	_alloc;
		tree_type				_tree;
		Compare					_comp;

	public:

		//default constructor
		explicit map (const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(), _comp(comp) {}

		// Range constructor
		template<	class InputIterator>
		map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

		// copy constructor					
		map (const map& x);

		virtual ~map() {}

		map& operator= (const map& x) { return *this;	}

		// Iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();

		// Capacity
		bool empty() const{ if (size()) { return true; } return false; }
		size_type size() const ;
		size_type max_size() const ;

		// Element access
		mapped_type& operator[] (const key_type& k);
		mapped_type& at (const key_type& k);
		const mapped_type& at (const key_type& k) const;

		// Modifiers
		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);
		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		void swap (map& x);
		void clear();

		// Observers
		key_compare key_comp() const;
		value_compare value_comp() const { return value_compare(_tree.key_comp());	}

		// Operations
		iterator find (const key_type& k);
		const_iterator find (const key_type& k) const;
		size_type count (const key_type& k) const;
		iterator lower_bound (const key_type& k);
		const_iterator lower_bound (const key_type& k) const;
		iterator upper_bound (const key_type& k);
		const_iterator upper_bound (const key_type& k) const;
		pair<iterator,iterator> equal_range (const key_type& k);
		pair<const_iterator, const_iterator> equal_range (const key_type& k) const;

		// Allocator
		allocator_type get_allocator() const { return _alloc.get_allocator(); }
};
}

#endif