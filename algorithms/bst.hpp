#ifndef _BST_HPP_
#define _BST_HPP_

#include <iostream>
#include <algorithm>
#include "../algorithms/node.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"
#include "../inc/pair.hpp"


namespace ft {

	template <class T>
	struct get_key_from_pair : std::unary_function<T, typename T::first_type>
	{		typename T::first_type operator()(T pair) const { return pair.first; } };

	template <	class Key, class Tp, class Compare = std::less<Key>,
							class Alloc = std::allocator<BSTNode<Tp> > > 
	class BST  {

		/** @rebind:	Defines an allocator for a new type different
		 * 						from the one defined in the container.
		 * 						Alloc = std::allocator<T> allocates type T elements
		 * 						Alloc_Node = allocates BSTNodes
		 */

	public:
		typedef Key															key_type;
		typedef Tp															value_type;
		typedef Compare													key_compare;
		typedef ft::BST_iterator<Tp>						iterator;
		typedef ft::BST_iterator<const Tp> 			const_iterator;
		typedef ft::reverse_iterator<Tp>				reverse_iterator;
		typedef ft::reverse_iterator<const Tp> 	const_reverse_iterator;
		typedef ptrdiff_t												difference_type;
		typedef size_t													size_type;
		typedef	Alloc														allocator_type;
		typedef BSTNode<value_type>							node_type;
		typedef BSTNode<value_type>*						Node;

		Node						_end;
		Node						_root;
		Compare 				_comp;
		allocator_type	_alloc;
		size_type				_size;

	public:

		explicit BST(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) :
		_end(NULL), _root(NULL), _comp(comp), _alloc(alloc), _size(0) {
			_end = _alloc.allocate(1);
			_alloc.construct(_end, node_type(value_type()));
			_root = _end;
		}

		/** @bug: Need to use std::allocator to destroy elements
		 */
		~BST() {
			deleteTree();
		}

		void deleteTree() {
			deleteTree(_root);
		}

		iterator search(key_type key) {
			return search(_root, key);
		}

		iterator search(Node root, key_type key) {
			if (root == NULL)
				return iterator(_end);
			else if (key < get_key_from_pair<Tp>(root->_data))
				return search(root->_left, key);
			else if (key > get_key_from_pair<Tp>(root->_data))
				return search(root->_right, key);
			return iterator(&_end);
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

			key_type get_key(value_type data) {
			Node x = _root;
			while(x != NULL) {
				if (data < x->_data)
					x = x->_left;
				else if (data > x->_data)
					x = x->_right;
				else
					return *this->get_key(x->_data);
			}
			return 0;
		} // end get()

		pair<iterator,bool> insert (value_type& data) {
			iterator it = search(get_key_from_pair<Tp>(data));
			if (it != _end)
				return ft::make_pair(it, false);
			Node node = _alloc.allocate(1);
			_alloc.construct(node, node_type(data));
			if (node->_parent == NULL)
			{
				_root = node;
				return _root;
			}
			it = put(node, data);
			_size++;
			return ft::make_pair(it, true);
		}

		pair<iterator,bool>	put(Node node, value_type data) {
			while (node != NULL) {
				if (_comp(get_key_from_pair<Tp>(node->_left), get_key_from_pair<Tp>(data)))
					return put(node->_left, data);
				else
					return put(node->_right, data);
			}
			return iterator(_end);
		}



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

	iterator get_end() { return  iterator(&_end); }

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