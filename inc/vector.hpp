#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_
#include <memory>
#include <cstddef> // for ptrdiff_t
#include <iterator> // substitute later 

/**
 * @brief Vectors are sequence containers representing arrays that can change in size
*/
namespace ft {

	template <class T, class Alloc = std::allocator<T> > // generic template
	class vector {
		public:
//											Definition														Member type
			typedef						T																			value_type;
			typedef						Alloc																	allocator_type;
			typedef typename	Alloc::reference 											reference;
			typedef typename	Alloc::const_reference 								const_reference;
			typedef typename	Alloc::pointer												pointer;
			typedef typename	Alloc::const_pointer									const_pointer;
			typedef typename	std::random_access_iterator_tag				iterator;
			typedef typename	std::random_access_iterator_tag				const_iterator;
			typedef typename 	std::reverse_iterator<iterator>				reverse_iterator;
			typedef typename	std::reverse_iterator<const iterator>	const_reverse_iterator;
			typedef 					ptrdiff_t															difference_type;
			typedef 					size_t																size_type;

		private:
			allocator_type	_allocator;	//	Allocator object
			pointer					_first;
			size_type				_size;			//	Initial container size(number of elements)


		public:
			// Empty container constructor (default)
			explicit
			vector (const allocator_type& alloc = allocator_type()) :
				_allocator(alloc),
				_first(0),
				_size(0) {}

			// fill constructor 
			explicit
			vector (size_t n, const value_type& val = value_type(), 
							const allocator_type& alloc= allocator_type()) :
				_allocator(alloc),
				_first(0),
				_size(n)	{
				}

			// range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
							const allocator_type& alloc = allocator_type()) :
								_allocator(alloc),
								_first(first),
								_size((int)(last - first))
			{}

			// copy constructor
			vector (const vector& x) {}

			~vector() {}
			vector& operator= (const vector& x) {}

			iterator begin() {
				return iterator(_first);
			};
			iterator end() {
				return iterator(_first + _size);
			};
	};
}

#endif