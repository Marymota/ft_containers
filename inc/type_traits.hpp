#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_

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

	template <bool B, class T = void> struct enable_if {};

	template<class T>	struct enable_if<true, T>
	{ typedef T value; 	};// If true define the T type value

	/** @integral_constant: Template designed to provide compile-time constants as types
	 */

	template <class T, T v>
	struct integral_constant {
		typedef T value_type;
		static const value_type value = v;
		typedef integral_constant<T,v> type;
		operator value_type() const { return value; }
	};

	// Instantiation of integral_constant to represent the bool value true
	typedef integral_constant<bool,true> true_type;
	// Instantiation of integral_constant to represent the bool value false
	typedef integral_constant<bool,false> false_type;

	// Trait class that identifies whether T is an integral type.
	template <typename> struct is_integral_type : false_type {};

	template<>	struct is_integral_type<bool> : true_type {};
	template<>	struct is_integral_type<char> : true_type {};
	template<>	struct is_integral_type<wchar_t> : true_type {};
	template<>	struct is_integral_type<signed char> : true_type {};
	template<>	struct is_integral_type<short int> : true_type {};
	template<>	struct is_integral_type<int> : true_type {};
	template<>	struct is_integral_type<long int> : true_type {};
	template<>	struct is_integral_type<long long int> : true_type {};
	template<>	struct is_integral_type<unsigned char> : true_type {};
	template<>	struct is_integral_type<unsigned short int> : true_type {};
	template<>	struct is_integral_type<unsigned int> : true_type {};
	template<>	struct is_integral_type<unsigned long int> : true_type {};
	template<>	struct is_integral_type<unsigned long long int> : true_type {};

	template<typename T> struct is_integral : is_integral_type<T> {};
	}


#endif