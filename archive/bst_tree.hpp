#ifndef _BST_HPP_
#define _BST_HPP_

#include "../inc/pair.hpp"
#include "../inc/bidirectional_iterator.hpp"
#include "../inc/reverse_iterator.hpp"

namespace ft {

	template <class T>
	struct BSTNode {

		T					_data;
		BSTNode*	_left;
		BSTNode*	_right;

		BSTNode(T data, BSTNode* left, BSTNode* right) : _data(data), _left(left), _right(right) {}
};

template <	class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<BSTNode<T> > >
class BST {

public:

	 /*----------------*/
	/**	MEMBER:TYPES: */
 /*----------------*/

	typedef Key																					key_type;
	typedef T																						value_type;
	typedef Compare																			key_compare;
	typedef Alloc																				allocator_type;
	typedef value_type& 																reference;
	typedef const value_type&														const_reference;
	typedef value_type*																	pointer;
	typedef const value_type*														const_pointer;

	typedef BSTNode<value_type>													node_type;
	typedef BSTNode<value_type>*												Node;

	typedef ft::bidirectional_iterator<node_type>				iterator;
	typedef ft::bidirectional_iterator<const node_type>	const_iterator;  
	typedef ft::reverse_iterator<iterator>							reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;

	typedef std::size_t																	size_type;
	typedef std::ptrdiff_t															difference_type;

private:
	// This personalized allocator is created to allocate pairs (Key -> Value)
	typedef typename Alloc::template	rebind<node_type>::other	node_allocator_type;

	Node								_root;
	allocator_type			_alloc;
	key_compare					_comp;
	size_type						_size;
	node_allocator_type _alloc_tree;

  /**-------------------*/
 /** MEMBER:FUNCTIONS: */
/*--------------------*/
public:

	explicit BST(const key_compare& comp = key_compare(), allocator_type const& alloc = allocator_type()) :
	_root(NULL), _alloc(alloc), _comp(comp), _size(0) {
		_root = _alloc_tree.allocate(1);
		_alloc_tree.construct(_root, T());
	}

	Node* find(Key key) {
		Node x = _root;
		while (x != NULL)
			if (key > x)
				x = x->_right;
			else if (key < x)
				x = x->_left;
			else
				x = NULL;
		return x;
	}

	ft::pair<iterator, bool> insert(const value_type& val) {
		iterator it = find();

		if (it != NULL)
			return ft::make_pair(it, false);

		Node node = _alloc_tree.allocate(1);
		_alloc_tree.construct(node, node_type(val, NULL, NULL));

		it = iterator(recursive_insert(node));
		_size++;

		return ft::make_pair(it, true);
	}

	Node recursive_insert(Node node) {
		if (node->_left != NULL)
		{
			insert(node->_left->_data);
			recursive_insert(node->_left);
		}
		if (node->_right != NULL)
		{
			insert(node->_right->_data);
			recursive_insert(node->_right);
		}
		return node;
	}

	BST&	operator=(const BST& x) {
		Node node = NULL;
		if (x._size != 0) {
			recursive_insert(x._root);
			insert(x._root->_data);
		}
		return *this;
	}

	value_type& operator[] (const key_type& k) {
		return (*((this->insert(ft::make_pair(k, value_type()))).first));
	}

	void tree_printHelper(Node _root, std::string indent, bool last) {
		if (_root != NULL) {
			std::cout << indent;
			if (last) {
				std::cout<<"R----";
				indent += "    ";
			} else {
				std::cout << "L----";
				indent += "|    ";
			}
			std::cout << _root->_key << std::endl;
			tree_printHelper(_root->_left, indent, false);
			tree_printHelper(_root->_right, indent, true);
		}
	}

	void tree_print() {
		if (_root) {
			tree_printHelper(_root, "", true);
		}
	}
}; }

#endif