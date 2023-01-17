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
		 /** MAP: */
		/*-------*/

	template <class T>
	struct get_key_from_pair : std::unary_function<T, typename T::first_type>
	{
		typename T::first_type operator()(T pair) const { return pair.first; }
	};

// Class template
template <class Key,	class T,	class Compare = std::less<Key>,
					class Alloc = std::allocator<ft::pair<const Key, T> > >
class map {

	public:

	 /*----------------*/
	/**	MEMBER:TYPES: */
 /*----------------*/

		// Template parameters
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef Compare					key_compare;
		typedef Alloc					allocator_type;

		typedef typename Alloc::template rebind<value_type>::other alloc_pair;
		typedef BST<key_type, value_type, get_key_from_pair<value_type>, Compare, Alloc> BST_type;

	// Tree structure
		BST_type	_tree;

	public:
		typedef typename alloc_pair::reference				reference;
		typedef typename alloc_pair::const_reference		const_value_type;
		typedef typename alloc_pair::pointer				pointer;
		typedef typename alloc_pair::const_pointer			const_pointer;
		typedef typename BST_type::iterator					iterator;
		typedef typename BST_type::const_iterator			const_iterator;
		typedef typename BST_type::reverse_iterator			reverse_iterator;
		typedef typename BST_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename BST_type::difference_type			difference_type;
		typedef size_t										size_type;


public:

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
		class value_compare
			: public std::binary_function<value_type, value_type, bool> {
		friend class map<Key, T, Compare, Alloc>;
		// Initializes the internal instance of the comparator to c
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) { }
		public:
			// Compares the given values by calling the stored comparator 'comp'
			bool operator()( const value_type& lhs, const value_type& rhs ) const {
				return comp(lhs.first, rhs.first);
			}
		};

	public:
		//default constructor
		explicit map (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type()) :
									_tree(comp, alloc) {}

		// Range constructor
		template<	class InputIterator>
		map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

		// copy constructor					
		map (const map& x);

		virtual ~map() {}

		map& operator= (const map& x){

			_tree = x->_tree;

			return *this;
		}

		// Iterators
		iterator begin();
		const_iterator begin() const;
		iterator end() { return _tree.get_end() ; }
		const_iterator end() const;
		reverse_iterator rbegin();
		reverse_iterator rend();

		// Capacity
		bool empty() const{ if (size()) { return true; } return false; }
		size_type size() const ;
		size_type max_size() const ;

		// Element access
		mapped_type& operator[] (const key_type& k) {
			return ((this->insert(ft::make_pair(k, mapped_type()))).first);
		}

		mapped_type& at (const key_type& k);
		const mapped_type& at (const key_type& k) const;

		// Modifiers
		/** @insert: Attemps to insert a ft::pair into the map
		 * pair<iterator, bool>:
		 * bool represents the result of insertion
		 * and iterator represents the position of newly added element
		 */

		pair<iterator,bool> insert (const value_type& val) {
			iterator it = _tree.search(val.first);

			if (it != end()) return ft::make_pair(it, false);

			it = iterator(_tree.put(val.first, val.second));

			return ft::make_pair(it, true);			
		};


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
		value_compare value_comp() const { return value_compare(0);	}

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
		allocator_type get_allocator() const;
};
}

#endif