#pragma once
#include <iostream>

template <class T>
class LinkedQueue
{
	struct QueueNode
	{
		T data;
		QueueNode* next;

		QueueNode(const T data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	QueueNode* head;
	QueueNode* tail;


	void free();
	void copyFrom(const LinkedQueue& other);
	bool empty() const;

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>&);
	LinkedQueue(LinkedQueue<T>&&);
	~LinkedQueue();

	LinkedQueue<T>& operator=(const LinkedQueue&);
	LinkedQueue<T>& operator=(LinkedQueue&&);

	void push(const T);
	void pop();
	T front() const;
};

template <class T>
void LinkedQueue<T>::free()
{
	QueueNode* iter = head;
	while (iter != nullptr)
	{
		QueueNode* prev = iter;
		iter = iter->next;
		delete prev;
	}
	head = tail = nullptr;
}

template <class T>
void LinkedQueue<T>::copyFrom(const LinkedQueue<T>& other)
{
	QueueNode* iter = other.head;

	while (iter != nullptr)
	{
		push(iter.data);
		iter = iter->next;
	}
}

template<class T>
bool LinkedQueue<T>::empty() const
{
	return (head == tail && tail == nullptr);
}

template <class T>
LinkedQueue<T>::LinkedQueue()
{
	head = nullptr;
	tail = nullptr;
}

template <class T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
	copyFrom(other);
}

template <class T>
LinkedQueue<T>::LinkedQueue(LinkedQueue<T>&& other)
{
	head = other.head;
	tail = other.tail;

	other.head = nullptr;
	other.tail = nullptr;
}

template <class T>
LinkedQueue<T>::~LinkedQueue()
{
	free();
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
LinkedQueue<T>& LinkedQueue<T>::operator=(LinkedQueue<T>&& other)
{
	if (this != &other)
	{
		head = other.head;
		tail = other.tail;

		other.head = nullptr;
		other.tail = nullptr;
	}
	return *this;
}

template <class T>
void LinkedQueue<T>::push(const T el)
{
	if (empty())
	{
		tail = new QueueNode(el);
		head = tail;
		tail = tail->next;
	}
	else
	{
		tail = new QueueNode(el);
		tail = tail->next;
	}

}

template <class T>
void LinkedQueue<T>::pop()
{
	if (empty())
		throw std::runtime_error("Can not pop empty queue!");
	else if (head == tail)
	{
		delete head;

		head = nullptr;
		tail = nullptr;
	}
	
	else
	{
		QueueNode nextOne = head->next;
		delete head;
		head = nextOne;
	}
}

template <class T>
T LinkedQueue<T>::front() const
{
	if (empty())
		throw std::runtime_error("Can not get an element from an empty queue!");
	else
		return head->data;
}

