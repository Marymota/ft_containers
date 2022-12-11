#include <iostream>
#include <string>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
//	#include <../inc/map.hpp>
	#include "../inc/stack.hpp"
	#include "../inc/vector.hpp"
#endif

// #include <stdlib.h>
// 
// #define MAX_RAM 4294967296
// #define BUFFER_SIZE 4096
// struct Buffer
// {
// 	int idx;
// 	char buff[BUFFER_SIZE];
// };
// 
// 
// #define COUNT (MAX_RAM / (int)sizeof(Buffer))
// 
// template<typename T>
// class MutantStack : public ft::stack<T>
// {
// public:
// 	MutantStack() {}
// 	MutantStack(const MutantStack<T>& src) { *this = src; }
// 	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
// 	{
// 		this->c = rhs.c;
// 		return *this;
// 	}
// 	~MutantStack() {}
// 
// 	typedef typename ft::stack<T>::container_type::iterator iterator;
// 
// 	iterator begin() { return this->c.begin(); }
// 	iterator end() { return this->c.end(); }
// 
// };

// int main(int argc, char** argv) {
// 	if (argc != 2)
// 	{
// 		std::cerr << "Usage: ./test seed" << std::endl;
// 		std::cerr << "Provide a seed please" << std::endl;
// 		std::cerr << "Count value:" << COUNT << std::endl;
// 		return 1;
// 	}
// 	const int seed = atoi(argv[1]);
// 	srand(seed);
// 
// 	ft::vector<std::string> vector_str;
// 	ft::vector<int> vector_int;
// 	ft::stack<int> stack_int;
// 	ft::vector<Buffer> vector_buffer;
// 	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
// 	ft::map<int, int> map_int;
// 
// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		vector_buffer.push_back(Buffer());
// 	}
// 
// 	for (int i = 0; i < COUNT; i++)
// 	{
// 		const int idx = rand() % COUNT;
// 		vector_buffer[idx].idx = 5;
// 	}
// 	ft::vector<Buffer>().swap(vector_buffer);
// 
// 	try
// 	{
// 		for (int i = 0; i < COUNT; i++)
// 		{
// 			const int idx = rand() % COUNT;
// 			vector_buffer.at(idx);
// 			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
// 		}
// 	}
// 	catch(const std::exception& e)
// 	{
// 		//NORMAL ! :P
// 	}
// 	
// 	for (int i = 0; i < COUNT; ++i)
// 	{
// 		map_int.insert(ft::make_pair(rand(), rand()));
// 	}
// 
// 	int sum = 0;
// 	for (int i = 0; i < 10000; i++)
// 	{
// 		int access = rand();
// 		sum += map_int[access];
// 	}
// 	std::cout << "should be constant with the same seed: " << sum << std::endl;
// 
// 	{
// 		ft::map<int, int> copy = map_int;
// 	}
// 	MutantStack<char> iterable_stack;
// 	for (char letter = 'a'; letter <= 'z'; letter++)
// 		iterable_stack.push(letter);
// 	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
// 	{
// 		std::cout << *it;
// 	}
// 	std::cout << std::endl;
// 	return (0);
// }

	void vector_reverse_iterator() {
//		ft::vector<int> myvector;
//		for (int i=0; i<10; i++) myvector.push_back(i);
//
//		typedef ft::vector<int>::iterator iter_type;
//
//		iter_type from (myvector.begin());
//		iter_type until (myvector.end());
//
//		ft::reverse_iterator<iter_type> rev_until (from);
//		ft::reverse_iterator<iter_type> rev_from	(until);
//
//		std::cout << "reverse iterator vector:";
//		while (rev_from != rev_until)
//			std::cout << ' ' << *rev_from++;
//		std::cout << '\n';
			ft::vector<int> myvector (5);

			int i = 0;
			ft::vector<int>::reverse_iterator rit = myvector.rbegin();
			for(; rit != myvector.rend(); ++rit)
				*rit = ++i;
			
			std::cout << "myvector contains:";
			for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
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
		std::cout << "The contents of second are:";
		for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << ' ' << *it;
		}
//		ft::vector<int> third (second.begin(), second.end()); // iterating through second
//		ft::vector<int> fourth (third); 											// a copy of third
// 
//		// the iterator constructor can also be used to construct from arrays:
// 		int myints[] = {16, 2, 77, 29};
// 		ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int));
// 		std::cout << "The contents of fifth are:";
// 		for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
// 			std::cout << ' ' << *it;
 		std::cout << '\n';
}

void stack_operators() {
	ft::stack<int> st;
	// push three elements into the stack
	st.push(1);
	st.push(2);
	st.push(3);

	// copy
	ft::stack<int> st1(st);
	std::cout << st.size() << std::endl;
	std::cout << st1.size() << std::endl;

	if (st == st1)
		std::cout << "Both stacks are equal" << std::endl;
	std::cout << st.size() << std::endl;
	std::cout << st1.size() << std::endl;

	if (st <= st1)
		std::cout << "stack is less or equal than stack1" << std::endl;
	else if (st >= st1)
		std::cout << "stack is more or equal than stack1" << std::endl;

	st1.pop();
	std::cout << st.size() << std::endl;
	std::cout << st1.size() << std::endl;

	if (st <= st1)
		std::cout << "stack is less or equal than stack" << std::endl;
	else if (st >= st1)
		std::cout << "stack is more or equal than stack1" << std::endl;
	
	st1.top() = 5;
	std::cout << st.size() << std::endl;
	std::cout << st1.size() << std::endl;

	if (st <= st1)
		std::cout << "stack is less or equal than stack1" << std::endl;
	else if (st >= st1)
		std::cout << "stack is more or equal than stack1" << std::endl;

	if (st != st1)
		std::cout << "Both stacks are not equal" << std::endl;
	
	std::cout << "Stack: ";
	while (!st.empty()) {
		std::cout << st.top() << ' ';
		st.pop();
	}
	std::cout << std::endl;

	std::cout << "Stack1: ";
	while (!st1.empty()) {
		std::cout << st1.top() << ' ';
		st1.pop();
	}
	std::cout << std::endl;
}

void stack() {
	ft::stack<int> st;

	// push three elements into the stack
	st.push(1);
	st.push(2);
	st.push(3);

	//pop and printtwo elements from the stack
	std::cout << st.top() << ' ';
	st.pop();
	std::cout << st.top() << ' ';
	st.pop();

//	//modify top element
	st.top() = 77;

	//push two new elements
	st.push(4);
	st.push(5);

	//pop one element without processing it
	st.pop() ;

	// pop and print remaining elements
	while (!st.empty()) {
		std::cout << st.top() << ' ';
		st.pop();
	}
	std::cout << std::endl;
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

int main() {
	//	stack(); 	// Print "3 2 4 77"
	//	stack_operators();

	// 	VECTOR
	//	test_vector();
	//	construct_vector();
	//	vector_assignment();
	//	vector_begin_end();
		vector_reverse_iterator();
	return 0;
}

