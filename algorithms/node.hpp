#ifndef _BSTNODE_HPP_
#define _BSTNODE_HPP_

#include <iostream>

namespace ft {

	template <class Key, class T>
	struct BSTNode {

		typedef Key			key_type;
		typedef T 			value_type;
		typedef size_t	size_type;

		Key				_key;
		T				_data;
		BSTNode *		_left;
		BSTNode	*		_right;
		size_type		_count;
	
		BSTNode()	: _key(0), _data(0), _left(NULL), _right(NULL), _count(0) {}
		BSTNode(Key key, value_type data, size_type count) : _key(key), _data(data), _left(NULL), _right(NULL), _count(count) {}

		BSTNode* minimum(BSTNode* x){ while (x->_left != NULL){ x = x->_left; } return x; }
		BSTNode* maximum(BSTNode* x){ while (x->_right != NULL){ x = x->_right; } return x; }

		key_type get_node_key() { return this->_key; }
		value_type get_node_value() { return this->_data; }

	}; // end struct BSTNode
}

#endif