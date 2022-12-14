#ifndef _TEST_VECTOR_
#define _TEST_VECTOR_
	
#include "../inc/vector.hpp"

void vector_assign() {
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	first.assign(7,100);

	ft::vector<int>::iterator it;
	it = first.begin()+1;

	second.assign (it, first.end()-1);

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints+3);

	std::cout << "Size of first: "  << int (first.size())		<< '\n';
	std::cout << "Size of second: " << int (second.size())	<< '\n';
	std::cout << "Size of third: "	<< int (third.size())		<< '\n';
}

void vector_at() {
	ft::vector<int> myvector (10);
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;
	std::cout << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		std::cout << ' ' << myvector.at(i);
	std::cout << '\n';
}

void vector_swap() {
	ft::vector<int> foo (3,100);
	ft::vector<int> bar (5,200);
	foo.swap(bar);
	std::cout << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		std::cout << ' ' << foo[i];
	std::cout << '\n';
	std::cout << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		std::cout << ' ' << bar[i];
	std::cout << '\n';
}

void vector_erase() {
	ft::vector<int> myvector;
	for (int i = 1; i <= 10; i++) myvector.push_back(i);
	myvector.erase(myvector.begin()+5);
	myvector.erase(myvector.begin(), myvector.begin()+3);
	for (unsigned i = 0; i < myvector.size(); ++i)
		std::cout << ' ' << myvector[i];
	std::cout << '\n';
}

void vector_reserve() {
	ft::vector<int>::size_type sz;
	
	ft::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);
	std::cout << "making bar grow:\n";
	for (int i = 0; i < 100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
}

void vector_reverse_iterator() {
	ft::vector<int> myvector;
	for (int i=0; i<10; i++) myvector.push_back(i);
	typedef ft::vector<int>::iterator iter_type;
	iter_type from (myvector.begin());
	iter_type until (myvector.end());
	ft::reverse_iterator<iter_type> rev_until (from);
	ft::reverse_iterator<iter_type> rev_from	(until);
	std::cout << "reverse iterator vector:";
	while (rev_from != rev_until)
		std::cout << ' ' << *rev_from++;
	std::cout << '\n';
}

void vector_begin_end() {
	ft::vector<int> myvector;
	for (int i = 1; i <= 5; i++) myvector.push_back(i);
	std::cout << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void vector_assignment() {
	ft::vector<int> foo (3,0);
	ft::vector<int> bar (5,0);
	bar = foo;
	foo = ft::vector<int>();
	std::cout << "Size of foo: " << int(foo.size()) << '\n';
	std::cout << "Size of bar: " << int(bar.size()) << '\n';
}

void construct_vector() { // cplusplus.com/reference/vector/vector/vector/
	ft::vector<int> first; 																// empty vector of ints
	ft::vector<int> second (4,100);												// four ints with value 100
	ft::vector<int> third (second.begin(), second.end()); // iterating through second
	ft::vector<int> fourth (third); 											// a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16, 2, 77, 29};
	ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int));
	std::cout << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
}

void test_vector() {
	ft::vector<int> vec;
	vec.push_back(0);
	while (!vec.empty()) {
		std::cout << "c" << vec.capacity() << ' ';
		std::cout << "s" << vec.size() << ' ';
		vec.insert(vec.begin(), 1);
		std::cout << "c" << vec.capacity() << ' ';
		std::cout << "s" << vec.size() << ' ';
		vec.push_back(2);
		std::cout << "c" << vec.capacity() << ' ';
		std::cout << "s" << vec.size() << ' ';
		vec.push_back(3);
		std::cout << "c" << vec.capacity() << ' ';
		std::cout << "s" << vec.size() << ' ';
		vec.push_back(4);
		std::cout << "c" << vec.capacity() << ' ';
		std::cout << "s" << vec.size() << ' ';
		std::cout << "[" << *(vec.end() - 1) << "]" << ' '; // last element pushed (3)

		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		vec.pop_back();
		std::cout << std::endl;
	}
}

#endif