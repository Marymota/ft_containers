#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <memory>		// add allocator<T>
#include <cstddef> 	// add ptrdiff_t
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"

/** @details The <memory> header provides a class, called allocator<T>, that allocates
 *	a block of uninitialized memory that is intended to contain objects of type T, and
 *	returns a pointer to the initial element of that memory. 
 *	@brief Vectors are sequence containers representing arrays that can change in size.
 *	@container_properties:
 *	->	Vectors are sequence containers that are ordered in a strict linear sequence.
 *			Individual elements are accessed by their position in this sequence.
 *	-> Vectors are dynamic arrays that allow direct access to any element in the sequence,
 *			even through pointer arithmetics, and provides relatively fast addition/removal of
 *			elements at the end of the sequence. 
 *	-> A Vector container uses an allocator object to dynamically handle its storage needs.
 *	@template_class: We want to allow users to use vector to hold a variety of types.
 */

namespace ft {

	// Container definition
	template <class T, class Alloc = std::allocator<T> > // generic template
	class vector {

		public: // interface

//		MEMBER TYPES
//		Definition																									Member type				notes
			typedef	T																										value_type;				
			typedef Alloc																								allocator_type;		//allocator<value_type>
			typedef typename allocator_type::reference									reference;				//allocator: value_type&
			typedef typename allocator_type::const_reference 						const_reference;	//allocator: const value_type&
			typedef typename allocator_type::pointer										pointer;					//allocator: value_type*
			typedef typename allocator_type::const_pointer							const_pointer;		//allocator: const value_type*
			typedef	ft::random_access_iterator<value_type>							iterator;
			typedef	ft::random_access_iterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;	//signed integral type: ptrdiff_t		
			typedef	size_t																							size_type;				//unsigned integral type: difference_type

		protected: // implementation
			allocator_type	_allocator;				//	Allocator object
			pointer					_data;						//	First element
			pointer 				_size;						//	Last element in the vector 
			pointer					_capacity;				//	Las allocated piece of memory

		public:
		/********************************************************************
		 * 													MEMBER FUNCTIONS												*
		 ********************************************************************/
		/*** Constructors ***/

			// DEFAULT CONSTRUCTOR
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
				_allocator(alloc),
				_data(0),
				_size(0),
				_capacity(0)
			{}

			/** FILL CONSTRUCTOR
					@uninitialized_fill: Constructs all the elements in the range (first, last)
					initializing them to the value of 'val'
				*/
			explicit
			vector (size_type n, const value_type& val = value_type(), 
							const allocator_type& alloc= allocator_type()) : _allocator(alloc)
			{
				_data = _allocator.allocate(n);
				_size = _data;
				_capacity = _data + n;
				while (n--) {
					_allocator.construct(_size, val);
					_size++;
				}
			}
			// RANGE CONSTRUCTOR


			/** COPY CONSTRUCTOR
			 *	@details
			 * 	Memory is allocated equal to the capacity of the original vector
			 *	Elements of the original vector are copied to the new allocated space
			 */ 
			vector (const vector& x) {
				_data = _allocator.allocate(x.capacity());
				_size = std::uninitialized_copy(x.begin(), x.end(), _data);
				_capacity = _size;
			}

		// DESTRUCTOR
			~vector() {
				size_type save_size = size();
				/** @why: pointer i != _size don't work */
				for (size_type i = 0; i < save_size; i++){ 
					_size--;
				}
				if (_capacity)
					_allocator.deallocate(_data, capacity()); //	void deallocate (pointer p, size_type n);
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
			 * attempted to copy the elements from 'y', those elements would have been destroyed
			 * and the memory returned to the system.
			*/
		
			//	ITERATORS
			iterator begin(){ 											return iterator(_data);} 	
			const_iterator begin() const{						return const_iterator(_data);}						
			iterator end(){													return iterator(_size);}									
			const_iterator end() const{							return const_iterator(_size);}						
			reverse_iterator rbegin(){							return reverse_iterator(end()); }				
			const_reverse_iterator rbegin() const{ 	return const_reverse_iterator(end());}	
			reverse_iterator rend(){								return reverse_iterator(begin());}			
			const_reverse_iterator rend() const{		return const_reverse_iterator(begin());}
			const_iterator cbegin() const{					return const_iterator(_data);}				
			const_iterator cend() const{						return const_iterator(_size);}						
			const_reverse_iterator crbegin() const{	return const_reverse_iterator(end());}	
			const_reverse_iterator crend() const{		return const_reverse_iterator(begin());}

			// CAPACITY
			size_type size() const {			return _size - _data; }
			size_type max_size() const { 	return _capacity; } //?
			// resize
			size_type capacity() const { 	return _capacity - _data; }
			bool empty() const { 					return (begin() == end()); }
			// reserve: 			Request a change in capacity
			// shrink_to_fit: Shrink to fit

			// Element access
			reference operator[](size_type n) { 						return *(begin() + n );}
			const_reference operator[](size_type n) const { return *(begin() + n );}
			// at: 						Access element
			// front: 				Access first element
			// back: 					Access last element
			reference back() { return *(end() - 1); }
			const_reference back() const { return *(end() - 1); }	
			// data: 					Access data

			//	MODIFIERS
			/** @assign:	Assigns new contents to the vector replacing its current contents
			 *						and modifying its size accordingly. 
			 */
			// range
					//template <class InputIterator>
					//void assign (InputIterator first, InputIterator last,
					/** @why: Understand the necessity of using enable_if and is_integral
					//typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = u_nullptr) */
					//{
						// In the range version, the new contents are elements constructed from each of the
						// elements in the range between first and last, in the same order.
					//}
			// fill
			//	void assign (size_type n, const value_type& val){
					// In the fill version the new contents are n elements, each initializer to a copy of val.
			//	}
				

			/*	@push_back: Add element at the end
			 * 	If the storage capacity of the vector is not almost full 
			 *	(-1 from full capacity) a new object (val) is constructed
			 *	after the last element and the number of elements (size)
			 *	is incremented by one.
			 *	If the storage capacity of the vector is almost full its
			 *	necessary to extend the vector.
			 */
			
			void push_back(const value_type& val){
				if (_size != _capacity) {
					_allocator.construct(_size, val); //void construct ( pointer p, const_reference val );
					_size++;
				}
				else
					insert_aux(end(), val);
			}

			// pop_back:			Delete last element
			void pop_back() {
				_allocator.destroy(_data - 1);
				_size--;
			}

			// single element
			iterator insert (iterator position, const T& val) {
				size_type n = position - begin();
				if (_size != _capacity && position != end()) {
					_allocator.construct(_size, val); //void construct ( pointer p, const_reference val );
					_size++;
				}
				else {
					insert_aux(position, val);
				}
				return _data + n;
			}

			/**	@insert_aux:
			 *	If size does not exceeds the capacity of the vector,
			 *	we copy the vector elements to the space after position
			 * 	and construct the new object at position.
			 * 	If size is equal to the vector capacity a resize is necessary.
			 * 	A new empty vector is created with double the size of the previous.
			 *	All the elements until position are copied.
			 *	The "val" is added into position.
			 *	The rest of the content after position is copied to the new vector.
			 * 	All old vector is destroyed and deallocated.
			 *	The vector pointers are redirected to the new vector. 
			 */ 

			void insert_aux (iterator position, const value_type& val) {
				if (_size != _capacity) {
					std::uninitialized_copy(position, end() - 1, (position + 1));
					_allocator.construct(&(*position), val);
					_size++;
				}
				else { // No free space
					const size_type old_size = size();
					const size_type len = old_size != 0 ? 2 * old_size : 1; 							// if _size != 0 double it
					pointer new_start = _allocator.allocate(len); 
					pointer new_finish = new_start;
					try {
						new_finish = std::uninitialized_copy(begin(), position, new_start); // copy from start of old vec to position
						_allocator.construct(new_finish, val); 															// add new value to position in the new vec
						++new_finish;
						new_finish = std::uninitialized_copy(position, end(), new_finish);	// copy the rest of the old vector after position
					}
					catch(...) {																													// If an error occurrs destroy the new allocated vector
						for (pointer i = new_finish; i != new_start; i--) {
							_allocator.destroy(i);
						}
						_allocator.deallocate(new_start, len);
						throw;
					}
					for (pointer i = _data; i != _size; i++)
						_allocator.destroy(i); 					// Destroy old vector data 
					int n = _capacity - _data;
					_allocator.deallocate(_data, n);	//	Deallocate old vector data 
					_data = new_start;								//	Redirect pointers to new vector		
					_size = new_finish;
					_capacity = _data + len;
				}
			}
//
//			// range
//			template <class InputIterator>
//			void insert (iterator position, InputIterator first, InputIterator last);
			
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
		if (lhs.size() != rhs.size())
			return false;
		for(size_t i = 0; i < lhs.size(); i++) {
				if (lhs[i] != rhs[i])
					return false;
			}
			return true;
	}

	template <class T, class Alloc> 
	bool operator != (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
		return !(lhs	==	rhs); }
	
	// lexicographical_compare compares the elements sequentially (checking both a<b and b<a)
	template <class T, class Alloc> 
	bool operator <	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class T, class Alloc> 
	bool operator <=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return !(lhs > rhs); }

	template <class T, class Alloc> 
	bool operator >	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return rhs < lhs; }

	template <class T, class Alloc> 
	bool operator >=	(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { 
		return !(lhs < rhs); }
}

#endif

// Resources: 
//	Accelerated C++ Practical Programming by Example - Andrew Koenig, Barbara E. Moo
//	https://djvu.online/file/rh2C1FgVK0ODE
// 	11.3.3 Assignment is not initialization (bookmark)
