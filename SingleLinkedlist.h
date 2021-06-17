#pragma once
#include <cstddef>
#include<iterator>
#include <iostream>
#include <algorithm>

// потом поменяем на шаблоны

template <typename T>
class LinkedList
{
	using ValueType = T;
	// класс узла списка
	// по своей сути, может содержать любые данные,
	// можно реализовать и ассоциативный массив, просто добавив 
	// поле с ключем в узел и, с учетом этого, поменять методы LinkedList 
	// (доступ по ключу, поиск по ключу и т.д.)
	struct Node {
		Node(const ValueType& value, Node* next = nullptr) {
			_value = value;
			_next = next;
		}
		~Node() {
			_value = 0;
		}

		void insertNext(const ValueType& value) {
			LinkedList::Node* newNode = new Node(value, nullptr);
			if (this->_next == nullptr) {
				_next = newNode;
			}
			else {
				Node* nextNode = _next;
				_next = newNode;
				newNode->_next = nextNode;
			}
		}
		void removeNext() {
			if (_next == nullptr)
			{
			}
			else {
				if (_next->_next == nullptr) {
					delete _next;
				}
				else {
					Node* nextNode = _next->_next;
					delete _next;
					_next = nextNode;
				}
			}
		}

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

		ListIterator() : _ptr(nullptr) {}
		ListIterator(pointer pData) : _ptr(pData) {}

		ValueType& operator*() {
			return _ptr->_value;
		}

		bool operator==(const ListIterator& other) const {
			if (_ptr == other._ptr) {
				return 1;
			}
			else {
				return 0;
			}
		}
		bool operator!=(const ListIterator& other) const {
			return !(*this == other);
		}
		ListIterator& operator++() {
			this->_ptr = this->_ptr->_next;
			return *this;
		}
		ListIterator operator++(int) {
			ListIterator temp = *this;
			this->_ptr = this->_ptr->_next;
			return temp;
		}
	private:
		pointer _ptr;
	};
	ListIterator begin() {
		return ListIterator(_head);
	}
	ListIterator end() {
		return ListIterator(nullptr);
	}
	////
	LinkedList() {
		_size = 0;
		_head = nullptr;
	}
	LinkedList(const LinkedList& copyList) {
		_size = copyList._size;
		_head = new Node(copyList._head->_value, copyList._head->_next);
		Node* temp = copyList._head->_next;
		while (temp->_next != nullptr) {
			temp = new Node(temp->_value, temp->_next);
			temp = temp->_next;
		}
	}
	LinkedList& operator=(const LinkedList& copyList) {
		if (this != &copyList) {
			clear();
			_size = copyList._size;
			_head = new Node(copyList._head->_value, copyList._head->_next);
			Node* temp = copyList._head->_next;
			while (temp->_next != nullptr) {
				temp = new Node(temp->_value, temp->_next);
				temp = temp->_next;
			}
		}
		return *this;
	}

	LinkedList(LinkedList&& moveList) noexcept {
		_size = moveList._size;
		_head = moveList._head;
		moveList._head = nullptr;
		moveList._size = 0;
	}
	LinkedList& operator=(LinkedList&& moveList) noexcept {
		if (this != &moveList) {
			clear();
			_size = moveList._size;
			_head = moveList._head;
			moveList._head = nullptr;
			moveList._size = 0;
		}
		return *this;
	}

	~LinkedList() {
		this->clear();
	}
	////

	// доступ к значению элемента по индексу
	const ValueType& operator[](const size_t pos) const {
		Node* current = getNode(pos);
		return current->_value;
	}
	ValueType& operator[](const size_t pos) {
		Node* current = getNode(pos);
		return current->_value;
	}
	// доступ к узлу по индексу
	Node* getNode(const size_t pos) const {
		Node* current = _head;
		for (int i = 0; i < pos; ++i) {
			if (current->_next != nullptr) {
				current = current->_next;
			}
		}
		return current;
	}

	// вставка элемента по индексу, сначала ищем, куда вставлять (О(n)), потом вставляем (O(1))
	void insert(const size_t pos, const ValueType& value) {
		Node* current;
		if (!pos) {
			current = getNode(pos);
		}
		else {
			current = getNode(pos - 1);
		}
		if (_head == nullptr) {
			_head = new Node(value, nullptr);
		}
		else {
			current->insertNext(value);
		}
		++_size;
	}
	//
	void pushBack(const ValueType& value) {
		insert(_size, value);
	}
	// вставка в начало (О(1))
	void pushFront(const ValueType& value) {
		Node* newHead = new Node(value);
		Node* current = _head;
		_head = newHead;
		_head->_next = current;
		++_size;

	}

	void popFront() {
		Node* current = _head->_next;
		delete _head;
		_head = current;
		--_size;
	}


	// удаление
	void remove(const size_t pos) {
		Node* current = getNode(pos);
		current->removeNext();
		--_size;
	}
	void removeNextNode(Node* node) {
		Node* current = findNode(node->_value);
		current->removeNext();
		--_size;
	}
	void removeFront() {
		popFront();
	}
	void removeBack() {
		Node* current = getNode((_size - 1));
		delete current->_next;
		current->_next = nullptr;
		--_size;
	}

	// поиск, О(n)
	long long int findIndex(const ValueType& value) const {
		size_t idx = 0;
		Node* current = _head;
		while (current->_value != value) {
			current = current->_next;
			++idx;
		}
		return idx;
	}
	Node* findNode(const ValueType& value) const {
		Node* current = _head;
		while (current->_value != value) {
			current = current->_next;
		}
		return current;
	}

	// разворот списка
	// изменение текущего списка
	void reverse() {
		Node* nextCurrent = _head->_next;
		Node* current = _head;
		Node* endNode = getNode(_size - 1);
		_head->_next = nullptr;
		for (size_t i = 0; i < _size - 1; ++i) {
			current->_next = endNode->_next;;
			endNode->_next = current;
			current = nextCurrent;
			nextCurrent = current->_next;
		}
		_head = endNode;
	}

	// получение нового списка (для константных объектов)
	LinkedList reverse() const {
		LinkedList newList = *this;
		newList.reverse();
		return newList;
	}
	// чтобы неконстантный объект тоже мог возвращать новый развернутый список
	LinkedList getReverseList() const {
		LinkedList newList = *this;
		newList.reverse();
		return newList;
	}

	size_t size() const {
		return _size;
	}

	void clear() {
		while (_size) {
			popFront();
		}
	}

	friend std::ostream& operator<<(std::ostream& o, LinkedList& list) {
		LinkedList::Node* current = list._head;
		for (int i = 0; i < list._size; ++i) {
			o << current->_value << " ";
			current = current->_next;
		}
		o << ": size - " << list._size << std::endl;
		return o;
	}
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node) {
		if (node == nullptr) {
			return;
		}

		Node* nextDeleteNode = node->_next;
		delete node;
		forceNodeDelete(nextDeleteNode);
	}
};