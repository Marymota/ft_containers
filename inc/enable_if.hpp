#ifndef __ENABLE_IF__
#define __ENABLE_IF__

namespace ft {

	template <bool, class T> 
	struct enable_if 
	{};

	template<class T>
	struct enable_if<true, T>
	{ 
		typedef T value; // If true define the T type value
	};

	template <class T, T v>
	struct integral_constant
	{
		typedef T value_type;
		typedef integral_constant<T,v> type;
		static const T value = v;
		operator T() { return value; }
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template<typename T>
	struct is_integral : public false_type{};

	template<>
	struct is_integral<char> : public true_type{};
}

#endif