#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <cstddef>
#include <memory>
#include <iostream>

#include "../inc/iterator_traits.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"
#include "../inc/pair.hpp"

namespace ft {

	enum Color { RED = false, BLACK = true };

template <class Val>
struct Rb_tree_node {

	typedef Rb_tree_node*	Node;
	typedef Rb_tree_node<Val>* Link_type;
	Val value_field;

	Node	_parent;
	Node	_left;
	Node	_right;
	Color	_color;

	static Node minimum(Node x){ while (x->_left != 0){ x = x->_left; } return x; }
	static Node maximum(Node x){ while (x->_right != 0){ x = x->_right; } return x; }
};

template <class Val>
struct Rb_tree_Iterator{

	typedef Val 																					value_type;

	typedef Rb_tree_node<value_type> 											node_type;
	typedef Rb_tree_node<value_type>*											Node;
	typedef bidirectional_iterator_tag										iterator_category;
	typedef ft::bidirectional_iterator<node_type>					iterator;
	typedef ft::bidirectional_iterator<const node_type>		const_iterator;
	Node node;

	Rb_tree_Iterator(Node x) {node = x;}

	void increment(){
		if (node->_right) {
			node = node->_right;
			while (node->_left){ node = node->_left; }
		}
		else {
			Node* parent = node->_parent;
			while (parent->_right == node) {
				node = parent;
				parent = node->_parent;
			}
			if (node->_right != parent)
				node = parent;
		}
	}

	void decrement(){
		if (node->_color == RED && node->_parent->_parent == node)
			node = node->_right;
		else if (node->_left) {
			node = node->_left;
			while (node->_right){ node = node->_right; }
		}
		else {
			Node* parent = node->_parent;
			while (parent->_left == node) {
				node = parent;
				parent = node->_parent;
			}
			if (node->_left != parent)
				node = parent;
		}
	}
};

template <class Key, class Val,	class Compare = std::less<Key>, class Alloc = std::allocator<Val> >
class Rb_tree {

protected:
	typedef Rb_tree_node<Val>* 											Node;
	typedef Rb_tree_node<Val>												node_type;

public:
	typedef Val																			value_type;
	typedef Compare																	key_compare;
	typedef value_type* 														pointer;
	typedef const value_type* 											const_pointer;
	typedef value_type&															reference;
	typedef const value_type& 											const_reference;
	typedef size_t																	size_type;
	typedef ptrdiff_t 															difference_type;
	typedef Alloc 																	allocator_type;
	typedef ft::Rb_tree_Iterator<value_type> 				iterator;
	typedef ft::Rb_tree_Iterator<const value_type> 	const_iterator;
	typedef ft::reverse_iterator<value_type> 				reverse_iterator;
	typedef ft::reverse_iterator<const value_type> 	const_reverse_iterator;

private:
	Node 						_root;
	Node 						_nil;
	allocator_type 	_alloc;
	
	public:	
		Rb_tree(const key_compare& comp, allocator_type const& alloc = allocator_type()) :
			_root(NULL),
			_nil(NULL),
			_alloc(alloc)
		{
			_nil = _alloc.allocate(1);
			_alloc.construct(_nil, node_type(value_type(), NULL, NULL, NULL, BLACK));
			_root = _nil;
		}
		
		~Rb_tree() {
			tree_clear(_root);
			_root = _nil;
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}
	
		iterator begin(){ return iterator(_root->_left); }
		iterator end(){ return iterator(_root); }
		size_t size()const{ return 0; }
		bool empty()const{ return _root == _nil; }

		void tree_clear(Node node) {
			if (node == _nil)
				return;
			tree_clear(node->_left);
			tree_clear(node->_right);
	
			_alloc.destroy(node);
			_alloc.deallocate(node, 1);
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
		Node tree_sucessor(Node x){
			if (x == _nil){ return _nil; }
			if (x->_right != _nil)
				return tree_minimum(x->_right);
			Node y = x->_parent;
			while (y != _nil && x == y->_right) { x = y; y = y->_parent; }
			return y;
		}
		
		// The greatest node smaller than key
		Node tree_predecessor(Node x){
			if (x == _nil){ return _nil; }
			if (x->_left != _nil)
				return tree_maximum(x->_left);
			Node y = x->_parent;
			while (y != _nil && x == y->_left) { x = y; y = y->_parent; }
			return y;
		}

		Node create_node(const value_type key) {
			// Create a new empty node
			Node node = _alloc.allocate(1);
			_alloc.construct(node, node_type(key, NULL, _nil, _nil, RED));

			node->_key = key;
			node->_parent = _nil;
			// Assign NUll to the left and right child of new_node
			node->_left = _nil;
			node->_right = _nil;

			return node;
		}

		void tree_insert(const value_type key) {
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
			//_root->_color = BLACK;
		 	// Call insert_fix() to mantain the property of red_black tree if violated
			//if (node->_parent != NULL && node->_parent->_parent != NULL)
			//	tree_insert_fix(node);
		}

		Node tree_delete_node(Node node) {
			Node y;
			Node x; // the node child

			if(node->_left == _nil || node->_right == _nil){y = node; }
			else{ y = tree_sucessor(node); }

			if(y->_left != _nil) { x = y->_left; }
			else { x = y->_right; }

			if(x != _nil) {	x->_parent = y->_parent; }

			if(y->_parent == _nil) { _root = x; }
			else if (y == y->_parent->_left) { y->_parent->_left = x; }
			else { y->_parent->_right = x; }

			if (y != node) { node->_key = y->_key; } 
			else { _alloc.deallocate(node, 1); } // valgrind error because of this deallocation
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

			if (node->_color == RED && p->_color == RED)
			{

				if (un != _nil && un->_color == RED)
					tree_color_flip(node, un, gp);
				else if (node == node->_parent->_left)
					tree_rotate_right(node);
				else
					tree_rotate_left(node);
			//	tree_recolor(node->_parent);
			//	if (node->_color == RED && (node->_left->_color == RED || node->_right->_color == RED))
			//		tree_insert_fix(node);
			}
		}

	/**	@recolor: If new_node check if color rules are applied correctly
	*/
		void tree_recolor (Node node) {
			std::cout << "node: " << node->_key << std::endl;
			_root->_color = BLACK;
			if (node == _root) {
				if (node->_left != _nil)
					node->_left->_color = RED;
				if (node->_right != _nil)
					node->_right->_color = RED;
			else if (node->_color == RED)
			{
				if (node->_left != _nil)
					node->_left->_color = BLACK;
				if (node->_right != _nil)
					node->_right->_color = BLACK;
			}
		}	
		if (node->_color == RED) {
			node->_color = BLACK;
			node->_left->_color = RED;
			node->_right->_color = RED;
		}
	} // end recolor

/**	@color_flip: If new_node is red and has a red parent and a red aunt we color flip
*/
		void tree_color_flip(Node node, Node un, Node gp) {
			std::cout << "color flip" << std::endl<< std::endl;
			if (un->_color == RED) {
				node->_parent->_color = BLACK;
				un->_color = BLACK;
				gp->_color = RED;
			}
		};
		//	end color_flip

/**	@rotate: If new_node is red and has a red parent and a black aunt we rotate
 * 	@rotate_left: If new_node is on the right of its parent
 * 	@rotate_right: If new_node is on the right of its parent
*/
		void tree_rotate_right(Node node) {

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
				if (sColor == BLACK)
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
};

}

#endif

//RESOURCES::
//	www.programiz.com/dsa/red-black-tree