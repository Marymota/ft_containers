#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <iostream>

namespace ft {

enum Color { _red = false, _black = true};

template <class T>
struct Rb_tree_Node {
	T								_key;
	Color						_color;
	Rb_tree_Node*		_parent;
	Rb_tree_Node*		_left;
	Rb_tree_Node*		_right;

	Rb_tree_Node() : _key(0), _color(_black), _parent(0), _left(0), _right(0) {}
	Rb_tree_Node(Rb_tree_Node*	pt, Rb_tree_Node*	 parent) :
		_key(0),
		_color(_red),
		_parent(parent),
		_left(0),
		_right(0)
	{}
};
	
template <class T>
class Rb_tree {

	typedef T													value_type;
	typedef Rb_tree_Node<value_type>	node_type;
	typedef Rb_tree_Node<value_type>*	Node;

	private:
		Node _nil;
		Node _root;

	public:	
		Rb_tree() : _nil(new Node), _root(_nil) {}
		~Rb_tree() {delete _nil;}

		void insert(int key) {
			Node new_node = new Node;	// Create a new empty node
			new_node->_parent = 0;
			new_node->_left = _nil;
			new_node->_right = _nil;
			new_node->_color = _red;

			// 1. Let y be the leaf and x be the root of the tree
			Node x = _root;	
			Node y = 0;				
			
			//	2. chech if the tree is empty
			//	3. repeat until a leaf is reached
			while (x != _nil) {
				y = x;										
				//	3.a. compare 	new_key with root_key
				if (new_node->_key < x->_key) {
					// 3.b. if new_key is less than root_key go left
					x = x->_left;
				}
				else {
					// 3.c. if new_key is more than root_key go right
					x = x->_right;
				}
			}
			// 4. Assign the parent of the leaf as a parent of newNode
			new_node->_parent = y;
			// 5. If leaf_key is greater than new_key, make new_node as a right child
			// 6. Else, make new_node as left child
			if (y->_key > new_node->_key)
				y->_left = new_node;
			else
				y->_right = new_node;
			// 7. Assign NUll to the left and right child of new_node
			new_node->_right = 0;
			new_node->_left = 0;
			// 8. Assig RED color to new_node
			new_node->_color = _red;
			// 9. Call insert_fix() to mantain the property of red_black tree if violated
			//insert_fix();
		}
};

}

#endif

//RESOURCES::
//	www.programiz.com/dsa/red-black-tree