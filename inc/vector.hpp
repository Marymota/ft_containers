#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <iostream>
#include <memory>		// add allocator<T>
#include <cstddef> 	// add ptrdiff_t
#include "reverse_iterator.hpp"
#include "random_access_iterator.hpp"
#include "type_traits.hpp"
#include "iterator_traits.hpp"
#include "memory.hpp"
#include "iterator.hpp"

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

									 /*----------*/
									/**	VECTOR: */
								 /*----------*/

namespace ft {
	//	Vector class template - container definition
	template < class T, class Alloc = std::allocator<T> > // generic template
	class vector {														

		public:
		
	 /*----------------*/
	/**	MEMBER:TYPES: */
 /*----------------*/

	//	Definition																									Member type				notes
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
			pointer 				_finish;						//	Last element in the vector 
			pointer					_capacity;				//	Las allocated piece of memory

		public:

	  /**-------------------*/
	 /** MEMBER:FUNCTIONS: */
	/*--------------------*/

	/***	(constructor)
	 * 		Construct vector	***/

			// DEFAULT CONSTRUCTOR
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
				_allocator(alloc),
				_data(),
				_finish(),
				_capacity()
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
				_finish = _data;
				_capacity = _data + n;

				for(; n > 0; --n, _finish++) {
					_allocator.construct(_finish, val);
				}
			}
			
			// RANGE CONSTRUCTOR
			/** @brief Given the distance between first and last as N,
			 *		if first and last are both forward, bidirectional or random-access iterators,
			 * 			the copy constructor of T is only called N times, and
			 * 			no reallocation occurs.
			 * 		otherwise (first and last are just input iterators),
			 * 			the copy constructor of T is called O(N) times, and
			 * 			reallocation occurs O(log N) times.
			 * 
			 *	This constructor has the same effect as:
			 *	vector(static_cast<size_type>(first), static_cast<value_type>(last), a)
			 *	if Input_Iterator is an integral type
			 */

			template <typename InputIterator>								
			vector(	InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
							typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL) :
				_allocator(alloc),
				_data(0),
				_finish(0),
				_capacity(0)
			{
				const size_type n = std::distance(first, last);
				_data = _allocator.allocate(n);
				_finish = _data;
				_capacity = _data + n;

				for(; first != last; ++first, _finish++)
					_allocator.construct(_finish, *first);
			}

			/** COPY CONSTRUCTOR
			 *	@details
			 * 	Memory is allocated equal to the capacity of the original vector
			 *	Elements of the original vector are copied to the new allocated space
			 */ 
			vector (const vector& other) {
				_data = _allocator.allocate(other.capacity());
				_finish = ft::uninitialized_copy(other.begin(), other.end(), _data);
				_capacity = _finish;
			}

/***	(destructor)
 * 		Vector destructor	***/
			~vector() {
				size_type save_finish = size();
				/** @why: pointer i != _finish don't work */
				for (size_type i = 0; i < save_finish; i++){ 
					_finish--;
				}
				if (_capacity)
					_allocator.deallocate(_data, capacity()); //	void deallocate (pointer p, size_type n);
			}

/***	operator=
 * 		Assign content	***/
			vector& operator= (const vector& other) {
				_data = other._data;
				_finish = ft::uninitialized_copy(other.begin(), other.end(), _data);
				_capacity = _finish;
				return *this;
			}

/** @assign:	Assigns new contents to the vector replacing its current contents
 *						and modifying its size accordingly. 
 */
		// Replaces the contents with 'count' copies of value 'value'
		void assign( size_type count, const value_type& value) {
			while(!empty())
				pop_back();
			reserve(count);
 			while(count--)
				push_back(value);
		}

		template< class InputIterator > 
		void assign( InputIterator first, InputIterator last,
		typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
		{
			while(!empty())
				pop_back();
			reserve(std::distance(first, last));
 			while (last != first)
				push_back(*last--);
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
		
	/** ITERATORS:	***/

			iterator begin(){ 											return _data ;} 	
			const_iterator begin() const{						return _data ;}						
			iterator end(){													return _finish ;}									
			const_iterator end() const{							return _finish ;}						
			reverse_iterator rbegin(){							return reverse_iterator(end()) ;}	 				// end() of _finish? is it different?			
			const_reverse_iterator rbegin() const{ 	return const_reverse_iterator(end()) ;}	
			reverse_iterator rend(){								return reverse_iterator(begin());}			
			const_reverse_iterator rend() const{		return const_reverse_iterator(begin()) ;}


	/** CAPACITY: */

			bool empty() const { 					return (begin() == end()); } 						//checks whether the container is empty
			size_type size() const {			return size_type(end() - begin()); } 		// returns the n of elements
			size_type max_size() const { 	return size_type(-1) / sizeof(T); }			// returns the max possible n of elems 
			
			void reserve(size_type new_cap) { 																		// reservers storage if capacity is less than new_cap
				if (capacity() < new_cap) {
					pointer new_data = _allocator.allocate(new_cap); 
					pointer new_finish = new_data;
					try {
						new_finish = ft::uninitialized_copy(begin(), end(), new_data); // copy from start of old vec to position
					}
					catch(...) {																											// If an error occurrs destroy the new allocated vector
						for (pointer i = new_finish; i != new_data; i--) {
							_allocator.destroy(i);
						}
						_allocator.deallocate(new_data, new_cap);
						throw;
					}
					for (pointer i = _data; i != _finish; i++)
						_allocator.destroy(i); 					// Destroy old vector data 
					int n = _capacity - _data;
					_allocator.deallocate(_data, n);	//	Deallocate old vector data 
					_data = new_data;									//	Redirect pointers to new vector		
					_finish = new_finish;
					_capacity = _data + new_cap;
				}
			}
			
			size_type capacity() const { 	return size_type(_capacity - _data); } // returns n of elems that can be held in curr alloc storage


	/** ELEMENT:ACCESS: */

			reference operator[](size_type n) { return *(begin() + n );}
			const_reference operator[](size_type n) const { return *(begin() + n );}
			reference at(size_type pos) {	return *(begin() + pos);}
			const_reference at(size_type pos) const {	return *(begin() + pos);}
			reference front() {	return *(begin()); }
			const_reference front() const {	return *(begin()); }
			reference back() { return *(end() - 1); }
			const_reference back() const { return *(end() - 1); }
			value_type* data() { return begin(); }
			const value_type* data() const { begin(); }
			
	/**	MODIFIERS: */
			

			/*	@push_back: Add element at the end
			 * 	If the storage capacity of the vector is not almost full 
			 *	(-1 from full capacity) a new object (val) is constructed
			 *	after the last element and the number of elements (size)
			 *	is incremented by one.
			 *	If the storage capacity of the vector is almost full its
			 *	necessary to extend the vector.
			 */
			
			void push_back(const value_type& val){
				if (_finish != _capacity) {
					_allocator.construct(_finish, val); //void construct ( pointer p, const_reference val );
					_finish++;
				}
				else
					insert_aux(end(), val);
			}

			// pop_back:			Delete last element
			void pop_back() {
				_allocator.destroy(_data - 1);
				_finish--;
			}

			// single element
			iterator insert (iterator position, const value_type& value) {
				size_type n = position - begin();
				if (_finish != _capacity && position == end())
						push_back(value);
				else
					insert_aux(position, value);
			return begin() + n;
		}

/** @insert_fill: 	*/
			void insert (iterator position, size_type n, const value_type& value)
			{
				if (((size() + n) < capacity()) && position == end()) {
					while (n--)
						push_back(value);
				}
				else if ((size() + n) < capacity()) {
					ft::uninitialized_copy(position, end() - 1, (position + 1));
					while (n--) {
						_allocator.construct(&(*position), value); 		
						_finish++;
					}
				}
				else {
					size_type len = size() + n;
					size_type new_capacity = capacity();
					while (len > new_capacity) {
						new_capacity = len != 0 ? 2 * len : 1;
					}
					pointer new_start = _allocator.allocate(len); 
					pointer new_finish = new_start;
					try {
						new_finish = ft::uninitialized_copy(begin(), position, new_start); // copy from start of old vec to position
						while (n--)
							_allocator.construct(new_finish++, value); 															// add new value to position in the new vec
						new_finish = ft::uninitialized_copy(position, end(), new_finish);	// copy the rest of the old vector after position
					}
					catch(...) {																													// If an error occurrs destroy the new allocated vector
						for (pointer i = new_finish; i != new_start; i--) {
							_allocator.destroy(i);
						}
						_allocator.deallocate(new_start, len);
						throw;
					}
					for (pointer i = _data; i != _finish; i++)
						_allocator.destroy(i); 					// Destroy old vector data 
					int n = _capacity - _data;
					_allocator.deallocate(_data, n);	//	Deallocate old vector data 
					_data = new_start;								//	Redirect pointers to new vector		
					_finish = new_finish;
					_capacity = _data + len;
				}
			}


/** @insert_range:	template <class InputIterator> void insert (iterator position, InputIterator first, InputIterator last); */
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type n = std::distance(first, last);
				if (((size() + n) < capacity()) && position == end()) {
					while (first != last) {
						push_back(*first++);
						_finish++;
					}
				}
				else if ((size() + n) < capacity()) {
					ft::uninitialized_copy(position, end() - 1, first);
					while (first != last) {
						_allocator.construct(&(*position), *first++); 		
						_finish++;
					}
				}
				else {
					size_type len = size() + n;
					size_type new_capacity = capacity();
					while (len > new_capacity) {
						new_capacity = len != 0 ? 2 * len : 1;
					}
					pointer new_start = _allocator.allocate(len); 
					pointer new_finish = new_start;
					try {
						new_finish = ft::uninitialized_copy(begin(), position, new_start); // copy from start of old vec to position
						while (first != last)
							_allocator.construct(new_finish++, *first++);												// add new value to position in the new vec
						new_finish = ft::uninitialized_copy(position, end(), new_finish);	// copy the rest of the old vector after position
					}
					catch(...) {																													// If an error occurrs destroy the new allocated vector
						for (pointer i = new_finish; i != new_start; i--) {
							_allocator.destroy(i);
						}
						_allocator.deallocate(new_start, len);
						throw;
					}
					for (pointer i = _data; i != _finish; i++)
						_allocator.destroy(i); 					// Destroy old vector data 
					int n = _capacity - _data;
					_allocator.deallocate(_data, n);	//	Deallocate old vector data 
					_data = new_start;								//	Redirect pointers to new vector		
					_finish = new_finish;
					_capacity = _data + len;
				}
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
				if (_finish != _capacity) {
					ft::uninitialized_copy(position, end() - 1, (position + 1));
					_allocator.construct(&(*position), val);
					_finish++;
				}
				else { // No free space
					const size_type old_finish = size();
					const size_type len = old_finish != 0 ? 2 * old_finish : 1; 					// if _finish != 0 double it
					pointer new_start = _allocator.allocate(len); 
					pointer new_finish = new_start;
					try {
						new_finish = ft::uninitialized_copy(begin(), position, new_start); // copy from start of old vec to position
						_allocator.construct(new_finish, val); 															// add new value to position in the new vec
						++new_finish;
						new_finish = ft::uninitialized_copy(position, end(), new_finish);	// copy the rest of the old vector after position
					}
					catch(...) {																													// If an error occurrs destroy the new allocated vector
						for (pointer i = new_finish; i != new_start; i--) {
							_allocator.destroy(i);
						}
						_allocator.deallocate(new_start, len);
						throw;
					}
					for (pointer i = _data; i != _finish; i++)
						_allocator.destroy(i); 					// Destroy old vector data 
					int n = _capacity - _data;
					_allocator.deallocate(_data, n);	//	Deallocate old vector data 
					_data = new_start;								//	Redirect pointers to new vector		
					_finish = new_finish;
					_capacity = _data + len;
				}
			}
			
			/** @brief:
			 * If the position given is not the last element of the vector
			 * we copy all the elements from position to the last element
			 * The size (_finish iterator) is reduced and the last element is deleted
			 * Position is returned as the element after the one it was erased
			 */
			iterator erase (iterator position) {
				if (position + 1 != end())
					ft::uninitialized_copy(position + 1, end(), position);
				--_finish;
				_allocator.destroy(_finish);
				return position;
			}

			/** @brief:
			 * The function recieves an iterator to the start and end
			 * of a range of elements to be erased copy all elements between 
			 * (range)last and the last element of the vector starting at 
			 * (range)first the _finish iterator is reduced by the length 
			 * of the range erased then the elements between the (range)first 
			 * and the last element are destroyed, since they were already copied
			 * The last element in the vector is returned
			 */ 
			iterator erase (iterator first, iterator last) {
				ft::uninitialized_copy(last, end(), first);
				_finish = _finish - (last - first);
				while (first != _finish)
					_allocator.destroy(&*first++);
				return first;
			};

			void swap (vector& other) {
				pointer tmp = _data;
				_data = other._data;

				other._data = tmp;
				 tmp = _finish;
				_finish = other._finish;
				other._finish = tmp;

				 tmp = _capacity;
				_capacity = other._capacity;
				other._capacity = tmp;
			}

			// emplace:				Construct and insert element
			// emplace_back		Construct and insert element at the end

	/** ALLOCATOR: ***/

			allocator_type get_allocator() const { return _allocator; }

	/*-----------------------------------*/
 /**	NON:MEMBER:FUNCTION:OVERLOADS:	*/
/*-----------------------------------*/
	/** @_relational_operators: */

			template <class TO, class AllocO> friend bool operator== (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
			template <class TO, class AllocO> friend bool operator!= (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
			template <class TO, class AllocO> friend bool operator<  (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
			template <class TO, class AllocO> friend bool operator<= (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
			template <class TO, class AllocO> friend bool operator>  (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
			template <class TO, class AllocO> friend bool operator>= (const vector<TO,AllocO>& lhs, const vector<TO,AllocO>& rhs);
			
			template< class TO, class AllocO> friend void swap ( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ); 

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

	template< class T, class Alloc> 
	void swap ( ft::vector<T,Alloc>& lhs, ft::vector<T,Alloc>& rhs ){ lhs.swap(rhs); }
};

#endif