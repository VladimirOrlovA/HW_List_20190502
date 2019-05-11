#pragma once
#include<iostream>
using namespace std;

template <class T>
struct elem {
	T obj;
	elem<T>*next;
	elem<T>*prev;
};


template <class T>
class list_ {
	elem<T> *head;
	elem<T> *tail;
	size_t size_;
public:
	list_();
	void push_back(const T& obj);
	void push_front(const T& obj);
	void pop_back();
	void pop_front();
	void insert(size_t pos, const T& obj);
	void removeAt(size_t pos);
	size_t size() const;
	const T& getElement(size_t pos)const;
	//
	list_(const list_<T>& right);
	list_(list_<T>&& right);
	list_<T>& operator=(const list_<T>& right);
	list_<T>& operator=(list_<T>&& right);
	T& operator[](size_t pos) const;
	~list_();

	template<class T>
	friend ostream& operator<<(ostream&os, list_<T>& lst);
};



template<class T>
inline list_<T>::list_()
{
	head = tail = nullptr;
	size_ = 0;
}

template<class T>
inline void list_<T>::push_back(const T & obj)
{
	elem<T> *n = new elem<T>;
	n->obj = obj;
	n->next = nullptr;
	n->prev = this->tail;
	if (tail == nullptr)
		tail = head = n;
	else {
		tail->next = n;
		tail = n;
	}
	size_++;
}

template<class T>
inline void list_<T>::push_front(const T & obj)
{
	elem<T> *n = new elem<T>;
	n->obj = obj;
	n->next = this->head;
	n->prev = nullptr;
	if (head == nullptr)
		head = tail = n;
	else
	{
		head->prev = n;
		head = n;
	}
	size_++;
}

template<class T>
inline void list_<T>::pop_back()
{
	if (this->size_ == 0)
		return;
	if (this->head == this->tail)
	{
		delete this->head;
		this->head = this->tail = nullptr;
		this->size_ = 0;
		return;
	}
	this->tail = this->tail->prev;
	delete this->tail->next;
	this->tail->next = nullptr;
	this->size_--;
}

template<class T>
inline void list_<T>::pop_front()
{
	if (size_ == 0)
		return;
	if (this->head == this->tail)
	{
		this->head = this->tail = nullptr;
		this->size_ = 0;
		return;
	}
	elem<T> *tmp = head;
	head = head->next;
	head->prev = nullptr;
	delete tmp;
	this->size_--;
}

template<class T>
inline void list_<T>::insert(size_t pos, const T & obj)
{
	if (pos > size_)
		return;
	if (pos == size_)
	{
		push_back(obj);
		return;
	}
	if (pos == 0)
	{
		push_front(obj);
		return;
	}
	elem<T> *flag;
	elem<T> *nElem = new elem<T>;
	nElem->obj = obj;
	if (pos < size_ / 2)
	{
		flag = head;
		for (size_t i = 0; i < pos - 1; i++)
		{
			flag = flag->next;
		}

	}
	else
	{
		flag = tail;
		for (size_t i = size_ - 1; i > pos - 1; i--)
		{
			flag = flag->prev;
		}
	}
	nElem->next = flag->next;
	nElem->next->prev = nElem;
	flag->next = nElem;
	nElem->prev = flag;
	size_++;
}

template<class T>
inline void list_<T>::removeAt(size_t pos)
{
	if (pos < 0 || pos >= size_) {
		cout << "Error - Position out of range\n";
		return;
	}

	if (pos == 0) {
		pop_front();
		return;
	}

	if (pos == size_ - 1) {
		pop_back();
		return;
	}

	elem<T> *curElem;
	if (pos < size_ / 2) {
		curElem = head;
		for (size_t i = 0; i < pos; i++)
			curElem = curElem->next;
	}
	else {
		curElem = tail;
		for (size_t i = size_ - 1; i > pos; i--)
			curElem = curElem->prev;
	}
	curElem->prev->next = curElem->next;
	curElem->next->prev = curElem->prev;
	delete[] curElem;
	size_--;
}

template<class T>
inline size_t list_<T>::size() const
{
	return size_;
}


template<class T>
inline const T & list_<T>::getElement(size_t pos) const
{
	if (pos < 0 || pos >= this->size_)
		cout << "no" << endl;
	else {
		if (pos == 0)
			return this->head->obj;

		elem<T> *tmp = head;
		for (size_t i = 0; i < pos; i++)
		{
			tmp = tmp->next;
		}
		return tmp->obj;
	}
}

template<class T>
inline list_<T>::list_(const list_<T>& right)
{
	size_ = right.size_;
	if (right.head == nullptr) {
		head = tail = nullptr;
		size_ = 0;
		return;
	}
	head = right.head;
	tail = right.tail;
	elem<T> *curElem = head;
	elem<T> *curElemRight = right.head;
	for (size_t i = 0; i < size_ - 1; i++)
	{
		curElem->obj = curElemRight->obj;
		curElem->next = curElemRight->next;
		curElem->prev = curElemRight->prev;

		curElem = curElem->next;
		curElemRight = curElemRight->next;
	}
}

template<class T>
inline list_<T>::list_(list_<T>&& right)
{
	head = nullptr;
	size_ = 0;
	swap(head, right.head);
	swap(tail, right.tail);
	swap(size_, right.size_);
}

template<class T>
inline list_<T>& list_<T>::operator=(const list_<T>& right)
{
	if (this == &right)
		return *this;
	this->~list_();
	size_ = right.size_;
	if (right.head == nullptr) {
		head = tail = nullptr;
		return *this;
	}
	head = right.head;
	tail = right.tail;
	elem<T> *curElem = head;
	elem<T> *curElemRight = right.head;
	for (size_t i = 0; i < right.size_-1; i++)
	{
		curElem->obj = curElemRight->obj;
		curElem->next = curElemRight->next;
		curElem->prev = curElemRight->prev;

		curElem = curElem->next;
		curElemRight = curElemRight->next;
	}
	return *this;
}

template<class T>
inline list_<T>& list_<T>::operator=(list_<T>&& right)
{
	this->~list_();
	swap(this->head, right.head);
	swap(this->head, right.tail);
	swap(this->size_, right.size_);
	return *this;
}

template<class T>
inline T& list_<T>::operator[](const size_t pos) const
{
	if (pos < 0 || pos >= size_)
	{
		cout << "Error - Position out of range";
		return head->obj;
	}

	size_t counter = 0;

	if (pos < size_ / 2) {
		elem<T> *curElem = head;
		while (curElem->next != nullptr)
		{
			if (pos == counter)
				return curElem->obj;
			curElem = curElem->next;
			counter++;
		}
	}
	else
	{
		counter = size_;
		elem<T> *curElem = tail;
		while (curElem->prev != nullptr)
		{
			counter--;
			if (pos == counter)
				return curElem->obj;
			curElem = curElem->prev;
		}
	}
}


template<class T>
inline list_<T>::~list_()
{
	while (size_)
		pop_front();
}

template<class T>
ostream& operator<<(ostream&os, list_<T>& lst)
{
	for (size_t i = 0; i < lst.size_; i++)
	{
		os << lst[i] << " ";
	}
	os << "\n\n";

	return os;
}