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
			this->first = pr.first;
			this->second = pr.second;
			return *this;
		}
};

	/*-----------------------------------*/
 /**	NON:MEMBER:FUNCTION:OVERLOADS:	*/
/*-----------------------------------*/
/** @_relational_operators: */

		template <class T1, class T2>
		bool operator== (	const ft::pair<T1, T2>& lhs,
											const ft::pair<T1, T2>& rhs)
		{	return lhs.first == rhs.first && lhs.second == rhs.second; }


		template <class T1, class T2>
		bool operator!= (	const ft::pair<T1, T2>& lhs,
											const ft::pair<T1, T2>& rhs)
		{	return !(lhs == rhs);	}


		template <class T1, class T2>
		bool operator<  (	const ft::pair<T1, T2>& lhs,
											const ft::pair<T1, T2>& rhs)
		{	if (lhs.first < rhs.first) return true;
			else if (rhs.first < lhs.first) return false;
			else if (lhs.second < rhs.second) return true; 
			else return false; }


		template <class T1, class T2>
		bool operator<= (	const ft::pair<T1, T2>& lhs,
																										const ft::pair<T1, T2>& rhs)
		{	return !(rhs < lhs);	}


		template <class T1, class T2>
		bool operator>  (	const ft::pair<T1, T2>& lhs,
																										const ft::pair<T1, T2>& rhs)
		{ return rhs < lhs; }


		template <class T1, class T2>
		bool operator>= (	const ft::pair<T1, T2>& lhs,
																										const ft::pair<T1, T2>& rhs)
		{ return !(lhs < rhs);  }


// need to add relational operators 

template <class T1, class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y) { return ( ft::pair<T1,T2>(x,y) ); }

};

#endif