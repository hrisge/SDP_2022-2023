#pragma once
#include <iostream>

template <class T>
class DoublyLinkedList
{
public:
	struct DoublyLinkedListNode
	{
		T data;
		DoublyLinkedListNode* next;
		DoublyLinkedListNode* prev;

		DoublyLinkedListNode(const T& el, DoublyLinkedListNode* n = nullptr, DoublyLinkedListNode* p = nullptr) : data {el} , next {n}, prev {p} {}
	};

	using DLL = DoublyLinkedList;
	using DLLN = DoublyLinkedListNode;

private:

	DoublyLinkedListNode* head;
	DoublyLinkedListNode* tail;

	void copyFrom(const DoublyLinkedList<T>&);
	void free();


public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>&);
	DoublyLinkedList(DoublyLinkedList<T>&&);
	~DoublyLinkedList();

	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>&);
	DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&&);

	void pushBack(const T&);
	void pushFront(const T&);
	void popBack();
	void popFront();
	bool empty() const;
	const T& front() const;
	const T& back() const;
	void print() const;
};

template <class T>
void DoublyLinkedList<T>::print() const
{
	DoublyLinkedListNode* iter = head;
	while (iter)
	{
		std::cout << iter->data << " -> ";
		iter = iter->next;
	}
}

template <class T>
const T& DoublyLinkedList<T>::back() const
{
	if (empty())
		throw std::runtime_error("List is empty!");

	return tail->data;
}

template <class T>
const T& DoublyLinkedList<T>::front() const
{
	if (empty())
		throw std::runtime_error("List is empty!");

	return head->data;
}

template <class T>
bool DoublyLinkedList<T>::empty() const
{
	return head == nullptr;
}

template <class T>
void DoublyLinkedList<T>::popBack()
{
	if (empty())
		throw std::runtime_error("List is empty!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		tail->prev->next = nullptr;

		DoublyLinkedListNode* toDelete = tail;
		tail = tail->prev;
		delete toDelete;
	}
}

template <class T>
void DoublyLinkedList<T>::popFront()
{
	if (empty())
		throw std::runtime_error("List is empty!");

	if (head == tail)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		head->next->prev = nullptr;

		DoublyLinkedListNode* toDelete = head;
		head = head->next;
		delete toDelete;
	}
}

template <class T>
void DoublyLinkedList<T>::pushBack(const T& el)
{
	DoublyLinkedListNode* toPush = new DoublyLinkedListNode(el);

	if (empty())
		head = tail = toPush;

	else
	{
		toPush->prev = tail;
		tail->next = toPush;
		tail = toPush;
	}
}

template <class T>
void DoublyLinkedList<T>::pushFront(const T& el)
{
	DoublyLinkedListNode* toPush = new DoublyLinkedListNode(el);

	if (empty())
		head = tail = toPush;
	else
	{
		toPush->next = head;
		head->prev = toPush;
		head = toPush;
	}
}

template <class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other)
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
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	free();
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other)
{
	head = other.head;
	tail = other.tail;

	other.head = nullptr;
	other.tail = nullptr;
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	copyFrom(other);
}

template <class T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList& other)
{
	DoublyLinkedListNode* iter = other.head;
	while (iter)
	{
		pushBack(iter->data);
		iter = iter->next;
	}
}

template <class T>
void DoublyLinkedList<T>::free()
{
	DoublyLinkedListNode* iter = head;

	while (iter)
	{
		DoublyLinkedListNode* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}

	head = tail = nullptr;
}

template <class T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	head = nullptr;
	tail = nullptr;
}
