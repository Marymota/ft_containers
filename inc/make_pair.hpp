#ifndef _MAKE_PAIR_HPP_
#define _MAKE_PAIR_HPP_

#include "pair.hpp"

namespace ft {

template <class T1, class T2>
ft::pair<T1, T2> make_pair( T1 t, T2 u ) {
	T1 first(t);
	T2 second(u);
};
}

#endif