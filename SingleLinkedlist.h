#pragma once
#include <cstddef>
#include<iterator>
#include <iostream>

// потом поменяем на шаблоны
using ValueType = int;

class LinkedList
{
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr);
		~Node();

		void insertNext(const ValueType& value);
		void removeNext();

		ValueType _value;
		Node* _next;
	};

public:
	class ListIterator {
	public:
		using value_type = Node;
		using pointer = Node*;
		using reference = Node&;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::forward_iterator_tag;

		ListIterator();
		ListIterator(pointer pData);

		ValueType& operator*();

		bool operator==(const ListIterator& other) const;
		bool operator!=(const ListIterator& other) const;
		ListIterator& operator++();
		ListIterator operator++(int);
	private:
		pointer _ptr;
	};
	ListIterator begin();
	ListIterator end();
	////
	LinkedList();
	LinkedList(const LinkedList& copyList);
	LinkedList& operator=(const LinkedList& copyList);

	LinkedList(LinkedList&& moveList) noexcept;
	LinkedList& operator=(LinkedList&& moveList) noexcept;

	~LinkedList();
	////

	// доступ к значению элемента по индексу
	const ValueType& operator[](const size_t pos) const;
	ValueType& operator[](const size_t pos);
	// доступ к узлу по индексу
	Node* getNode(const size_t pos) const;

	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value);
	//
	void pushBack(const ValueType& value);
	// вставка в начало (О(1))
	void pushFront(const ValueType& value);

	void popFront();


	// удаление
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	// поиск, О(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// разворот списка
	void reverse();						// изменение текущего списка
	LinkedList reverse() const;			// полчение нового списка (для константных объектов)
	LinkedList getReverseList() const;	// чтобы неконстантный объект тоже мог возвращать новый развернутый список

	size_t size() const;

	void clear();

	friend std::ostream& operator<<(std::ostream& o, LinkedList& list);
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};