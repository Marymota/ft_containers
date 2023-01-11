#ifndef _BSTNODE_HPP_
#define _BSTNODE_HPP_

#include <iostream>

namespace ft {

	template <class T>
	class BSTNode {

	public:
		typedef T value_type;

		value_type 	_data;
		BSTNode *		_left;
		BSTNode	*		_right;

		BSTNode()	: _data(0), _left(NULL), _right(NULL) {}
		BSTNode(value_type data) : _data(data), _left(NULL), _right(NULL) {}
		BSTNode(value_type data, BSTNode * left, BSTNode * right) : _data(data), _left(left), _right(right) {}
	}; // end struct BSTNode
}

#endif