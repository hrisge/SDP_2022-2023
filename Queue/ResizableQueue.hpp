#pragma once
#include <iostream>

const size_t INITIAL_CAPACITY = 4;

template <class T>
class ResizableQueue
{
	T* data;
	size_t capacity;
	size_t head;
	size_t tail;

	void free();
	void copyFrom(const ResizableQueue<T>&);
	 
	bool full() const;
	bool empty() const;
	void resize();

public:
	ResizableQueue();
	ResizableQueue(const ResizableQueue<T>&);
	ResizableQueue(ResizableQueue<T>&&);
	~ResizableQueue();

	ResizableQueue<T>& operator=(const ResizableQueue<T>&);
	ResizableQueue<T>& operator=(ResizableQueue<T>&&);

	void push(const T&);
	void pop();
	T front() const;
};

template <class T>
void ResizableQueue<T>::free()
{
	delete[] data;
	capacity = 0;
	head = 0;
	tail = 0;
}

template <typename T>
void ResizableQueue<T>::copyFrom(const ResizableQueue<T>& other)
{
	data = new T[other.capacity];
	for (size_t i = 0; i < tail; ++i)
		data[i] = other.data[i];

	capacity = other.capacity;
	head = other.head;
	tail = other.tail;
}

template <class T>
bool ResizableQueue<T>::full() const
{
	return tail == capacity;
}

template <class T>
bool ResizableQueue<T>::empty() const
{
	return head == tail;
}

template <class T>
void ResizableQueue<T>::resize()
{
	T* buff = new T[capacity * 2];
	for (size_t i = 0; i < capacity; ++i)
		buff[i] = data[i];

	delete[] data;
	data = buff;
	capacity *= 2;
}

template <class T>
ResizableQueue<T>::ResizableQueue()
{
	data = new T[INITIAL_CAPACITY];
	capacity = INITIAL_CAPACITY;
	head = 0;
	tail = 0;
}

template<class T>
ResizableQueue<T>::ResizableQueue(const ResizableQueue<T>& other)
{
	copyFrom(other);
}

template <class T>
ResizableQueue<T>::ResizableQueue(ResizableQueue<T>&& other)
{
	data = other.data;
	capacity = other.capacity;
	head = other.head;
	tail = other.tail;

	other.data = nullptr;
	other.capacity = 0;
	other.head = 0;
	other.tail = 0;
}

template <class T>
ResizableQueue<T>::~ResizableQueue()
{
	free();
}

template <class T>
ResizableQueue<T>& ResizableQueue<T>::operator=(const ResizableQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
ResizableQueue<T>& ResizableQueue<T>::operator=(ResizableQueue<T>&& other)
{
	if (this != &other)
	{
		data = other.data;
		capacity = other.capacity;
		head = other.head;
		tail = other.tail;

		other.data = nullptr;
		other.capacity = 0;
		other.head = 0;
		other.tail = 0;
	}
	return *this;
}

template <class T>
void ResizableQueue<T>::push(const T& el)
{
	if (full())
		resize();

	data[tail++] = el;
}

template<class T>
void ResizableQueue<T>::pop()
{
	if (empty())
		throw std::runtime_error("Can not pop from an empty queue");
	head++;
}

template <class T>
T ResizableQueue<T>::front() const
{
	return data[head];
}