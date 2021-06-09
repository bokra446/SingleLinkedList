#pragma once
#include <cstddef>
#include<iterator>

// ����� �������� �� �������
using ValueType = int;

class LinkedList
{
	// ����� ���� ������
	// �� ����� ����, ����� ��������� ����� ������,
	// ����� ����������� � ������������� ������, ������ ������� 
	// ���� � ������ � ���� �, � ������ �����, �������� ������ LinkedList 
	// (������ �� �����, ����� �� ����� � �.�.)
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

	// ������ � �������� �������� �� �������
	const ValueType& operator[](const size_t pos) const;
	ValueType& operator[](const size_t pos);
	// ������ � ���� �� �������
	Node* getNode(const size_t pos) const;

	// ������� �������� �� �������, ������� ����, ���� ��������� (�(n)), ����� ��������� (O(1))
	void insert(const size_t pos, const ValueType& value);
	//
	void pushBack(const ValueType& value);
	// ������� � ������ (�(1))
	void pushFront(const ValueType& value);

	void popFront();


	// ��������
	void remove(const size_t pos);
	void removeNextNode(Node* node);
	void removeFront();
	void removeBack();

	// �����, �(n)
	long long int findIndex(const ValueType& value) const;
	Node* findNode(const ValueType& value) const;

	// �������� ������
	void reverse();						// ��������� �������� ������
	LinkedList reverse() const;			// �������� ������ ������ (��� ����������� ��������)
	LinkedList getReverseList() const;	// ����� ������������� ������ ���� ��� ���������� ����� ����������� ������

	size_t size() const;

	void clear();
private:
	Node*	_head;
	size_t	_size;

	void forceNodeDelete(Node* node);
};