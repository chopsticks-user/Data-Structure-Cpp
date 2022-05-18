#pragma once
#include <iostream>
#include <memory>
template<typename T> class List
{
private:
	template<typename T> struct Node
	{
		T _data;
		std::shared_ptr<Node<T>> _next;
		explicit Node<T>() :_data{ 0 }, _next{ nullptr } { }
		explicit Node<T>(const T& rh_value) : _data{ rh_value }, _next{ nullptr }{ }
	};
	std::shared_ptr<Node<T>> _head;
public:
	List<T>();
	List<T>(const List<T>&);
	List<T>(const int&, const T&);

	template<typename T> friend std::ostream& operator << (std::ostream& os, const List<T>&);
	//template<typename T> friend std::istream& operator >> (std::istream& is, const List<T>&);

	const T& operator [] (const int&);

	const List<T>& operator = (const List<T>&);

	const bool& operator == (const List<T>&);

	const bool& operator != (const List<T>&);

	const List<T>& push_back(const T&);
	const List<T>& push_back(const List<T>&);

	const List<T>& push_front(const T&);
	const List<T>& push_front(const List<T>&);

	const List<T>& pop_back();

	const List<T>& pop_front();

	const List<T>& insert(const int&, const T&);
	const List<T>& insert(const int&, const List<T>&);

	const List<T>& remove(const T&);

	const List<T>& clear();

	List<T> inverse();

	int size();
	template<typename T> friend const int& size_of(const List<T>&);
};
