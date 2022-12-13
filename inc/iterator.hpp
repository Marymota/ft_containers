#ifndef _ITERATOR_HPP_
#define _ITERATOR_HPP_

#include <iterator>

namespace ft {

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};


	template <class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last, input_iterator_tag) {
		typename ft::iterator_traits<InputIterator>::difference_type result(0);
		for (; first != last; ++first)
			++result;
		return result;
	}

	template <class random_access_iterator>
	typename ft::iterator_traits<random_access_iterator>::difference_type
	_distance(random_access_iterator first, random_access_iterator last, random_access_iterator_tag) {
		return last - first;
	}

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last) {
		return _distance(first, last, typename iterator_traits<InputIterator>::iterator_category());
	}
};

#endif