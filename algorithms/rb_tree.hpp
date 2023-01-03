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

	typedef T														value_type;
	typedef Alloc												allocator_type;
	typedef Rb_tree_Node<value_type>		node_type;
	typedef Rb_tree_Node<value_type>*		Node;

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
		
		~Rb_tree() {
			tree_clear(_root);
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}


		Node tree_search(value_type key) {
			Node x = _root;
			while (x != _nil && key != x->_key)
				if (key < x->_key){ x = x->_left; }
				else{ x = x->_right; }
			return x;
		}

		Node tree_minimum(){ Node x = _root; while (x->_left != _nil){ x = x->_left; } return x; }
		Node tree_maximum(){ Node x = _root; while (x->_right != _nil){ x = x->_right; } return x; }
		Node tree_minimum(Node x){ while (x->_left != _nil){ x = x->_left; } return x; }
		Node tree_maximum(Node x){ while (x->_right != _nil){ x = x->_right; } return x; }

		// The smallest node greater than key
		Node tree_sucessor(value_type key){
			Node x = tree_search(key);
			if (x == _nil){ return _nil; }
			if (x->_right != _nil)
				return tree_minimum(x->_right);
			Node y = x->_parent;
			while (y != _nil && x == y->_right) { x = y; y = y->_parent; }
			return y;
		}
		
		// The greatest node smaller than key
		Node tree_predecessor(value_type key){
			Node x = tree_search(key);
			if (x == _nil){ return _nil; }
			if (x->_left != _nil)
				return tree_maximum(x->_left);
			Node y = x->_parent;
			while (y != _nil && x == y->_left) { x = y; y = y->_parent; }
			return y;
		}

		Node create_node(value_type key) {
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
			return node;
		}

		void tree_insert(value_type key) {
			Node node = create_node(key);
			Node x = _root;
			Node y = _nil;
			while (x != _nil) {
				y = x;
				if (node->_key < x->_key)
					x = x->_left;
				else
					x = x->_right;
			}
			node->_parent = y;
			if (y == _nil)
				_root = node;
			else if (y->_key > node->_key)
				y->_left = node;
			else
				y->_right = node;
			_root->_color = _black;
		// Call insert_fix() to mantain the property of red_black tree if violated
		//	if (node->_parent != NULL && node->_parent->_parent != NULL)
		//		tree_insert_fix(node);
		}

		Node tree_delete_node(value_type key) {
			Node node = tree_search(key);
			Node y;
			Node x; // the node child

			if(node->_left == _nil || node->_right == _nil){ y = node; }
			else{ y = tree_sucessor(key); }

			if(y->_left != _nil) { x = y->_left; }
			else { x = y->_right; }

			if(x != _nil) { x->_parent = y->_parent; }

			if(y->_parent == _nil) { _root = x; }
			else if (y == y->_parent->_left) { y->_parent->_left = x; }
			else { y->_parent->_right = x; }

			if (y != node) { node->_key = y->_key; }
			return y;
		}

		void tree_insert_fix(Node& node) {
		
			std::cout << "insert_fix" << std::endl;
		
			Node p  = node->_parent;
			Node gp = node->_parent->_parent;
			Node un;
			if (gp->_left != _nil && gp->_left != node->_parent)
				un = gp->_left;
			else if (gp->_right != node->_parent)
				un = gp->_right;
			else
				un = _nil;

			std::cout << "node: " << node->_key << std::endl;
			std::cout << "gp: " << gp->_key << std::endl;
			std::cout << "p: " << p->_key << std::endl;

			if (node->_color == _red && p->_color == _red)
			{

				if (un != _nil && un->_color == _red)
					tree_color_flip(node, un, gp);
				else if (node == node->_parent->_left)
					tree_rotate_right(node);
				else
					tree_rotate_left(node);
				//recolor(node->_parent);
				if (node->_color == _red && (node->_left->_color == _red || node->_right->_color == _red))
					tree_insert_fix(node);
			}
		}

	/**	@recolor: If new_node check if color rules are applied correctly
	*/
		void tree_recolor (Node node) {
			std::cout << "node: " << node->_key << std::endl;
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
		void tree_color_flip(Node node, Node un, Node gp) {
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
		void tree_rotate_right(Node& node) {

			std::cout << "rotate right" << std::endl;
			
			Node p = node->_parent;
			Node gp = p->_parent;

			node->_parent->_parent = gp;
			gp->_right = node;
			p->_parent = node;
			p->_left = node->_right;
			node->_right = p;
			node = node->_right;
		};
		//	end rotate

		void tree_rotate_left(Node& node) {

			std::cout << "rotate left" << std::endl;
			Node gp = node->_parent->_parent;
			Node p = node->_parent;
			
	//		std::cout << "node: " << node->_key << std::endl;
	//		std::cout << "gp: " << gp->_key << std::endl;
	//		std::cout << "p: " << p->_key << std::endl;


			node->_parent->_parent = gp;
			gp->_left = node;
			p->_parent = node;
			p->_right = node->_left;
			node->_left = p;
		};
		//	end rotate

		void tree_printHelper(Node _root, std::string indent, bool last) {
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
				tree_printHelper(_root->_left, indent, false);
				tree_printHelper(_root->_right, indent, true);
			}
		}

		void tree_print() {
			if (_root) {
				tree_printHelper(_root, "", true);
			}
		}

		void tree_clear(Node node) {
			if (node == _nil)
				return;
			tree_clear(node->_left);
			tree_clear(node->_right);
			_root = _nil;
		}
};

}

#endif

//RESOURCES::
//	www.programiz.com/dsa/red-black-tree