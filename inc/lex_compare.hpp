#ifndef _LEXICOGRAPHICAL_COMPARE_HPP_
#define _LEXICOGRAPHICAL_COMPARE_HPP_

namespace ft {

	/** @lexicographical_comparison: 
	 * 	Returns true if the range [first1, last1) compares
	 * 	lexicographically less than the range [first2, last2).
	 * 	The kind of comparison generally used to sort words alphabetically in dictionaries;
	 * 	
	*/
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(	InputIterator1 first1, InputIterator1 last1,
																InputIterator2 first2, InputIterator2 last2) 
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			//	Compare each element of each range
			//	Return (true/false) if an element of the first range 
			//	is not equal to the element of the second range
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		// Finally compare the size of both ranges
		return (first1 == last1) && (first2 != last2);
	}

	template<class InputIterator1, class InputIterator2, class Compare >
	bool lexicographical_compare(	InputIterator1 first1, InputIterator1 last1,
																InputIterator2 first2, InputIterator2 last2,
																Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

};


#endif