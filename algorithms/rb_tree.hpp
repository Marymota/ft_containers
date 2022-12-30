#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <iostream>
#include <string>

namespace ft {

enum Color { _red = 1, _black = 0};

template <class T>
struct Rb_tree_Node {
	
	typedef T			value_type;
	value_type			_key;
	Rb_tree_Node*		_parent;
	Rb_tree_Node*		_left;
	Rb_tree_Node*		_right;
	Color						_color;

	Rb_tree_Node(	value_type key, Rb_tree_Node* parent,
						Rb_tree_Node* left, Rb_tree_Node* right, enum Color color ) :
		_key(key),
		_parent(parent),
		_left(left),
		_right(right),
		_color(color)
	{}
};

template <class T, class Alloc = std::allocator<Rb_tree_Node<T> > > 
class Rb_tree {

	typedef T									value_type;
	typedef Alloc								allocator_type;
	typedef Rb_tree_Node<value_type>		node_type;
	typedef Rb_tree_Node<value_type>*	Node;

	private:
		Node _root;
		Node _nil;
		allocator_type _alloc;

	public:	
		Rb_tree(allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_nil(NULL),
			_alloc(alloc)
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, _black));
			_root = _nil;
		}
		~Rb_tree() {delete _nil;}

		// Algorithm to insert a node
		void insert(value_type key) {

			// Create a new empty node
			Node node = _alloc.allocate(1);
			_alloc.construct(node, node_type(key, NULL, _nil, _nil, _red));

			node->_key = key;
			node->_parent = _nil;
			// Assign NUll to the left and right child of new_node
			node->_left = _nil;
			node->_right = _nil;
			// All first added nodes are red
			node->_color = _red;

			std::cout << "node: " << node->_key << std::endl;
			// Let y be the leaf and x be the root of the tree
			Node x = _root;
			Node y = _nil;
			// chech if the tree is empty
			// repeat until a leaf is reached
			while (x != _nil) {
				y = x;
				//	compare 	new_key with root_key
				if (node->_key < x->_key) {
					// if new_key is less than root_key go left
					x = x->_left;
				}
				else {
					// if new_key is more than root_key go right
					x = x->_right;
				}
			}
			// Assign the parent of the leaf as a parent of newNode
			node->_parent = y;
			// If leaf_key is greater than new_key, make new_node as a right child
			// Else, make new_node as left child
			if (y == _nil)
				_root = node;
			else if (y->_key > node->_key)
				y->_left = node;
			else
				y->_right = node;
			_root->_color = _black;
			// Call insert_fix() to mantain the property of red_black tree if violated
			if (node->_parent != NULL && node->_parent->_parent != NULL)
				insert_fix(node);
		}

		void insert_fix(Node node) {
			Node p  = node->_parent;
			Node gp = node->_parent->_parent;
			Node un;

			if (gp->_left != _nil && gp->_left != node->_parent)
				un = gp->_left;
			else if (gp->_right != node->_parent)
				un = gp->_right;
			else
				un = _nil;
			while (node->_parent->_color != _black)
			{
				if (node->_color == _red && p->_color == _red)
				{
					if (un != _nil && un->_color == _red)
						color_flip(node, un, gp);
					else if (node == node->_parent->_left)
						rotate_right(node);
					else
						rotate_left(node);
				}
				node = node->_parent;
			}
			recolor(node->_parent);				
		}

	/**	@recolor: If new_node check if color rules are applied correctly
	*/
		void recolor (Node node) {
			_root->_color = _black;
			if (node == _root) {
				if (node->_left != _nil)
					node->_left->_color = _red;
				if (node->_right != _nil)
					node->_right->_color = _red;
			else if (node->_color == _red)
			{
				if (node->_left != _nil)
					node->_left->_color = _black;
				if (node->_right != _nil)
					node->_right->_color = _black;
			}
		}	
		if (node->_color == _red) {
			node->_color = _black;
			node->_left->_color = _red;
			node->_right->_color = _red;
		}
	} // end recolor

/**	@color_flip: If new_node is red and has a red parent and a red aunt we color flip
*/
		void color_flip(Node node, Node un, Node gp) {
			std::cout << "color flip" << std::endl<< std::endl;
			if (un->_color == _red) {
				node->_parent->_color = _black;
				un->_color = _black;
				gp->_color = _red;
			}
		};
		//	end color_flip

/**	@rotate: If new_node is red and has a red parent and a black aunt we rotate
 * 	@rotate_left: If new_node is on the right of its parent
 * 	@rotate_right: If new_node is on the right of its parent
*/
		void rotate_right(Node node) {

			std::cout << "rotate right" << std::endl;
			
			node = node->_parent;
			Node tmp = _nil;
			if (node == node->_parent->_left)
				tmp = node->_parent;
			node->_right = tmp;
			tmp->_parent = node;
			if (tmp == _root)
				_root = node;
			node = node ->_right;
			node->_left = _nil;
			node->_right = _nil;
		};
		//	end rotate

		void rotate_left(Node node) {

			std::cout << "rotate left" << std::endl;
			node = node->_parent;
			Node tmp = node->_parent;
			node->_parent = tmp->_parent;
			node->_left = tmp;
			tmp->_parent = node;
			tmp->_left = _nil;
			tmp->_right = _nil;
			node->_parent->_right = node;
		};
		//	end rotate

		void printHelper(Node _root, std::string indent, bool last) {
			if (_root != _nil) {
				std::cout << indent;
				if (last) {
					std::cout<<"R----";
					indent += "    ";
				} else {
					std::cout << "L----";
					indent += "|    ";
				}
				Color sColor = _root->_color;
				if (sColor == _black)
					std::cout << _root->_key << "(B)" << std::endl;
				else
					std::cout << _root->_key << "(R)" << std::endl;
				printHelper(_root->_left, indent, false);
				printHelper(_root->_right, indent, true);
			}
		}

		void tree_print() {
			if (_root) {
				printHelper(_root, "", true);
			}
		}
};

}

#endif

//RESOURCES::
//	www.programiz.com/dsa/red-black-tree