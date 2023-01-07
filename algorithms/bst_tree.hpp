#ifndef _BST_HPP_
#define _BST_HPP_

#include "../inc/pair.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"

namespace ft {
	template <class Key, class Value>
	class Node {

	typedef ft::pair<const Key, Value>	value_type;

	private:
		value_type	_data;
		Node		_left;
		Node		_right;
};

	template <	class Key, class T, class Compare = std::less<Key>,
				class Allocator = std::allocator<ft::pair<const Key, T> > >
	class BST {
		typedef Key												key_type;
		typedef T												mapped_type;
		typedef ft::pair<const Key, T>							value_type;
		typedef std::size_t										size_type;
		typedef std::ptrdiff_t									difference_type;
		typedef Compare											key_compare;
		typedef Allocator										allocator_type;
		typedef value_type& 									reference;
		typedef const value_type&								const_reference;
		typedef typename Allocator::pointer						pointer;
		typedef typename Allocator::const_pointer				const_pointer;
		typedef ft::bidirectional_iterator<value_type>			iterator;
		typedef ft::bidirectional_iterator<const value_type>	const_iterator;  
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	value_type										Node;

	private:
		Node _root;

	public:
		explicit bst_tree (	const key_compare& comp = key_compare(),
							const allocator_type& alloc = allocator_type()) :
							_root(NULL)
							{}
		
		void put(Key key, Value val);
		mapped_type get(Key key);
		void delese(Key key);
		iterator<Key> iterator();



		void tree_printHelper(Node _root, std::string indent, bool last) {
			if (_root != NULL) {
				std::cout << indent;
				if (last) {
					std::cout<<"R----";
					indent += "    ";
				} else {
					std::cout << "L----";
					indent += "|    ";
				}
				std::cout << _root->_key << std::endl;
				tree_printHelper(_root->_left, indent, false);
				tree_printHelper(_root->_right, indent, true);
			}
		}

		void tree_print() {
			if (_root) {
				tree_printHelper(_root, "", true);
			}
		}
	};
}

#endif