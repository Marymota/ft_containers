#ifndef _PAIR_HPP_
#define _PAIR_HPP_

#include <iterator>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"
#include "random_access_iterator.hpp"

namespace ft {

template <class T1, class T2> 
struct pair {

	public:
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		// default constructor
		pair() : first(), second() {};
		// copy
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};
		// initialization
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr) 
		{ 
			if (*this = pr) return *this;
			first(pr.first);
			second(pr.second);
			return *this;
		}
};
}

#endif