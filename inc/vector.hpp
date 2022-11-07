#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_
#include <memory>
#include <cstddef> // for ptrdiff_t
#include <iterator> // substitute later 

/**
 * @brief Vectors are sequence containers representing arrays that can change in size
 * Template class: We want to allow users to use vector to hold a variety of types.
*/
namespace ft {

	template <class T, class Alloc = std::allocator<T> > // generic template
	class vector {
		public: // interface
//											Definition														Member type
			typedef						T																			value_type;
			typedef						Alloc																	allocator_type;
			typedef typename	Alloc::reference 											reference;
			typedef typename	Alloc::const_reference 								const_reference;
			typedef typename	Alloc::pointer												pointer;
			typedef typename	Alloc::const_pointer									const_pointer;

			typedef 					pointer																		iterator;
			typedef 					const T*															const_iterator;
			typedef typename 	std::reverse_iterator<iterator>				reverse_iterator;
			typedef typename	std::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef 					ptrdiff_t															difference_type;
			typedef 					size_t																size_type;

		private: // implementation
			allocator_type	_allocator;	//	Allocator object
			iterator	data;
			iterator	limit;
			//size_type				size;			//	Initial container size(number of elements)

		public:
		/********************************************************************
		 * 													MEMBER FUNCTIONS												*
		 ********************************************************************/
		/*** Constructors ***/

			// Empty container constructor (default)
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
				_allocator(alloc),
				data(0),
				limit(0)
			{
				//create();
			}

			// fill constructor 
			explicit
			vector (size_t n, const value_type& val = value_type(), 
							const allocator_type& alloc= allocator_type()) :
				_allocator(alloc),
				data(0),
				limit(0)
			{}

			// range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type()) :
								_allocator(alloc),
								data(0)
			{
				(void) first;
				(void) last;
			}
	
			// copy constructor
			vector (const vector& rhs) :
				_allocator(rhs._allocator),
				data(NULL)
			{
				// create(x.begin(), x.end());
			}

			// destructor
			~vector() {}

			/**
			 * @details We explicitly test for self-assignment by comparing the pointer
			 * and 'this', which points to the left-hand side. If the objects are the same,
			 * then there's nothing to do in the assignment operator, and we immediatly
			 * fall through to the return statement.
			 * If the objects are different, we need to free the old space and assign new
			 * values to each element, copying the contents from the right-hand side to the
			 * newly allocated array.
			 * 
			 * If we didn't check for self-assignment, we would always uncreate() the existing
			 * array from the left-hand operand, destroying the elements and returning the space
			 * that had been used. However, if the two operands were the same object, then the 
			 * right operand, the result would be that, when we freed the space held by the left 
			 * operand, we would also have freed the space for the right-hand object. When create()
			 * attempted to copy the elements from 'rhs', those elements would have been destroyed
			 * and the memory returned to the system.
			* /
			vector& operator= (const vector& rhs) {
				// check for Self-assignment
			//	if (&rhs != this) {
			//		// free the array in the left-hand side
			//		 uncreate();
			//		// copy elements from the right-hand to the left-hand side
			//		 create(rhs.begin(), rhs.end());
			//	}
				return *this;
			}

			/*** Iterators ***/

			// begin: Return iterator to beginning
			iterator begin() {
				return data;
			}

			const_iterator begin() const {
				return data;
			}

			// end: Return iterator to end
			iterator end() {
				return limit;
			}

			const_iterator end() const {
				return limit;
			}

			// rbegin: 				Return reverse iterator to reverse beginning
			iterator rbegin() {
				return data + limit;
			}

			// rend: 					Return reverse iterator ro reverse end
			iterator rend() {
				return data;
			}

			// cbegin 				Return const_iterator to beginning
			const_iterator cbegin() const{
				return data;
			};

			// cend 					Return const_iterator to end
			const_iterator cend() {
				return data + size;
			};

			// crbegin				Return cons_reverse_iterator to reverse beginning
			const_iterator crbegin() {
				return data + size;
			}
			// crend					Return const_reverse_iterator to reverse end
			const_iterator crend() {
				return data;
			}

			/*** Capacity ***/
			// size: 					Return size
			size_type size() const {
				return limit - data;
			}
			// maxsize: 			Return maximum size
			// resize: 				Change size
			// capacity: 			Return size of allocated storage capacity
			// empty: 				Test whether vector is empty
			// reserve: 			Request a change in capacity
			// shrink_to_fit: Shrink to fit

			/*** Element access ***/
			// operator[]: 		Access element
			reference operator[](size_type n) {
				return data[n];
			}
			
			const_reference operator[](size_type n) const {
				return data[n];
			}
			// at: 						Access element
			// front: 				Access first element
			// back: 					Access last element
			// data: 					Access data

			/*** Modifiers ***/
			// assign: 				Assign vector content
			// push_back: 		Add element at the end
			void push_back( const value_type& value ) {
				(void) value;
			};
			// pop_back:			Delete last element
			// insert:				Insert elements
			// erase:					Erase elements
			// swap:					Swap content
			// emplace:				Construct and insert element
			// emplace_back		Construct and insert element at the end

			/*** Allocator ***/
			// get_allocator: Get allocator

		/********************************************************************
		 * 										NON-MEMBER FUNCTION OVERLOADS									*
		 ********************************************************************/
		// Relational operators
		template <class TO, class AllocO> friend bool operator== (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
		template <class TO, class AllocO> friend bool operator!= (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
		template <class TO, class AllocO> friend bool operator<  (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
		template <class TO, class AllocO> friend bool operator<= (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
		template <class TO, class AllocO> friend bool operator>  (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
		template <class TO, class AllocO> friend bool operator>= (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);

		// swap
	};
			// Operator= : Assign content
	template <class T, class Alloc> 
	bool operator == (const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs) {
		return lhs	==	rhs; }

	template <class T, class Alloc> 
	bool operator != (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return lhs	!=	rhs; }

	template <class T, class Alloc> 
	bool operator <	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return lhs	<	rhs; }

	template <class T, class Alloc> 
	bool operator <=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return lhs	<=	rhs; }

	template <class T, class Alloc> 
	bool operator >	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return lhs	>	rhs; }

	template <class T, class Alloc> 
	bool operator >=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return lhs	>=	rhs; }

}

#endif

// Resources: 
//	Accelerated C++ Practical Programming by Example - Andrew Koenig, Barbara E. Moo
// 	11.3.3 Assignment is not initialization (bookmark)
