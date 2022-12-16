#ifndef _IS_INTEGRAL_HPP_
#define _IS_INTEGRAL_HPP_

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

		/** @integral_constant: Template designed to provide compile-time constants as types*/
		template <class T, T v>
		struct integral_constant {
			typedef T value_type;
			static const value_type value = v;
		};

		// Instantiation of integral_constant to represent the bool value true
		typedef integral_constant<bool,true> true_type;
		// Instantiation of integral_constant to represent the bool value false
		typedef integral_constant<bool,false> false_type;

		// Trait class that identifies whether T is an integral type.
		template<typename>	struct is_integral : public false_type {};

		template<>	struct is_integral<bool>									 	: public true_type {};
		template<>	struct is_integral<char>									 	: public true_type {};
		template<>	struct is_integral<wchar_t>									: public true_type {};
		template<>	struct is_integral<signed char>							: public true_type {};
		template<>	struct is_integral<short int>								: public true_type {};
		template<>	struct is_integral<int>											: public true_type {};
		template<>	struct is_integral<long int>							 	: public true_type {};
		template<>	struct is_integral<long long int>						: public true_type {};
		template<>	struct is_integral<unsigned char>						: public true_type {};
		template<>	struct is_integral<unsigned short int> 			: public true_type {};
		template<>	struct is_integral<unsigned int> 						: public true_type {};
		template<>	struct is_integral<unsigned long int> 		 	: public true_type {};
		template<>	struct is_integral<unsigned long long int> 	: public true_type {};
	}


#endif