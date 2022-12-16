#ifndef _ENABLE_IF_HPP_
#define _ENABLE_IF_HPP_

/** @brief type_traits (Header)
 * This Header defines a series of classes to obtain type information on compile-time.
 * Vector range constructor requires the std::is_integral type_trait and std::enable_if
 * so that it will call the fill constructor instead of the range constructor
 * when integers are given as arguments
 */ 

namespace ft {

	/**	If B is true, enable_if has a public member typedef type, equal to T;
	 * otherwise, there is no member typedef.
	 * 
	 * This metafunction is a conveninet way to leverage
	 * SFINAE ("Substitution Failure is Not An Error")
	 * prior to C++20's concepts, in particular for conditionally
	 * removing functions from the candidate set based on type traits.
	 */ 

		// ENABLE_IF: Enable type if condition is met (possible implementation)
		template <bool B, class T = void> struct enable_if {};
		template<class T>	struct enable_if<true, T> { typedef T type; };// If true define the T type value
}
#endif