#pragma once

template<class T>
class Node
{
private:
	T key;
	T value;
	Node<T> *left;
	Node<T> *right;
	int height;
public:
	Node();
	Node(const T & k, const T & val);

	void setKey(const T&);
	void setValue(const T&);
	void setHeight(int h) { height = h; }
	T getKey() const;
	T getValue() const;
	int getHeight() const { return height; }
	void setLeft(Node<T> *);
	void setRight(Node<T> *);
	Node<T> * getLeft() const;
	Node<T> * getRight() const;
};

template <class T>
Node<T>::Node()
	: left(nullptr), right(nullptr), height(1)
{
}

template <class T>
Node<T>::Node(const T & k, const T & val)
	: key(k), value(val), left(nullptr), right(nullptr), height(1)
{
}

template <class T>
void Node<T>::setKey(const T & k) {
	key = k;
}

template <class T>
void Node<T>::setValue(const T & val) {
	value = val;
}

template <class T>
T Node<T>::getKey() const {
	return key;
}

template <class T>
T Node<T>::getValue() const {
	return value;
}

template <class T>
void Node<T>::setLeft(Node<T> * ptr) {
	left = ptr;
}

template <class T>
void Node<T>::setRight(Node<T> * ptr) {
	right = ptr;
}

template <class T>
Node<T> * Node<T>::getLeft() const {
	return left;
}

template <class T>
Node<T> * Node<T>::getRight() const {
	return right;
}

