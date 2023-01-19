#ifndef _PAIR_HPP_
#define _PAIR_HPP_

#include <iterator>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator_traits.hpp"
#include "random_access_iterator.hpp"

namespace ft {

/** Way to store two heterogeneus objects as a single unit. */
template <class T1, class T2> 
struct pair {

	public:
		// Member types
		typedef T1	first_type;		//	type of the first template parameter
		typedef T2	second_type;	//	type of the second template parameter

		// Member objects
		first_type	first;	// first value in pair
		second_type second;	// second value in pair

		// default constructor (constructs a pair object)
		pair() : first(first_type()), second(second_type()) {}

		// initialization
		pair( const first_type& x, const second_type& y) : first(x), second(y) {}

		// copy
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}



		pair& operator= (const pair& pr) 
		{ 
			if (*this == pr) return *this;
			first = pr.first;
			second = pr.second;

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


// Creates a pair object, deducing the target type from the types of arguments
template <class T1, class T2>
ft::pair<T1,T2> make_pair (T1 x, T2 y) { return ft::pair<T1,T2>(x,y); }

};

#endif