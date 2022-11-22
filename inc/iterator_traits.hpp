#ifndef _ITERATOR_TRAITS_HPP_
#define _ITERATOR_TRAITS_HPP_

#include <cstddef>

namespace ft {
	
	struct input_iterator {};
	struct output_iterator {};
	struct forward_iterator : public input_iterator {};
	struct bidirectional_iterator : public forward_iterator {};
	struct random_access_iterator : public bidirectional_iterator {};

	template <class iterator>
	struct iterator_traits {
		typedef typename iterator::value_type						value_type;
		typedef typename iterator::difference_type			difference_type;
		typedef typename iterator::iterator_category		iterator_category;
		typedef typename iterator::pointer							pointer;
		typedef typename iterator::reference						reference;
	};

	template <class T>
	struct iterator_traits<T*> {
		typedef T														value_type;
		typedef ptrdiff_t										difference_type;
		typedef ft::random_access_iterator	iterator_category;
		typedef T*													pointer;
		typedef T&													reference;
	};
}

#endif