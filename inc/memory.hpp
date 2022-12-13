#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

namespace ft {
	template<class InputIterator, class ForwardIterator>
		ForwardIterator uninitialized_copy( InputIterator first, InputIterator last,
																				ForwardIterator result )
	{
		for(; first!=last; ++result, ++first)
			new (static_cast<void*>(&*result))
				typename iterator_traits<ForwardIterator>::value_type(*first);
		return result;
	}
};

#endif