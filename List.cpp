#include "List.h"


template<typename T>
inline List<T>::List() //default constructor
{
	this->_head = nullptr;
}

template<typename T>
inline List<T>::List(const List<T>& rh_list) //copy constructor
{
	//if the right-hand list is empty, return an empty list
	if (!rh_list._head)
		return;

	//initialize this->head
	this->_head = std::make_shared<Node<T>>();

	//copy the right-hand list->head
	auto copy_node = rh_list._head;

	//get data of the right-hand list's first node
	this->_head->_data = copy_node->_data;

	//travel through the copy list and use the push back function
	//to copy data to the list
	//ignore the fisrt node since it was copied
	copy_node = copy_node->_next;
	while (copy_node)
	{
		this->push_back(copy_node->_data);
		copy_node = copy_node->_next;
	}
}

template<typename T>
List<T>::List(const int& length, const T& value_of_each)   //initialize a list with length and a default value of each element
{
	if (length > 0)	
		for (int i = 0; i < length; i++)
			this->push_back(value_of_each);
}

template<typename T>
inline std::ostream& operator<<(std::ostream& os, const List<T>& output_list)
{
	//start at the beginning of the list
	auto temp_node = output_list._head;
	os << "[";

	//the reason for this loop condition is because I want to stop at the node
	//right before the last node so that I do not wnat to print an additional 
	//comma at the end
	while (temp_node->_next->_next)
	{
		os << temp_node->_data << ", ";
		temp_node = temp_node->_next;
	}
	os << temp_node->_next->_data << "]";
	return os;
}

/*template<typename T>
inline std::istream& operator>>(std::istream& is, const List<T>& input_list)
{
	return is;
}*/

template<typename T>
inline const T& List<T>::operator[](const int& pos)
{
	auto temp_node = this->_head;
	for (int i = 0; i < pos; i++)
		temp_node = temp_node->_next;
	return temp_node->_data;
}

template<typename T>
const List<T>& List<T>::operator=(const List<T>& rh_list)
{
	this->clear();
	if (!rh_list._head)
		return *this;
	this->_head = std::make_shared<Node<T>>();
	auto copy_node = rh_list._head;
	this->_head->_data = copy_node->_data;
	copy_node = copy_node->_next;
	while (copy_node)
	{
		this->push_back(copy_node->_data);
		copy_node = copy_node->_next;
	}
	return *this;
}

template<typename T>
const bool& List<T>::operator==(const List<T>& rh_list)
{
	if (this->size() != size_of(rh_list))
		return false;
	auto temp_node = this->_head;
	auto temp_rh_node = rh_list._head;
	while (temp_node and temp_rh_node)
	{
		if (temp_node->_data != temp_rh_node->_data)
			return false;
		temp_node = temp_node->_next;
		temp_rh_node = temp_rh_node->_next;
	}
	return true;
}

template<typename T>
const bool& List<T>::operator!=(const List<T>& rh_list)
{
	return !(*this == rh_list);
}

template<typename T>
const List<T>& List<T>::push_back(const T& rh_value)
{
	auto copy_node = std::make_shared<Node<T>>(rh_value);
	if (!this->_head)
	{
		this->_head = copy_node;
		return *this;
	}
	auto temp_node = this->_head;
	while (temp_node->_next)
	{
		temp_node = temp_node->_next;
	}
	temp_node->_next = copy_node;
	return *this;
}

template<typename T>
const List<T>& List<T>::push_back(const List<T>& rh_list)
{
	auto copy_list = rh_list;
	auto temp_node = this->_head;
	while (temp_node->_next)
	{
		temp_node = temp_node->_next;
	}
	temp_node->_next = std::move(copy_list._head);
	return *this;
}

template<typename T>
const List<T>& List<T>::push_front(const T& rh_value)
{
	auto copy_node = std::make_shared<Node<T>>(rh_value);
	if (this->_head)
		copy_node->_next = std::move(this->_head);
	this->_head = std::move(copy_node);
	return *this;
}

template<typename T>
const List<T>& List<T>::push_front(const List<T>& rh_list)
{
	auto copy_list = rh_list;
	auto temp_node = copy_list._head;
	while (temp_node->_next)
	{
		temp_node = temp_node->_next;
	}
	temp_node->_next = this->_head;
	this->_head = std::move(copy_list._head);
	return *this;
}

template<typename T>
const List<T>& List<T>::pop_back()
{
	auto temp_node = this->_head;
	while (temp_node->_next->_next)
		temp_node = temp_node->_next;
	temp_node->_next = nullptr;
	return *this;
}

template<typename T>
const List<T>& List<T>::pop_front()
{
	auto temp_node = this->_head;
	this->_head = temp_node->_next;
	return *this;
}

template<typename T>
const List<T>& List<T>::insert(const int& pos, const T& rh_value)
{
	if (!pos)
	{
		this->push_front(rh_value);
		return *this;
	}
	if (pos == this->size() - 1)
	{
		this->push_back(rh_value);
		return *this;
	}
	auto insert_node = std::make_shared<Node<T>>(rh_value);
	auto temp_node = this->_head;
	for (int i = 0; i < pos - 1; i++)
		temp_node = temp_node->_next;
	insert_node->_next = std::move(temp_node->_next);
	temp_node->_next = std::move(insert_node);
	return *this;
}

template<typename T>
const List<T>& List<T>::insert(const int& pos, const List<T>& rh_list)
{
	if (!pos)
	{
		this->push_front(rh_list);
		return *this;
	}
	if (pos == this->size() - 1)
	{
		this->push_back(rh_list);
		return *this;
	}
	auto temp_node = this->_head;
	for (int i = 0; i < pos - 1; i++)
		temp_node = temp_node->_next;
	auto copy_list = rh_list;
	auto insert_tail = copy_list._head;
	while (insert_tail->_next)
		insert_tail = insert_tail->_next;
	insert_tail->_next = std::move(temp_node->_next);
	temp_node->_next = std::move(copy_list._head);
	return *this;
}

template<typename T>
const List<T>& List<T>::remove(const T& pos)
{
	if (!pos)
	{
		this->pop_front();
		return *this;
	}
	if (pos == this->size() - 1)
	{
		this->pop_back();
		return *this;
	}
	auto temp_node = this->_head;
	for (int i = 0; i < pos - 1; i++)
		temp_node = temp_node->_next;
	auto temp1 = temp_node->_next;
	temp_node->_next = std::move(temp_node->_next->_next);
	return *this;
}

template<typename T>
const List<T>& List<T>::clear()
{
	while (this->_head)
	{
		auto temp_node = this->_head;
		this->_head = this->_head->_next;
		temp_node.reset();
	}
	return *this;
}

template<typename T>
List<T> List<T>::inverse()
{
	List<T> inversed_list;
	auto temp_node = this->_head;
	while (temp_node)
	{
		inversed_list.push_front(temp_node->_data);
		temp_node = temp_node->_next;
	}
	return inversed_list;
}

template<typename T>
int List<T>::size()
{
	if (!this->_head)
		return 0;
	int s = 0;
	auto temp_node = this->_head;
	while (temp_node)
	{
		temp_node = temp_node->_next;
		s++;
	}
	return s;
}

template<typename T>
const int& size_of(const List<T>& rh_list)
{
	if (!rh_list._head)
		return 0;
	int s = 0;
	auto temp_node = rh_list._head;
	while (temp_node)
	{
		temp_node = temp_node->_next;
		s++;
	}
	return s;
}
