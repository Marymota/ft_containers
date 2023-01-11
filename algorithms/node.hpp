#ifndef _BSTNODE_HPP_
#define _BSTNODE_HPP_

#include <iostream>

namespace ft {

	template <class Key, class T>
	struct BSTNode {

		typedef Key	key;
		typedef T 	value_type;

		key					_key;
		value_type	_data;
		BSTNode *		_left;
		BSTNode	*		_right;
	
		BSTNode()	: _key(0), _data(0), _left(NULL), _right(NULL) {}
		BSTNode(key key, value_type data) : _key(key), _data(data), _left(NULL), _right(NULL) {}

		key get_node_key() { return this->_key; }
		value_type get_node_value() { return this->_data; }

		BSTNode minimum(BSTNode x){ while (x->_left != NULL){ x = x->_left; } return x; }
		BSTNode maximum(BSTNode x){ while (x->_right != NULL){ x = x->_right; } return x; }
	}; // end struct BSTNode
}

#endif