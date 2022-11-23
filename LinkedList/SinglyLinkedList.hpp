#pragma once 
#include <iostream>

template <class T>
class SinglyLinkedList 
{
	struct LinkedListNode
	{
		T data;
		LinkedListNode* next;

		LinkedListNode(const T data)
		{
			this->data = data;
			next = nullptr;
		}
	};

	LinkedListNode* head;
	LinkedListNode* tail;

	void copyFrom(const SinglyLinkedList<T>&);
	void free();
	bool empty() const;

public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>&);
	SinglyLinkedList(SinglyLinkedList&&);
	~SinglyLinkedList();

	SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>&);
	SinglyLinkedList<T>& operator=(SinglyLinkedList<T>&&);

	void pushFront(const T&);
	void pushBack(const T&);
	void popFront();
	void popBack();

	void print() const;
};

template <class T>
void SinglyLinkedList<T>::free()
{
	LinkedListNode* iter = head;

	while (iter != nullptr)
	{
		LinkedListNode* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = tail = nullptr;
}

template <class T>
void SinglyLinkedList<T>::copyFrom(const SinglyLinkedList<T>& other)
{
	LinkedListNode* iter = other.head;
	while (iter != nullptr)
	{
		pushBack(iter->data);
		iter = iter->next;
	}
}

template <class T>
bool SinglyLinkedList<T>::empty() const
{
	return (head == nullptr);
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList()
{
	head = nullptr;
	tail = nullptr;
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
	copyFrom(other);
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(SinglyLinkedList<T>&& other)
{
	head = other->head;
	tail = other->tail;

	other->head = nullptr;
	other->tail = nullptr;
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	free();
}

template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(SinglyLinkedList<T>&& other)
{
	if (this != &other)
	{
		free();
		head = other->head;
		tail = other->tail;

		other->head = nullptr;
		other->tail = nullptr;
	}
	return *this;
}

template <class T>
void SinglyLinkedList<T>::pushFront(const T& data)
{
	if (empty())
	{
		this->head = new LinkedListNode(data);
		this->tail = this->head;
		return;
	}
	LinkedListNode* second = this->head;
	this->head = new LinkedListNode(data);
	this->head->next = second;
}

template <class T>
void SinglyLinkedList<T>::pushBack(const T& data)
{
	if (empty())
	{
		this->head = new LinkedListNode(data);
		this->tail = this->head;
		return;
	}

	this->tail->next = new LinkedListNode(data);
	this->tail = this->tail->next;
}

template <class T>
void SinglyLinkedList<T>::popBack()
{
	if (!empty())
	{
		LinkedListNode* iter = head;
		
		if (iter == tail)
		{
			delete iter;
			head = tail = nullptr;
			return;
		}

		while (iter->next != tail && iter->next != nullptr)
			iter = iter->next;

		iter->next = nullptr;
		delete tail;
		tail = iter;
	}
}

template <class T>
void SinglyLinkedList<T>::popFront()
{
	if (!empty())
	{
		LinkedListNode* toRemember = head->next;
		delete head;
		head = toRemember;
		if (head == nullptr) 
			tail = nullptr;
	}
}

template <class T>
void SinglyLinkedList<T>::print() const
{
	LinkedListNode* iter = head;
	while (iter != nullptr)
	{
		std::cout << iter->data << " ";
		if (iter->next != nullptr)
			std::cout << "-> ";
		iter = iter->next;
	}
}