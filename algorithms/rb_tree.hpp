#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <iostream>

namespace ft {

enum Color { _red = 1, _black = 0};

template <class T>
struct Rb_tree_Node {
	
	typedef T			value_type;
	value_type			_key;
	Rb_tree_Node*		_parent;
	Rb_tree_Node*		_left;
	Rb_tree_Node*		_right;
	Color					_color;

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
			Node new_node = _alloc.allocate(1);
			_alloc.construct(new_node, node_type(key, NULL, _nil, _nil, _red));

			new_node->_key = key;

			new_node->_parent = NULL;
			
//			// Assign NUll to the left and right child of new_node
			new_node->_left = _nil;
			new_node->_right = _nil;
//			// All first added nodes are red
			new_node->_color = _red;

			// 1. Let y be the leaf and x be the root of the tree
			Node x = _root;	
			Node y = 0;				
			
			//	2. chech if the tree is empty
			//	3. repeat until a leaf is reached
			while (x != _nil) {
				std::cout << "node: " << new_node->_key << std::endl;
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
			if (y == 0)
				_root = new_node;
			else if (y->_key > new_node->_key)
				y->_left = new_node;
			else
				y->_right = new_node;
			// 9. Call insert_fix() to mantain the property of red_black tree if violated
			//insert_fix(new_node);
		}

		void insert_fix(Node node) {
			if (node == _root) { node->_color == _black; return; }
			
			Node un; // uncle
			while (node->_parent != 0 && node->_parent == _red)
			{
				Node gp = node->_parent->_parent; // grandparent
				if (gp->_left == node->_parent) {
					if (gp->_right != NULL) {
						un = gp->_right;
						color_flip(node, un, gp);
						node = gp;
					}
					else if (gp->_right == NULL)
					{
						// if an uncle is Nil and all Nil's are black, we rotate
						if (node == node->_parent->_left)
							node = node->_parent;
						else if (node == node->_parent->_right)
							rotate_left(node);
						else
							rotate_right(node);
					}
				}
				else if (gp->_right == node->_parent)
				{
					if (gp->_left != NULL) {
						un = gp->_left;
						color_flip(node, un, gp);
						node = gp;
					}
					else if (gp->_left == NULL) {
						if (node->_parent->_left == node) {
							node = node->_parent;
							rotate_right(node);
						}
						node = node->_parent;
						rotate_left(node);
					}
				}
				// Root must always be black
				_root->_color= _black;
			}
		}

/**	@color_flip: If new_node is red and has a red parent and a red aunt we color flip
*/
		void color_flip(Node node, Node un, Node gp) {
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
			if (node->_left == NULL)
				return ;
			else
			{
				Node tmp = node;
				node->_parent = node->_left;
				node->_right = NULL;
				node->_left = NULL;
				node = node->_parent;
				node->_parent = node->_parent->_parent;
				node->_left = NULL;
				node->_right = tmp;
			}
		};
		//	end rotate

		void rotate_left(Node node) {
			if (node->_right == NULL)
				return ;
			else
			{
				Node tmp = node;
				node->_parent = node->_right;
				node->_left = NULL;
				node->_right = NULL;
				node = node->_parent;
				node->_parent = node->_parent->_parent;
				node->_left = tmp;
			}
		};
		//	end rotate

};

}

#endif

//RESOURCES::
//	www.programiz.com/dsa/red-black-tree