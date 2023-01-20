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
#include "../algorithms/bst.hpp"

namespace ft {

			/*-------*/
		 /** MAP: */
		/*-------*/

// Class template
template <typename Key,	typename T,	typename Compare = std::less<Key>,
					typename Alloc = std::allocator<ft::pair<const Key, T> > >
class map 
{
	public:

	 /*----------------*/
	/**	MEMBER:TYPES: */
 /*----------------*/


		// Template parameters
		typedef Key											key_type;
		typedef T												mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef	Compare									key_compare;
		typedef Alloc										allocator_type;

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

	private :
	// Tree structure
		typedef typename Alloc::template rebind<value_type>::other alloc_pair;
		typedef ft::BST<key_type, value_type,	key_compare, alloc_pair> tree_type;

		tree_type _tree;

	public:
		typedef typename tree_type::node_type		node_type;
		typedef typename tree_type::Node				Node;

		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference		const_value_type;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename tree_type::iterator								iterator;
		typedef typename tree_type::const_iterator					const_iterator;
		typedef typename tree_type::reverse_iterator				reverse_iterator;
		typedef typename tree_type::const_reverse_iterator	const_reverse_iterator;
		typedef typename tree_type::difference_type					difference_type;
		typedef size_t																			size_type;




	public:

		//default constructor
		explicit map (const key_compare& comp = key_compare(),
									const allocator_type& alloc = allocator_type()) :
									_tree(comp, alloc) { }

		// Range constructor
		template<	class InputIterator>
		map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
				_tree(comp, alloc) { insert(first, last); }

		// copy constructor					
		map (const map& x) : _tree(x) { }

		virtual ~map() {}

		map& operator= (const map& x){
			if (*this == x)
				return *this;
			return *this;
		}

		// Capacity
		bool empty() const{ if (size()) { return true; } return false; }
		size_type size() const ;
		size_type max_size() const ;

		// Element access: Return a reference to the mapped value of the element
		// with a key value equivalent to k
		mapped_type& operator[] (const key_type& key) {
			return (*((this->insert(ft::make_pair(key, mapped_type()))).first)).second;
		}

		mapped_type& at (const key_type& k);
		const mapped_type& at (const key_type& k) const;

		// Modifiers
		/** @insert: Attemps to insert a ft::pair into the map
		 * pair<iterator, bool>:
		 * bool represents the result of insertion
		 * and iterator represents the position of newly added element
		 */
		key_type get_key(value_type val) {
			return val.first;
		}

		mapped_type get_val(value_type val) {
			return val.second;
		}

		pair<iterator,bool> insert (const value_type& val) {
			return _tree.insert(val);
		}

		void erase (iterator position);
		size_type erase (const key_type& k);
		void erase (iterator first, iterator last);
		void swap (map& x);
		void clear();

		// Observers
		key_compare key_comp() const;
		value_compare value_comp() const { return value_compare(0);	}

		// Operations
		
		iterator find (const key_type& k)
		{ 	return find(_tree->_root, k); }

		const_iterator find (const key_type& k) const{
			return _tree.find(k);	}

		iterator find(Node root, key_type key) {
			if (root == NULL)
				return iterator(_tree->end());
			else if (key < get_key_from_pair<T>(root->_data))
				return find(root->_left, key);
			else if (key > get_key_from_pair<T>(root->_data))
				return find(root->_right, key);
			return iterator(_tree->_end);
		}	// end search()

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

	/*-----------------------------------*/
 /**	NON:MEMBER:FUNCTION:OVERLOADS:	*/
/*-----------------------------------*/
	/** @_relational_operators: */
	template <class Key, class T, class Compare, class Alloc> 
	bool operator == (const map<Key,T,Compare,Alloc>& lhs, 
										const map<Key,T,Compare,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return false;
		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class Key, class T, class Compare, class Alloc> 
	bool operator != (const map<Key,T,Compare,Alloc>& lhs,
										const map<Key,T,Compare,Alloc>& rhs) {
		return !(lhs	==	rhs); }
	
	template <class Key, class T, class Compare, class Alloc> 
	bool operator <	(const map<Key,T,Compare,Alloc>& lhs,
									 const map<Key,T,Compare,Alloc>& rhs) { 
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class Key, class T, class Compare, class Alloc> 
	bool operator <=	(const map<Key,T,Compare,Alloc>& lhs,
										 const map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs > rhs); }

	template <class Key, class T, class Compare, class Alloc> 
	bool operator >	(const map<Key,T,Compare,Alloc>& lhs,
									 const map<Key,T,Compare,Alloc>& rhs) {
	return rhs < lhs; }

	template <class Key, class T, class Compare, class Alloc> 
	bool operator >=	(const map<Key,T,Compare,Alloc>& lhs, 
										 const map<Key,T,Compare,Alloc>& rhs) {
	return !(lhs < rhs); }

}

#endif