#pragma once
#include <iostream>

template <class T>
class LinkedStack
{
	struct Node
	{
		T data;
		Node* next;

		Node(const T& data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	Node* head;

	void free();
	void copyFrom(const LinkedStack&);
	bool empty() const;

public:
	LinkedStack();
	LinkedStack(const LinkedStack&);
	LinkedStack(LinkedStack&&);
	~LinkedStack();

	LinkedStack<T>& operator=(const LinkedStack&);
	LinkedStack<T>& operator=(LinkedStack&&);

	void push(const T&);
	void pop();
	T top() const;
};

template <class T>
void LinkedStack<T>::free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* temp = iter;
		iter = iter->next;
		delete temp;
	}
}

template <class T>
void LinkedStack<T>::copyFrom(const LinkedStack& other)
{
	head = nullptr;
	if (other.empty())
		return;

	Node* iterOther = other.head;
	
	head = new Node(iterOther->data);
	Node* iterThis = head;
	
	while (iterOther != nullptr)
	{
		iterOther = iterOther->next;
		if (iterOther != nullptr)
		{
			iterThis = new Node(iterOther->data);
			iterThis = iterThis->next;
		}
	}
}

template <class T>
bool LinkedStack<T>::empty() const
{
	return head == nullptr;
}

template <class T>
LinkedStack<T>::LinkedStack()
{
	head = nullptr;
}

template <class T>
LinkedStack<T>::LinkedStack(const LinkedStack& other)
{
	copyFrom(other);
}

template <class T>
LinkedStack<T>::LinkedStack(LinkedStack&& other)
{
	head = other.head;
	other.head = nullptr;
}

template <class T>
LinkedStack<T>::~LinkedStack()
{
	free();
}

template <class T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
LinkedStack<T>& LinkedStack<T>::operator=(LinkedStack&& other)
{
	if (this != &other)
	{
		free();
		head = other.head;
		other.head = nullptr;
	}
	return *this;
}

template <class T>
void LinkedStack<T>::push(const T& data)
{
	Node* buff = new Node(data);
	if (empty())
		head = buff;
	else
	{
		buff->next = head;
		head = buff;
	}
}

template <class T>
void LinkedStack<T>::pop()
{
	if (empty())
		throw std::runtime_error("You can not delete the top element of an empty stack!");
	else if (head->next == nullptr)
	{
		T el = head->data;
		delete head;
		head = nullptr;
	}
	else
	{
		T el = head->data;
		Node* buff = head->next;
		delete head;
		head = buff;
	}
}

template <class T>
T LinkedStack<T>::top() const
{
	if (empty())
		throw std::runtime_error("You can not get the top element of an empty stack!");
	else
		return head->data;
}