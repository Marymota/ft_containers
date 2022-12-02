#ifndef _ITERATOR_TRAITS_HPP_
#define _ITERATOR_TRAITS_HPP_

#include <iterator>
#include <cstddef>

namespace ft {
	
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
		typedef T																value_type;
		typedef ptrdiff_t												difference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef T*															pointer;
		typedef T&															reference;
	};
}

#endif