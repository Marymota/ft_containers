#ifndef _BST_HPP_
#define _BST_HPP_

#include <iostream>
#include "../algorithms/node.hpp"

namespace ft {

	template <	class Key,	class T,
							class Alloc = std::allocator<T> >
	class BST : private BSTNode<Key, T> {

		/** @rebind:	Defines an allocator for a new type different
		 * 						from the one defined in the container.
		 * 						Alloc = std::allocator<T> allocates type T elements
		 * 						Alloc_Node = allocates BSTNodes
		 */

		typedef Key								key_type;
		typedef T									value_type;
		typedef BSTNode<Key, T>		node_type;
		typedef BSTNode<Key, T>*	Node;
		typedef size_t						size_type;

		typedef	Alloc							allocator_type;
		typedef typename Alloc::template rebind<BSTNode<Key, T> >::other	Alloc_Node;

//	private:
		Node				_root;
		Alloc				_alloc;
		Alloc_Node	_alloc_node;
		size_type		_size;

	public:

		BST() : _size(0) {
			_root = _alloc_node.allocate(1);
		}

		BST(key_type key, value_type data) : _size(0) {
			_root = _alloc_node.allocate(1);
			_alloc.construct(&_root->_data, key, data);
		}
		
		bool search(Node root, key_type key) {
			if (root == NULL)
				return false;
			else if (key < root->_key)
				return search(root->_left, key);
			else if (key > root->_key)
				return search(root->_right, key);
			return true;
		}	// end search()

		value_type get(Key key) {
			Node x = _root;
			while(x != NULL) {
				if (key < x->_key)
					x = x->_left;
				else if (key > x->_key)
					x = x->_right;
				else
					return x->_data;
			}
			return 0;
		}

		void put(key_type key, value_type data) {
			put(_root, key, data);
		}

		void	put(Node& root, key_type key, value_type data) {
			if (root == NULL) {
				root = new node_type(key, data);
				_size++;
				return ;
			}
			if (key == root->_key)
				root->_data = data;
			else if (key < root->_key)
				put(root->_left, key, data);
			else
				put(root->_right, key, data);				
			return ;
	} // end insert()

	void tree_printHelper(Node root, std::string indent, bool last) {
		if (root != NULL) {
			std::cout << indent;
			if (last) {
				std::cout<<"R----";
				indent += "    ";
			} else {
				std::cout << "L----";
				indent += "|    ";
			}
			std::cout << root->_key << "(" << root->_data << ")" << std::endl;
			tree_printHelper(root->_left, indent, false);
			tree_printHelper(root->_right, indent, true);
		}
	} // end tree_printHelper

	void tree_print() {
		if (_root)
			tree_printHelper(_root, "", true);
	} // end tree_print

}; // end namespace
}

#endif

//	RESOURCES:
//	https://math.hws.edu/eck/cs225/s03/binary_trees/