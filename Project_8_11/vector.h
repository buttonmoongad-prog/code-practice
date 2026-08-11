#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace button
{
	template <class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;

		iterator begin()
		{
			return _start;
		}
		
		iterator end()
		{
			return _finish;
		}

		const_iterator begin() const
		{
			return _start;
		}

		const_iterator end() const
		{
			return _finish;
		}

		vector() = default;

		vector(size_t n, const T& x = T())
		{
			reserve(n);

			for (size_t i = 0; i < n; i++)
			{
				push_back(x);
			}
			_finish = _start + n;
		}

		vector(const vector<T>& v)
		{
			reserve(v.capacity());
			
			size_t len = v.size();
			for (size_t i = 0; i < len; i++)
			{
				push_back(v[i]);
			}
			_finish = _start + len;
		}

		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			size_t len = last - first;
			_start = new T[len];
			_finish = _start;

			for (size_t i = 0; i < len; i++)
			{
				push_back(first[i]);
			}
			_end_of_storage = _finish;
		}

		size_t size() const
		{
			return _finish - _start;
		}

		size_t capacity() const
		{
			return _end_of_storage - _start;
		}

		bool empty() const
		{
			if (_start == _finish)
				return true;
			return false;
		}

		void reserve(size_t n)
		{
			if (n <= size())
			{
				return;
			}
			else
			{
				size_t old_size = size();
				T* tmp = new T[n];
				for (size_t i = 0; i < old_size; i++)
				{
					tmp[i] = _start[i];
				}

				delete[] _start;
				_start = tmp;
				_finish = _start + old_size;
				_end_of_storage = _start + n;
			}
		}

		void pop_back()
		{
			assert(!empty());
			_finish--;
		}

		//T&防止每次调用都进行一次拷贝构造
		void push_back(const T& x)
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}

			*_finish = x;
			_finish++;
		}

		iterator insert(iterator pos, const T& x)
		{
			assert(pos != _finish);

			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;
			}

			iterator it = _finish;
			while (it >= pos)
			{
				*it = *(it - 1);
				it--;
			}
			*pos = x;
			_finish++;
			return pos;
		}

		iterator erase(iterator pos)
		{
			assert(pos < _finish);

			iterator it = pos;
			while (it < end() - 1)
			{
				*it = *(it + 1);
				it++;
			}
			_finish--;
			return pos;
		}

		T& operator[](size_t pos)
		{
			return *(_start + pos);
		}

		const T& operator[](size_t pos) const
		{
			return *(_start + pos);
		}

		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;
		iterator _end_of_storage = nullptr;
	};

	template <class T>
	void print(const vector<T>& v)
	{
		for (auto& x : v)
		{
			cout << x << " ";
		}
		cout << endl;
	}

	void test_vector1()
	{
		vector<int> v1;

		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		print(v1);

		vector<int> v2(v1.begin(), v1.begin() + 3);
		print(v2);

		vector<int> v3(v1);
		print(v3);
	}

	void test_vector2()
	{
		vector<int> v1;

		v1.push_back(1);
		v1.push_back(2);
		v1.push_back(3);
		v1.push_back(4);
		v1.push_back(5);
		print(v1);

		int x;
		cin >> x;
		button::vector<int>::iterator p = find(v1.begin(), v1.end(), x);
		
		if (p != v1.end())
			p = v1.insert(p, 325);
		print(v1);
		
		v1.erase(v1.begin() + 1);
		print(v1);

	}
}
