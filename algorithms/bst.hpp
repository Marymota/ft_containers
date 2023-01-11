#ifndef _BST_HPP_
#define _BST_HPP_

#include <iostream>
#include "../algorithms/node.hpp"

namespace ft {

	template <	class T, class Alloc = std::allocator<T>,
							class Alloc_Node = std::allocator<ft::BSTNode<T> > >
	class BST : public BSTNode<T> {

		typedef T						value_type;
		typedef	Alloc				allocator_type;
		typedef	Alloc_Node	node_allocator_type;
		typedef BSTNode<T>	node_type;
		typedef BSTNode<T>*	Node;

		node_allocator_type	node_allocator;

//	private:
		Node 						_root;
		size_t					_size;

	public:

		BST() : _size(0) {
			_root = node_allocator.allocate(1);
			_root->_left = NULL;
			_root->_right = NULL;
			_root->_data = 0;
		}

		BST(T data) : _size(0) {
			_root = node_allocator.allocate(1);
			insert(_root, data);
		}

		~BST(){}
		
		Node search(Node root, value_type data) {
			if (root == NULL)
				return NULL;
			else if (data < root->_data)
				return search(root->_left, data);
			else if (data > root->_data)
				return search(root->_right, data);
			else
				return root;
		}	// end search()

		void insert(value_type data) {
			insert(_root, data);
		}

		void	insert(Node& root, value_type data) {
			if (root == NULL) {
				root = new node_type(data);
				return ;
		}
		else if (data < root->_data)
			insert(root->_left, data);
		else
			insert(root->_right, data);
		_size++;
	} // end insert()

	void tree_printHelper(Node root, std::string indent, bool last) {
		if (_root != NULL) {
			std::cout << indent;
			if (last) {
				std::cout<<"R----";
				indent += "    ";
			} else {
				std::cout << "L----";
				indent += "|    ";
			}
			std::cout << root->_data << std::endl;
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