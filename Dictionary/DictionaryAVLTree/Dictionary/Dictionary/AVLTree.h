#pragma once

#include "Node.h"
//#include "stdafx.h"
#include <iostream>

using namespace std;

//template<class T>
//T max(T a, T b) {
//	return (a > b) ? a : b;
//}

template<class T>
class AVLTree
{
private:
	Node<T> *root;
	int getHeight(Node<T> *r) {
		if (r == nullptr) return 0;
		return r->getHeight();
	}
	Node<T> * rightRotate(Node<T> *y);
	Node<T> * leftRotate(Node<T> *x);
	int getBalance(Node<T> *r);
	Node<T> * insertHelper(Node<T> *r, const T &k, const T &val, bool &flag);
	Node<T> * leftMostLeaf(Node<T> *r);
	Node<T> * removeHelper(Node<T> *r, const T &k, bool &flag);
	void clearHelper(Node<T> *r);
	Node<T> * copyTree(Node<T> *ar);
	void preorder(Node<T> * r) const;
	void inorder(Node<T> * r) const;
public:
	AVLTree();
	~AVLTree();
	bool insert(const T & k, const T & val);
	bool remove(const T & k);
	T search(const T & k) const;
	void clear();
	void preorderTravesal() const;
	void inorderTravesal() const;

	AVLTree<T> & operator = (const AVLTree<T> &);
};

//#include "AVLTree.cpp"

template<class T>
Node<T> * AVLTree<T>::rightRotate(Node<T> *y) {
	Node<T> *x = y->getLeft();
	Node<T> *T2 = x->getRight();

	x->setRight(y);
	y->setLeft(T2);

	y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);
	x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);

	return x;
}

template<class T>
Node<T> * AVLTree<T>::leftRotate(Node<T> *x) {
	Node<T> *y = x->getRight();
	Node<T> *T2 = y->getLeft();

	y->setLeft(x);
	x->setRight(T2);

	x->setHeight(max(getHeight(x->getLeft()), getHeight(x->getRight())) + 1);
	y->setHeight(max(getHeight(y->getLeft()), getHeight(y->getRight())) + 1);

	return y;
}

template<class T>
int AVLTree<T>::getBalance(Node<T> *r) {
	if (r == nullptr) {
		return 0;
	}
	return getHeight(r->getLeft()) - getHeight(r->getRight());
}

template<class T>
Node<T> * AVLTree<T>::insertHelper(Node<T> *r, const T &k, const T &val, bool &flag) {
	if (r == nullptr) {
		flag = true;
		return new Node<T>(k, val);
	}
	if (k < r->getKey()) {
		r->setLeft(insertHelper(r->getLeft(), k, val, flag));
	}
	else if (k > r->getKey()) {
		r->setRight(insertHelper(r->getRight(), k, val, flag));
	}
	else {
		return r;
	}

	r->setHeight(max(getHeight(r->getLeft()), getHeight(r->getRight())) + 1);

	int balance = getBalance(r);

	//Left left
	if (balance > 1 && k < r->getLeft()->getKey()) {
		return rightRotate(r);
	}
	//Right right
	if (balance < -1 && k > r->getRight()->getKey()) {
		return leftRotate(r);
	}
	//Left right
	if (balance > 1 && k > r->getLeft()->getKey()) {
		r->setLeft(leftRotate(r->getLeft()));
		return rightRotate(r);
	}
	//Right left
	if (balance < -1 && k < r->getRight()->getKey()) {
		r->setRight(rightRotate(r->getRight()));
		return leftRotate(r);
	}

	return r;
}

template<class T>
bool AVLTree<T>::insert(const T &k, const T &val) {
	bool flag = false;
	root = insertHelper(root, k, val, flag);
	return flag;
}

template<class T>
void AVLTree<T>::clearHelper(Node<T> *r) {
	if (r) {
		clearHelper(r->getLeft());
		clearHelper(r->getRight());
		delete r;
	}
}

template<class T>
void AVLTree<T>::clear() {
	clearHelper(root);
	root = nullptr;
}

template<class T>
AVLTree<T>::AVLTree() {
	root = nullptr;
}

template<class T>
AVLTree<T>::~AVLTree() {
	clear();
}

template<class T>
Node<T> *AVLTree<T>::copyTree(Node<T> *ar) {
	if (ar == nullptr) {
		return ar;
	}
	Node<T> *temp = new Node<T>(ar->getKey(), ar->getValue());
	temp->setLeft(copyTree(ar->getLeft()));
	temp->setRight(copyTree(ar->getRight()));
	return temp;
}

template<class T>
AVLTree<T> & AVLTree<T>::operator=(const AVLTree<T> &rhs) {
	if (this != &rhs) {
		if (root)
			clear();
		root = copyTree(rhs.root);
	}
	return *this;
}

template <class T>
void AVLTree<T>::preorder(Node<T> * r) const {
	if (r) {
		cout << r->getKey() << "  " << r->getValue() << "\n";
		preorder(r->getLeft());
		preorder(r->getRight());
	}
}

template <class T>
void AVLTree<T>::preorderTravesal() const {
	preorder(root);
	std::cout << std::endl;
}

template <class T>
void AVLTree<T>::inorder(Node<T> * r) const {
	if (r) {
		inorder(r->getLeft());
		cout << r->getKey() << "  " << r->getValue() << "\n";
		inorder(r->getRight());
	}
}

template <class T>
void AVLTree<T>::inorderTravesal() const {
	inorder(root);
	std::cout << std::endl;
}

template<class T>
Node<T> * AVLTree<T>::leftMostLeaf(Node<T> *r) {
	Node<T> *current = r;
	while (current->getLeft() != nullptr)
	{
		current = current->getLeft();
	}
	return current;
}

template<class T>
Node<T> * AVLTree<T>::removeHelper(Node<T> *r, const T &k, bool &flag) {
	//Step 1: perform standard BST delete
	if (r == nullptr) {
		return r;
	}
	if (k < r->getKey()) {
		r->setLeft(removeHelper(r->getLeft(), k, flag));
	}
	else if (k > r->getKey()) {
		r->setRight(removeHelper(r->getRight(), k, flag));
	}
	else {
		flag = true;
		if (r->getLeft() == nullptr || r->getRight() == nullptr) {
			Node<T> *temp = r->getLeft() ? r->getLeft() : r->getRight();
			if (temp == nullptr) {
				temp = r;
				r = nullptr;
			}
			else {
				*r = *temp;
			}
			delete temp;
		}
		else {
			Node<T> *temp = leftMostLeaf(r->getRight());
			r->setKey(temp->getKey());
			r->setValue(temp->getValue());
			r->setRight(removeHelper(r->getRight(), temp->getKey(), flag));
		}
	}
	if (r == nullptr) {
		return r;
	}

	//Step 2: update height of the current node
	r->setHeight(max(getHeight(r->getLeft()), getHeight(r->getRight())) + 1);

	//Step 3: balance
	int balance = getBalance(r);
	//Left left
	if (balance > 1 && getBalance(r->getLeft()) >= 0) {
		return rightRotate(r);
	}
	//Left right
	if (balance > 1 && getBalance(r->getLeft()) < 0) {
		r->setLeft(leftRotate(r->getLeft()));
		return rightRotate(r);
	}
	//Right right
	if (balance < -1 && getBalance(r->getRight()) <= 0) {
		return leftRotate(r);
	}
	//Right left
	if (balance < -1 && getBalance(r->getRight()) > 0) {
		r->setRight(rightRotate(r->getRight()));
		return leftRotate(r);
	}

	return r;
}

template<class T>
bool AVLTree<T>::remove(const T &k) {
	bool flag = false;
	root = removeHelper(root, k, flag);
	return flag;
}

template <class T>
T AVLTree<T>::search(const T & k) const {
	Node<T> * p = root;
	while (p) {
		if (p->getKey() == k)
			return p->getValue();
		else
			if (p->getKey() < k)
				p = p->getRight();
			else
				p = p->getLeft();
	}
	T res;
	return res;
}
