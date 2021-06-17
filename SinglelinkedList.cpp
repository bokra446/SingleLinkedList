#include "SingleLinkedlist.h"
#include <algorithm>

LinkedList::Node::Node(const ValueType& value, Node* next) {
	_value = value;
	_next = next;
}

LinkedList::Node::~Node() {
	_value = 0;
}

void LinkedList::Node::insertNext(const ValueType& value) {
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

void LinkedList::Node::removeNext() {
	if (_next == nullptr)
	{}
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

LinkedList::ListIterator::ListIterator() : _ptr(nullptr){}

LinkedList::ListIterator::ListIterator(pointer pData) : _ptr(pData) {}

ValueType& LinkedList::ListIterator::operator*() {
	return _ptr->_value;
}

bool LinkedList::ListIterator::operator==(const ListIterator& other) const {
	if (_ptr == other._ptr) {
		return 1;
	}
	else {
		return 0;
	}
}

bool LinkedList::ListIterator::operator!=(const ListIterator& other) const {
	return !(*this == other);
}

LinkedList::ListIterator& LinkedList::ListIterator::operator++() {
	this->_ptr = this->_ptr->_next;
	return *this;
}

LinkedList::ListIterator LinkedList::ListIterator::operator++(int) {
	ListIterator temp = *this;
	this->_ptr = this->_ptr->_next;
	return temp;
}

LinkedList::ListIterator LinkedList::begin() {
	return ListIterator(_head);
}

LinkedList::ListIterator LinkedList::end() {
	return ListIterator(nullptr);
}

LinkedList::LinkedList() {
	_size = 0;
	_head = nullptr;
}

LinkedList::LinkedList(const LinkedList& copyList) {
	_size = copyList._size;
	_head = new Node(copyList._head->_value, copyList._head->_next);
	Node* temp = copyList._head->_next;
	while (temp->_next != nullptr) {
		temp = new Node(temp->_value, temp->_next);
		temp = temp->_next;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& copyList) {
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

LinkedList::LinkedList(LinkedList&& moveList) noexcept {
		_size = moveList._size;
		_head = moveList._head;
		moveList._head = nullptr;
		moveList._size = 0;
}
LinkedList& LinkedList::operator=(LinkedList&& moveList) noexcept {
	if (this != &moveList) {
		clear();
		_size = moveList._size;
		_head = moveList._head;
		moveList._head = nullptr;
		moveList._size = 0;
	}
	return *this;
}

LinkedList::~LinkedList() {
	this->clear();
}

const ValueType& LinkedList::operator[](const size_t pos) const {
	Node* current = getNode(pos);
	return current->_value;
}
ValueType& LinkedList::operator[](const size_t pos) {
	Node* current = getNode(pos);
	return current->_value;
}

LinkedList::Node* LinkedList::getNode(const size_t pos) const {
	Node* current = _head;
	for (int i = 0; i < pos; ++i) {
		if (current->_next != nullptr) {
			current = current->_next;
		}
	}
	return current;
}

void LinkedList::insert(const size_t pos, const ValueType& value) {
	Node* current;
	if (!pos) {
		current = getNode(pos);
	}
	else {
		current = getNode(pos - 1);
	}
	std::cout << current->_value << std::endl;
	current->insertNext(value);
	++_size;
}

void LinkedList::pushBack(const ValueType& value) {
	insert(_size, value);
}

void LinkedList::pushFront(const ValueType& value) {
	Node* newHead = new Node(value);
	Node* current = _head;
	_head = newHead;
	_head->_next = current;
	++_size;
	
}

void LinkedList::popFront() {
	Node* current = _head->_next;
	delete _head;
	_head = current;
	--_size;
}


void LinkedList::remove(const size_t pos) {
	Node* current = getNode(pos);
	current->removeNext();
	--_size;
}
void LinkedList::removeNextNode(Node* node) {
	Node* current = findNode(node->_value);
	current->removeNext();
	--_size;
}
void LinkedList::removeFront(){
	popFront();
}
void LinkedList::removeBack() {
	Node* current = getNode((_size - 1));
	delete current->_next;
	current->_next = nullptr;
	--_size;
}

long long int LinkedList::findIndex(const ValueType& value) const {
	size_t idx = 0;
	Node* current = _head;
	while (current->_value != value) {
		current = current->_next;
		++idx;
	}
	return idx;
}

LinkedList::Node* LinkedList::findNode(const ValueType& value) const {
	Node* current = _head;
	while (current->_value != value) {
		current = current->_next;
	}
	return current;
}

void LinkedList::reverse() {
	Node* prevCurrent = nullptr;
	Node* nextCurrent = _head->_next;
	Node* current = _head;
	Node* endNode = current;
	for (size_t i = 0; i < _size; ++i) {
		std::swap(prevCurrent, current->_next);
		prevCurrent = current;
		current = nextCurrent;
		nextCurrent = current->_next;
	}
	_head = current;
}

LinkedList LinkedList::reverse() const {
	LinkedList newList = *this;
	newList.reverse();
	return newList;
}
LinkedList LinkedList::getReverseList() const {
	LinkedList newList = *this;
	newList.reverse();
	return newList;
}

size_t LinkedList::size() const
{
	return _size;
}

void LinkedList::forceNodeDelete(Node* node)
{
	if (node == nullptr) {
		return;
	}

	Node* nextDeleteNode = node->_next;
	delete node;
	forceNodeDelete(nextDeleteNode);
}

void LinkedList::clear() {
	while (_size) {
		popFront();
		--_size;
	}
}

std::ostream& operator<<(std::ostream& o, LinkedList& list) {
	LinkedList::Node* current = list._head;
	for (int i = 0; i < list._size; ++i) {
		o << current->_value << " ";
		current = current->_next;
	}
	o << ": size - " << list._size << std::endl;
	return o;
}