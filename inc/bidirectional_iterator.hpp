#ifndef _BIDIRECTIONAL_ITERATOR_HPP_
#define _BIDIRECTIONAL_ITERATOR_HPP_

#include <iterator>
#include <cstddef>
#include "iterator_traits.hpp"
#include "../algorithms/bst.hpp"

namespace ft {

	template<typename Tp>
	class BST_iterator {

		public:
			typedef Tp 																value_type;
			typedef Tp& 															reference;
			typedef Tp* 															pointer;

			typedef bidirectional_iterator_tag				iterator_category;
			typedef ptrdiff_t													difference_type;

			typedef BST_iterator<Tp>									it;
			typedef typename BSTNode<Tp>::node_type		node_type;
			typedef node_type*												Node;

			BST_iterator<Tp>() : _node() {}
			explicit BST_iterator(Node x) : _node(x) {}
			BST_iterator(const BST_iterator& ref) : _node(ref._node) {}
			~BST_iterator() {}

			BST_iterator& operator=(const BST_iterator& copy) {
				if(this != &copy)
					_node = copy._node;
				return (*this);
			}

		private:
			Node _node;

		public:
			bool operator!=(const BST_iterator& x) const 	{ return (_node != 	x._node);}
			bool operator==(const BST_iterator& x) const 	{ return (_node == 	x._node);}

			BST_iterator operator-(difference_type val) const { return BST_iterator<Tp>(_node - val);}
			difference_type operator-(BST_iterator const& rhs) const { return _node - rhs._node;}

			BST_iterator operator+(difference_type val) const { return BST_iterator<Tp>(_node + val);}
			difference_type operator+(BST_iterator const& rhs) const { return _node + rhs._node;}

			BST_iterator operator++() { ++_node; return *this; }
			BST_iterator operator++(int) { BST_iterator it(*this); ++_node; return it; }
			BST_iterator operator--() { --_node; return *this; }
			BST_iterator operator--(int) { BST_iterator it(*this); --_node; return it; }
			reference operator*() const { return static_cast<Node>(_node)->_data; }
			reference operator->() const { return *_node; }
	};
}

#endif