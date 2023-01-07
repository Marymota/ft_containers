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
		// Member types
		typedef T1	first_type;		//	type of the first template parameter
		typedef T2	second_type;	//	type of the second template parameter

		// Member objects
		T1 first;	// first value in pair
		T2 second;	// second value in pair

		// default constructor (constructs a pair object)
		pair() : first(), second() {};

		// copy
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};

		// initialization
		pair (const first_type& a, const second_type& b) : first(a), second(b) {}

		pair& operator= (const pair& pr) 
		{ 
			if (*this == pr) return *this;
			this->first(pr.first);
			this->second(pr.second);
			return *this;
		}
};


// need to add relational operators 

template <class T1, class T2>
pair<T1,T2> make_pair (T1 x, T2 y) { return ( pair<T1,T2>(x,y) ); }

};

#endif