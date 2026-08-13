#pragma once
#include<iostream>
#include<assert.h>
#include <algorithm>
using namespace std;

namespace button
{
	template<class T>
	struct list_node
	{
		list_node(const T& x = T())
			:_data(x)
			,_next(nullptr)
			,_prev(nullptr)
		{}

		T _data;
		list_node<T>* _next;
		list_node<T>* _prev;
	};

	template<class T, class Ref, class Ptr>
	struct list_iterator
	{
		typedef list_node<T> Node;
		typedef list_iterator<T, Ref, Ptr> Self;

		list_iterator(Node* node)
			:_node(node)
		{}

		Ref operator*()
		{
			return _node->_data;
		}

		Ptr operator->()
		{
			return &_node->_data;
		}

		Self operator++()
		{
			_node = _node->_next;
			return *this;
		}

		Self operator++(int)
		{
			Self cur = _node;
			_node = _node->_next;
			return cur;
		}

		Self operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		Self operator--(int)
		{
			Self cur = _node;
			_node = _node->_prev;
			return cur;
		}

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s) const
		{
			return _node == s._node;
		}

		Node* _node;
	};

	template<class container>
	void print_container(const container& con)
	{
		typename container::const_iterator it = con.begin();

		while (it != con.end())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;
	}


	template<class T>
	class list
	{
	public:
		typedef list_node<T> Node;
		typedef list_iterator<T, T&, T*> iterator;
		typedef list_iterator<T, const T&, const T*> const_iterator;

		iterator begin()
		{
			return _head->_next;
		}

		iterator end()
		{
			return _head;
		}

		const_iterator begin() const
		{
			return _head->_next;
		}

		const_iterator end() const
		{
			return _head;
		}

		void empty_init()
		{
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
			_size = 0;
		}

		list()
		{
			empty_init();
		}

		list(initializer_list<T> il)
		{
			empty_init();
			for (auto& e : il)
			{
				push_back(e);
			}
		}

		list(const list<T>& lt)
		{
			empty_init();
			for (auto& e : lt)
			{
				push_back(e);
			}
		}

		void push_back(const T& x)
		{
			insert(end(), x);
		}

		void push_front(const T& x)
		{
			insert(begin(), x);
		}

		iterator insert(iterator pos, const T& x)
		{
			Node* newnode = new Node(x);
			Node* prev = pos._node->_prev;

			prev->_next = newnode;
			newnode->_prev = prev;
			pos._node->_prev = newnode;
			newnode->_next = pos._node;
			
			_size++;
			return newnode;
		}

		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;

			prev->_next = next;
			next->_prev = prev;
			
			delete pos._node;
			--_size;
			return next;
		}

		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}

		size_t size() const
		{
			return _size;
		}

		bool empty() const
		{
			return _size == 0;
		}

		void clear()
		{
			while (_size != 0)
			{
				pop_back();
			}
		}

		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}

		void swap(list<T> lt)
		{
			std::swap(_head, lt._head);
			std::swap(_size, lt._size);
		}

		~list()
		{
			clear();
			delete _head;
			_head->_next = nullptr;
			_head->_prev = nullptr;

		}

	private:
		Node* _head;
		size_t _size;
	};

	void test_list1()
	{
		list<int> lt;

		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		lt.push_back(4);
		lt.push_back(5);

		list<int>::iterator it = lt.begin();
		while (it != lt.end())
		{
			cout << it._node->_data << " ";
			it++;
		}
		cout << endl;
	}

	void test_list2()
	{
		list<int> lt1;

		lt1.push_back(1);
		lt1.push_back(2);
		lt1.push_back(3);
		lt1.push_back(4);
		lt1.push_back(5);

		print_container(lt1);

		list<int> lt2(lt1);
		print_container(lt1);
		print_container(lt2);

		list<int> lt3;
		lt3.push_back(10);
		lt3.push_back(20);
		lt3.push_back(30);
		lt3.push_back(40);
		lt3.push_back(50);

		lt1 = lt3;
		print_container(lt1);
		print_container(lt3);

		list<int> lt4 = lt3;
		print_container(lt4);

		list<int> lt5 = { 1, 2, 3, 4, 5, 5, 6};
		print_container(lt5);

	}

}
