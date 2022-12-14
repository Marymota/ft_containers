#ifndef _TEST_VECTOR_HPP_
#define _TEST_VECTOR_HPP_
	
#include "../inc/stack.hpp"

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

#endif