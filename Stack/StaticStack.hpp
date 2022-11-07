#pragma once
#include <iostream>

const unsigned MAX_SIZE = 2048;

template <typename T>
class StaticStack
{
	T stack[MAX_SIZE];
	int topIndex;

public:
	StaticStack();

	bool empty() const;
	bool full() const;
	void push(const T&);
	void pop();
	T top() const;
};

template <typename T>
StaticStack<T>::StaticStack()
{
	topIndex = -1;
}

template <typename T>
bool StaticStack<T>::empty() const
{
	return topIndex == -1;
}

template <typename T>
bool StaticStack<T>::full() const
{
	return topIndex == MAX_SIZE - 1;
}

template <typename T>
void StaticStack<T>::push(const T& elem)
{
	if (full())
		throw std::runtime_error("Stack_is_full");
		
	stack[++topIndex] = elem;
}

template <typename T>
void StaticStack<T>::pop()
{
	if (empty()) 
		throw std::runtime_error("You can not delete the top element of an empty stack!");
	--topIndex;
}

template <typename T>
T StaticStack<T>::top() const
{
	if (empty()) 
		throw std::runtime_error("You can not get the top element of an empty stack!");

	return stack[topIndex];
}
