#pragma once
#include <iostream>

const size_t MAX_SIZE = 4;

template <class T>
class StaticQueue
{
	T data[MAX_SIZE];
	size_t head;
	size_t tail;
	size_t numberOfElements;

public:
	StaticQueue();

	void push(const T&);
	void pop();
	T front() const;

	bool empty() const;
	bool full() const;

	void print();
};

template <class T>
void StaticQueue<T>::print()
{
	while (!empty())
	{
		std::cout << front() << "   ";
		pop();
	}
}

template <class T>
StaticQueue<T>::StaticQueue()
{
	head = 0;
	tail = 0;
	numberOfElements = 0;
}

template <class T>
void StaticQueue<T>::push(const T& el)
{
	if (full())
		throw std::runtime_error("Queue is full can not add more elements");
	else if (tail == MAX_SIZE)
	{
		tail = 0;
		data[tail++] = el;
		++numberOfElements;
	}
	else
	{
		data[tail++] = el;
		++numberOfElements;
	}

}

template <class T>
void StaticQueue<T>::pop()
{
	if (empty())
		throw std::runtime_error("Can not pop out from an empty Queue");
	else if(head == MAX_SIZE)
	{
		head = 0;
		--numberOfElements;
	}
	else
	{
		++head;
		--numberOfElements;
	}
}

template <class T>
T StaticQueue<T>::front() const
{
	if (empty())
		throw std::runtime_error("Queue is empty can not get element!");
	else
		return data[head];
}

template <class T>
bool StaticQueue<T>::empty() const
{
	return numberOfElements==0;
}

template <class T>
bool StaticQueue<T>::full() const
{
	return numberOfElements == MAX_SIZE;
}