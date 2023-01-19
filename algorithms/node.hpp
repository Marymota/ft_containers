#ifndef _BSTNODE_HPP_
#define _BSTNODE_HPP_

#include <iostream>

namespace ft {

	template <typename T>
 	struct BSTNode {

		typedef T								value_type;				
		typedef BSTNode					node_type;
		typedef BSTNode*				Node;
		typedef const BSTNode*	const_Node;
		typedef size_t					size_type;

		value_type	_data;
		Node				_left;
		Node				_right;
		Node				_parent;
		size_type		_count;
	
		BSTNode(value_type val)	: _data(val), _left(NULL), _right(NULL), _parent(NULL), _count(0) {}

		Node minimum(Node x){ while (x->_left != NULL){ x = x->_left; } return x; }
		Node maximum(Node x){ while (x->_right != NULL){ x = x->_right; } return x; }
		const_Node minimum(const_Node x) const { while (x->_left != NULL){ x = x->_left; } return x; }
		const_Node maximum(const_Node x) const { while (x->_right != NULL){ x = x->_right; } return x; }

		virtual ~BSTNode() {}

	}; // end struct BSTNode
}

#endif