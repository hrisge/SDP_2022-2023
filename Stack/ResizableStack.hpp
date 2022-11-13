#pragma once
#include <iostream>

template <typename T>
class ResizableStack
{
	unsigned capacity;
	int topIndex;
	T* stack;

	void free();
	void copyFrom(const ResizableStack&);
	void resize();
	bool full() const;
	bool empty() const;

public:
	ResizableStack();
	ResizableStack(const ResizableStack&);
	ResizableStack(ResizableStack&&);
	~ResizableStack();

	ResizableStack<T>& operator=(const ResizableStack&);
	ResizableStack<T>& operator=(ResizableStack&&);

	void push(const T&);
	void pop();
	T top() const;
};

template <typename T>
void ResizableStack<T>::free()
{
	capacity = 0;
	topIndex = -1;
	delete[] stack;
}

template <typename T>
void ResizableStack<T>::copyFrom(const ResizableStack& other)
{
	capacity = other.capacity;
	stack = new T[capacity];
	for (unsigned i = 0; i < other.topIndex(); ++i)
		stack[i] = other.stack[i];
	topIndex = other.topIndex;
}

template <typename T>
void ResizableStack<T>::resize()
{
	capacity *= 2;
	T* buff = new T[capacity];

	for (size_t i = 0; i < topIndex; ++i)
		buff[i] = stack[i];

	delete[] stack;
	stack = buff;
}

template<typename T>
bool ResizableStack<T>::full() const
{
	return topIndex == capacity - 1;
}

template<typename T>
bool ResizableStack<T>::empty() const
{
	return topIndex == -1;
}

template <typename T>
ResizableStack<T>::ResizableStack()
{
	capacity = 16;
	topIndex = -1;
	stack = new T[capacity];
}

template <typename T>
ResizableStack<T>::ResizableStack(const ResizableStack& other)
{
	copyFrom(other);
}

template <typename T>
ResizableStack<T>::ResizableStack(ResizableStack&& other)
{
	capacity = other.capacity;
	topIndex = other.topIndex;
	stack = other.stack;

	other.capacity = 0;
	other.topIndex = -1;
	other.stack = nullptr;
}

template<typename T>
ResizableStack<T>::~ResizableStack()
{
	free();
}

template <typename T>
ResizableStack<T>& ResizableStack<T>::operator=(const ResizableStack& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
ResizableStack<T>& ResizableStack<T>::operator=(ResizableStack&& other)
{
	if (this != &other)
	{
		capacity = other.capacity;
		topIndex = other.topIndex;
		stack = other.stack;

		other.capacity = 0;
		other.topIndex = -1;
		other.stack = nullptr;
	}
	return *this;
}

template<typename T>
void ResizableStack<T>::push(const T& elem)
{
	if (full())
		resize();
	stack[++topIndex] = elem;
}

template<typename T>
void ResizableStack<T>::pop()
{
	if(empty())
		throw std::runtime_error("You can not delete the top element of an empty stack!");
	topIndex--;
}

template<typename T>
T ResizableStack<T>::top() const
{
	if(empty())
		throw std::runtime_error("You can not get the top element of an empty stack!");
	return stack[topIndex];
}

