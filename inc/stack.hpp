#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <vector>	//change to ft::vector when finished
	
	/*	Stacks are designed	to operate in a LIFO context (last-in first-out), 
	where elements are	inserted and extracted only from one end of the container.

	Stacks are implemented as container adaptors, which	are classes that use an
	encapsulated object of a specific container class as its underlying container
	providing a specific set of functions to access its elements. The standard
	container classes vector, deque and list fulfill these requirements.	*/

namespace ft {

	//	Template parameters:
	//		T: type of the elements; Aliases as member type stack::valye_type
	//		Container: Underlying container object type, where the elements are stored.
	//			Aliases as member type stack::container_type
	template< class T, class Container = std::vector<T> >
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
			//?	->	explicit stack (const container_type& ctnr = container_type()) : c(ctnr){} 
			//?			Container c must be initialized in the example above
			//? ->	Below, same constructor as above but 'c' does not need to be initialized (why ?)
			explicit stack(const Container& = Container()){}															// constructor
			// Member functions
			bool 							empty() const		 						{ return c.empty(); 				}	// Test if container is empty
			void							pop() 											{ return c.pop_back();			}	// Remove top element
			void 							push(const value_type& x) 	{ return c.push_back(x);		}	// Insert element
	//	void 							emplace(const value_type& x){ return c.emplace_back(x);	}	// c++11 (necessary??)
			size_type 				size() const 								{ return c.size();					}	// Return size
			value_type& 			top() 											{ return c.back();					}	// Access next element
			const value_type&	top() const 								{ return c.back(); 					}	// Access next element (const)
// ( ! )	Swap() //swap contents
			//Non-member function overloads
// ( ! )	relational operators 
// ( ! )	swap (stack)
			//Non-member class specializations
// ( ! )	uses_allocator<stack>
	};
}

#endif