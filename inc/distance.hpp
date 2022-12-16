#ifndef _DISTANCE_HPP_
#define _DISTANCE_HPP_

#include <iterator>
#include "iterator_traits.hpp"
#include "random_access_iterator.hpp"

namespace ft {

	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, std::input_iterator_tag,
	typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) {
		InputIterator result = 0;
		for (; first != last; ++first)
			result++;
		return result;
	}

	template <class random_access_iterator>
	typename ft::iterator_traits<random_access_iterator>::difference_type
	_distance(random_access_iterator first, random_access_iterator last, std::random_access_iterator_tag) {
		return last - first;
	}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return _distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
	}
};

#endif