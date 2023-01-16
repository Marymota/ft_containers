#ifndef _BST_HPP_
#define _BST_HPP_

#include <iostream>
#include <algorithm>
#include "../algorithms/node.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"
#include "../inc/pair.hpp"


namespace ft {

	template <	class Key,	class T, class NodeData, class Compare = std::less<Key>,
							class Alloc = std::allocator<ft::pair<const Key, T> > >
	class BST : public BSTNode<T> {

		/** @rebind:	Defines an allocator for a new type different
		 * 						from the one defined in the container.
		 * 						Alloc = std::allocator<T> allocates type T elements
		 * 						Alloc_Node = allocates BSTNodes
		 */

	public:
		typedef Key																			key_type;
		typedef T																				mapped_type;
		typedef ft::pair<const Key, T>									value_type;
		typedef Compare																	key_compare;
		typedef BSTNode<value_type>											node_type;
		typedef BSTNode<value_type>*										Node;
		typedef ft::BST_iterator<node_type>							iterator;
		typedef ft::BST_iterator<const node_type> 			const_iterator;
		typedef ft::reverse_iterator<node_type>					reverse_iterator;
		typedef ft::reverse_iterator<const node_type> 	const_reverse_iterator;
		typedef ptrdiff_t																difference_type;
		typedef size_t																	size_type;
		typedef	Alloc																		allocator_type;

		typedef typename Alloc::template rebind<BSTNode<T> >::other	Alloc_Node;

	private:
		Node				_root;
		Compare 		_comp;
		Alloc_Node	_alloc;
		size_type		_size;

	public:

		BST(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type()) :
				_root(NULL), _comp(comp), _alloc(alloc), _size(0)  {}

		BST(key_type key, mapped_type data, const allocator_type& alloc = allocator_type()) :  _root(NULL), _alloc(alloc), _size(1) {
			_root = _alloc.allocate(1);
			_root->_key = key;
			_root->_data = data;
			_root->_left = NULL;
			_root->_right = NULL;
		}

		/** @bug: Need to use std::allocator to destroy elements
		 */
		~BST() {
			deleteTree();
		}
		
		key_type get_key( value_type& val) {
			return val.first;
		}

		mapped_type get_val( value_type& val) {
			return val.second;
		}

		void deleteTree() {
			deleteTree(_root);
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

		mapped_type get(Key key) {
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

		void put(key_type key, mapped_type data) {
			++_size;
			put(_root, key, data);
		}

		Node	put(Node& root, key_type key, mapped_type data) {
			if (root == NULL) {
				root = new node_type();
				_size++;
				return root;
			}
			if (key == get_key(root->_data))
				root->_data = make_pair(key, data);
			else if (key < get_key(root->_data))
				put(root->_left, key, data);
			else
				put(root->_right, key, data);
			root->_count = 1 + count(root->_left) + count(root->_right);	
			return root;
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

	Node floor(Key key) {
		Node x = floor(_root, key);
		if (x == NULL) return 0;
		return x;
	}

	Node ceiling(Key key) {
		Node x = ceiling(_root, key);
		if (x == NULL) return 0;
		return x;
	}

	size_type count() { return count(_root);	}

	void tree_print() {
		if (_root)
			tree_print(_root, "", true);
	} // end tree_print

	/** @delete_min: 
	 * Call deleteMin() with the next smaller node as argument (node->left);
	 * If the next smaller node is a leaf (NULL) return the node at the right
	 * While recursivelly calling deleteMin() we point the 
	 * current node left link to its return 
	 * (node->left if a leaf is not found, continuing the recursive cycle,
	 * or node->right if a leaf is found, that will be automatically
	 * adopted by the previously node called in deleteMin();
	 */

	void deleteNode(key_type key) { _root = deleteNode(_root, key); --_size; }	
	void deleteMin() { deleteMin(_root); }
	void deleteMax() { deleteMax(_root); }

private:

	Node floor(Node x, key_type key) {
		if (x == NULL) return NULL;
		if (key == x->_key) return x;
		if (key < x->_key) return floor(x->_left, key);
		Node y = floor(x->_right, key);
		if (y != NULL)	return y;
		else	return x;
	} // end(floor)

	Node ceiling(Node x, key_type key) {
		if (x == NULL) return NULL;
		if (key == x->_key) return x;
		if (key > x->_key) return ceiling(x->_right, key);
		Node y = ceiling(x->_left, key);
		if (y != NULL)	return y;
		else	return x;
	} // end(ceiling)

	size_type count(Node x) {
		if (x == NULL)
			return 0;
		return x->_count;
	}

	Node deleteMin(Node x) {
		if (x->_left == NULL) { return x->_right; }
		x->_left = deleteMin(x->_left);
		x->_count = 1 + count(x->_left) + count(x->_right);
		return x;
	}

	Node deleteMax(Node x) {
		if (x->_right == NULL) { return x->_left; }
		x->_right = deleteMax(x->_right);
		x->_count = 1 + count(x->_left) + count(x->_right);
		return x;
	}

	Node deleteNode(Node x, key_type key) {
		/** @bug:	Need to protect from unexistent given key 
		 * 				Does not delete root
		*/
		// Search for the node to e deleted
		//if (node_isroot(x, key)) return _root;
		if (key == 0 || x == NULL) { return NULL; }
		if (key < x->_key) { x->_left = deleteNode(x->_left, key); }
		else if (key > x->_key) { x->_right = deleteNode(x->_right, key); }
		else {
			if (x->_right == NULL)	return x->_left; 	// no right child
			if (x->_left == NULL)	return x->_right;	// no left child
			
			Node t = x;
			x = this->maximum(t->_left);
			x->_left = deleteMax(t->_left);
			x->_right  = t->_right;
			x->_count = count(x->_left) + count(x->_right) + 1;
		}
		return x;
	}

	void deleteTree(Node root) {
		if (root == NULL)
			return ;
		deleteTree(root->_left);
		deleteTree(root->_right);
		delete root;
		root = NULL;
	}

	void clear_Node (Node x) {
		_alloc.destroy(x);
		_alloc.deallocate(x, sizeof(Node));
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
			std::cout << root->_key << "( " << root->_data << " )" << std::endl;
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