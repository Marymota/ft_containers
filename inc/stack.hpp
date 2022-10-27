#ifndef _STACK_HPP_
#define _STACK_HPP_
#include <vector>

namespace ft {

	template< class T, class Container = std::vector<T> >
	class stack {
		public:
//											Member type									Definition
			typedef 					Container										container_type;
			typedef typename	Container::value_type				value_type;
			typedef typename	Container::size_type				size_type;
			typedef typename	Container::reference				reference;
			typedef	typename	Container::const_reference	const_reference;
			
		protected:
			Container c;

		public:
			// 	Container c must be initialized:
			//	explicit stack (const container_type& ctnr = container_type()) : c(ctnr){}
			explicit stack(const Container& = Container()){} // c does not need to be initialized ?

			void 							emplace() const { return c.emplace_back(); }
			bool 							empty() const { return c.empty(); }
			void							pop() { return c.pop_back(); }
			void 							push(const value_type& val) { return c.push_back(); }
			size_type 				size() const { return c.size();	}
			value_type& 			top() { return c.back();	}
			const value_type& top() const { return c.back()}
	};
}

#endif