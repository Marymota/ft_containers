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
			_root = NULL;
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
		} // end get()

		void put(key_type key, value_type data) {
			put(_root, key, data);
		}

		void	put(Node& root, key_type key, value_type data) {
			if (root == NULL) {
				root = new node_type(key, data, 1);
				_size++;
				return ;
			}
			if (key == root->_key)
				root->_data = data;
			else if (key < root->_key)
				put(root->_left, key, data);
			else
				put(root->_right, key, data);
			root->_count = 1 + count(root->_left) + count(root->_right);	
			return ;
	} // end insert()


	/**	@floor: Largest element <= than the given key
	 *	Repeat until null:
	 *		Iterate left until a node->key is larger than the given key;
	 *		Create a new Node that copies the node on the right;
	 *		Node x keeps track of all the left turns
	 *		Node y keeps track of all the right turns
	 *		When y gets to a leaf we retrun x
	 *		(the last element less than the given key that was found)
	 *		else we return y (the given key is equal to the node y)
	 *	@ceiling: Largest element >= than the given key
	 *	Same as floor() but:
	 *		Node x keeps track of all right turns
	 *		Node y keeps track of all the left turns
	 */	

	key_type floor(Key key) {
		Node x = floor(_root, key);
		if (x == NULL) return 0;
		return x->_key;
	}

	key_type ceiling(Key key) {
		Node x = ceiling(_root, key);
		if (x == NULL) return 0;
		return x->_key;
	}

	size_type count() { return count(_root);	}

	void tree_print() {
		if (_root)
			tree_print(_root, "", true);
	} // end tree_print



private:

	Node floor(Node x, Key key) {
		if (x == NULL) return NULL;
		if (key == x->_key) return x;
		if (key < x->_key) return _floor(x->_left, key);
		Node y = floor(x->_right, key);
		if (y != NULL)	return y;
		else	return x;
	} // end(floor)

	Node ceiling(Node x, Key key) {
		if (x == NULL) return NULL;
		if (key == x->_key) return x;
		if (key > x->_key) return _ceiling(x->_right, key);
		Node y = _ceiling(x->_left, key);
		if (y != NULL)	return y;
		else	return x;
	} // end(ceiling)

	size_type count(Node x) {
		if (x == NULL)
			return 0;
		return x->_count;
	}

	void tree_print(Node root, std::string indent, bool last) {
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
			tree_print(root->_left, indent, false);
			tree_print(root->_right, indent, true);
		}
	} // end tree_printHelper

}; // end namespace
}

#endif

//	RESOURCES:
//	(book)Algorithms - Robert Sedgewick | Kevin Wayne
//	(Coursera course) Algorithms
//	https://math.hws.edu/eck/cs225/s03/binary_trees/