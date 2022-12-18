#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

#include <memory>

namespace ft {

enum Rb_color { red = false, black = true};

template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = std::allocator<Value> >
class rb_tree {
	typedef rb_tree* node;
	typedef const rb_tree* const_node;

	Rb_color	_color;
	node			_parent;
	node			_left;
	node			_right;

	static node minimum(node x) {
		while (x->_left != 0)
			x = x->_left;
		return x;
	}
};

}

#endif