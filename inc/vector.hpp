#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <memory>		// add allocator<T>
#include <cstddef> 	// add ptrdiff_t
#include <iterator>

/** @details The <memory> header provides a class, called allocator<T>, that allocates
 * a block of uninitialized memory that is intended to contain objects of type T, and
 * returns a pointer to the initial element of that memory. 
*/


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

			typedef 					T*							iterator;
			typedef						const T*				const_iterator;
			typedef typename 	std::reverse_iterator<iterator>				reverse_iterator;
			typedef typename	std::reverse_iterator<const_iterator>	const_reverse_iterator;
			typedef 					ptrdiff_t															difference_type;
			typedef 					size_t																size_type;

		private: // implementation
			allocator_type	allocator;	//	Allocator object
			iterator	data;							//	First element
			iterator	avail;						//	(One past) the last element in the vec
			iterator	limit;						//	(One past) the allocated memory
			//size_type				size;			//	Initial container size(number of elements)

		public:
		/********************************************************************
		 * 													MEMBER FUNCTIONS												*
		 ********************************************************************/
		/*** Constructors ***/

			// Empty container constructor (default)
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
				allocator(alloc),
				data(0),
				avail(0),
				limit(0)
			{}

			// fill constructor 
			explicit
			vector (size_t n, const value_type& val = value_type(), 
							const allocator_type& alloc= allocator_type()) : allocator(alloc)
			{
				data = alloc(n);
				limit = avail = data + n;
				// Constructs all the elements in the range (first, last)
				// initializing them to the value of 'val'
				uninitialized_fill(data, limit, val);
			}

			// range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type()) :
								allocator(alloc),
								data(0)
			{
				data = allocator.allocate(last - first);
				limit = avail = data;
				std::uninitialized_copy(first, last, data);
			}
	
			// copy constructor
			vector (const vector& rhs) :
				allocator(rhs.allocator),
				data(NULL)
			{
				data = allocator.allocate(end() - begin());
				limit = avail = std::uninitialized_copy(begin(), end(), data);
			}

			// destructor
			~vector() {
				if (data) {
					// destroy (in reverse order) the elements that were constructed
					iterator it = avail;
					while (it != data)
						allocator.destroy(--it);
					// return all the space that was allocated
					allocator.deallocate(data, limit - data);
				}
				// reset pointers to indicate that the vector is empty again
				data = limit = avail = 0;
			}

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
			*/
			// Iterators 

			// begin: Return iterator to beginning
			iterator begin() {
				return data;
			}

			const_iterator begin() const {
				return data;
			}

			// end: Return iterator to end
			iterator end() {
				return &data[begin() + avail];
			}

			const_iterator end() const {
				return data + avail;
			}

			// rbegin: 				Return reverse iterator to reverse beginning
			reverse_iterator rbegin() {
				return reverse_iterator(&data[begin() + avail]);
			}

			// rend: 					Return reverse iterator to reverse end
			reverse_iterator rend() {
				return reverse_iterator(data);
			}

			// cbegin 				Return const_iterator to beginning
			const_iterator cbegin() const{
				return data;
			};

			// cend 					Return const_iterator to end
			const_iterator cend() {
				return &data[begin() + avail];
			};

			// crbegin				Return cons_reverse_iterator to reverse beginning
			const_iterator crbegin() {
				return reverse_iterator(&data[begin() + avail]);
			}
			// crend					Return const_reverse_iterator to reverse end
			const_iterator crend() {
				return reverse_iterator(data);
			}

			/*** Capacity ***/
			// size: 					Return size
			size_type size() const {
				return &data[limit];
			}
			// maxsize: 			Return maximum size
			// resize: 				Change size
			// capacity: 			Return size of allocated storage capacity
			// empty: 				Test whether vector is empty
			bool empty() const {
				if (!data)
					return (true);
				return (false);

			}
			// reserve: 			Request a change in capacity
			// shrink_to_fit: Shrink to fit

			/*** Element access ***/
			// operator[]: 		Access element
			reference operator[](size_type n) {
				return &data[n];
			}
			
			const_reference operator[](size_type n) const {
				return &data[n];
			}
			// at: 						Access element
			// front: 				Access first element
			// back: 					Access last element
			reference back() { return *(end() - 1); }
			const_reference back() const { return end() - 1; }	
			// data: 					Access data

			/*** Modifiers ***/
			// assign: 				Assign vector content
			// push_back: 		Add element at the end
			void push_back( const value_type& value )
			{
				// when growing, allocate twice as much space as currently in use
				size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

				//allocate  new space and copy existing elements to the new space
				pointer new_data = allocator.allocate(new_size);
				pointer new_avail = std::uninitialized_copy(data, avail, new_data);

				//return the old space
				this->~vector();

				//reset pointers to the newly allocated space
				data = new_data;
				avail = new_avail;
				limit = data + new_size;
				allocator.construct(avail++, value);
			};
			// pop_back:			Delete last element
			void pop_back() {
				allocator.destroy(end() - 1);
				--avail;
			}
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
//	https://djvu.online/file/rh2C1FgVK0ODE
// 	11.3.3 Assignment is not initialization (bookmark)
