#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <vector>	//change to ft::vector when finished
#include "../inc/vector.hpp"	//change to ft::vector when finished
	/**
	 * @brief Stacks are designed	to operate in a LIFO context (last-in first-out), 
	 * where elements are	inserted and extracted only from one end of the container.
	 * Stacks are implemented as container adaptors, which	are classes that use an
	 * encapsulated object of a specific container class as its underlying container
	 * providing a specific set of functions to access its elements. The standard
	 * container classes vector, deque and list fulfill these requirements.
	*/

namespace ft {

	/**	Template parameters:
		*	<T> type of the elements; Aliases as member type stack::valye_type
		*	Container: Underlying container object type, where the elements are stored.
		*	Aliases as member type stack::container_type
	*/
	template< class T, class Container = ft::vector<T> > //change to ft::vector when finished
	class stack {
		public:
//											Member type									Definition
			typedef 					T														value_type;				//	elements type
			typedef 					Container										container_type;		//	underlying container type
			typedef typename	Container::size_type				size_type;				//	unsigned integral type
			typedef typename	Container::reference				reference;
			typedef	typename	Container::const_reference	const_reference;	
			
		protected:
			Container c;

		public:
			/**
				*	@question:	->	explicit stack (const container_type& ctnr = container_type()) : c(ctnr){} 
				*							Container c must be initialized in the example above
				*							->	Below, same constructor as above but 'c' does not need to be initialized (why ?)
			*/
			explicit stack(const Container& = Container()){}														// constructor
			// Member functions
			bool 							empty() const		 						{ return c.empty(); 				}	// Test if container is empty
			void							pop() 											{ return c.pop_back();			}	// Remove top element
			void 							push(const value_type& x) 	{ return c.push_back(x);		}	// Insert element
			size_type 				size() const 								{ return c.size();					}	// Return size
			value_type& 			top() 											{ return c.back();					}	// Access next element
			const value_type&	top() const 								{ return c.back(); 					}	// Access next element (const)

			/**	@attention c++11 functions are to be included ?
				* void 		emplace(const value_type& x){ return c.emplace_back(x);	}	// c++11 
				* Swap() //swap contents // c++11 
				* swap (stack) (Non-member function)
			*/

			/**
			 *	@brief	Non-member function overloads declarations
			 * 
			 *	@details	An operator must have exactly one argument
			 *	An operator member function can recieve only one parameter at a time from the stack.
			 * 	When defined as a member, the object for which it is called is implicitly 'this'
			 *	(just like any other member functions). The same applies for any other binary operators
			 *	which you have defined as members of your stack - you only provide one argument because
			 *	the "left-hand-side" argument of a binary function is implicit."
			 *	https://www.daniweb.com/posts/jump/195846
			 *	Non-member functions are allowed access to the privare part of a class and are called 
			 *	'friend' of the class. A function is made a 'friend' by declaration in that class.
			*/
			template <class TC, class Container_C> friend bool operator == (const stack<TC, Container_C>& lhs, const stack<TC, Container_C>& rhs);
			template <class TC, class Container_C> friend bool operator != (const stack<TC, Container_C>& lhs, const stack<TC, Container_C>& rhs);
			template <class TC, class Container_C> friend bool operator <  (const stack<TC, Container_C>& lhs, const stack<TC, Container_C>& rhs);
			template <class TC, class Container_C> friend bool operator <= (const stack<TC, Container_C>& lhs, const stack<TC, Container_C>& rhs);
			template <class TC, class Container_C> friend bool operator >  (const stack<TC, Container_C>& lhs, const stack<TC, Container_C>& rhs);
			template <class TC, class Container_C> friend bool operator >= (const stack<TC, Container_C>& lhs, const stack<TC, Container_C>& rhs);

	};

	/**	Non-member function overloads
		*	relational-operators (performs the appropriate comparison operation between lhs and rhs)
		*	@details	segmentation fault if 'c' is not used (i.e. lhs.c == rhs.c);
	*/	
	template <class T, class Container> 
	bool operator == (const ft::stack<T, Container>& lhs, const ft::stack<T, Container>& rhs) {
		return lhs.c	==	rhs.c; }

	template <class T, class Container> 
	bool operator != (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
		return lhs.c	!=	rhs.c; }

	template <class T, class Container> 
	bool operator <	(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { 
		return lhs.c	<	rhs.c; }

	template <class T, class Container> 
	bool operator <=	(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { 
		return lhs.c	<=	rhs.c; }

	template <class T, class Container> 
	bool operator >	(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { 
		return lhs.c	>	rhs.c; }

	template <class T, class Container> 
	bool operator >=	(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { 
		return lhs.c	>=	rhs.c; }
}

#endif