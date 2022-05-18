#pragma once
#include <iostream>
#include <memory>
#include "List.h"

template<typename T> class BST
{
protected:
	template<typename T> struct Node
	{
		T _data;
		std::shared_ptr<Node<T>> left;
		std::shared_ptr<Node<T>> right;
		explicit Node<T>() :_data{ 0 }, left{ nullptr }, right{ nullptr } { }
		explicit Node<T>(const T& rh_value) :_data{ rh_value }, left { nullptr }, right{ nullptr } { }
	};
	std::shared_ptr<Node<T>> root;
	const BST<T>& balance();
public:
	explicit BST<T>();
	explicit BST<T>(const BST<T>&);

	template<typename T> friend std::ostream& operator << (std::ostream&, const BST<T>&);

	const BST<T>& add(const T&);
	const BST<T>& add(const List<T>&);
	const BST<T>& add(const BST<T>&);
	const BST<T>& remove_once(const T&);
	const BST<T>& remove_all(const T&);
	const BST<T>& clear();
	const bool& search(const T&);
	const int& count(const T&);
};
