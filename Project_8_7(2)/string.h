#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace button
{
	class string
	{
	public:
		typedef char* iterator;
		typedef const char* const_iterator;

		iterator begin()
		{
			return _str;
		}

		const_iterator begin() const
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size == 0 ? 15 : _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		string(const string& str, size_t len = npos)
		{
			if (len > str._size)
				len = str._size;

			_size = len;
			_capacity = _size;
			_str = new char[_capacity + 1];

			strncpy(_str, str._str, len);
			_str[len] = '\0';
		}
		
		size_t size()
		{
			return _size;
		}

		size_t capacity()
		{
			return _capacity;
		}

		void reserve(size_t n)
		{
			if (n <= _capacity)
			{
				return;
			}

			else
			{
				size_t newcapacity = 16;
				while (n >= newcapacity)
				{
					newcapacity *= 2;
				}

				char* newstr = new char[newcapacity + 1];
				strcpy(newstr, _str);
				
				delete[] _str;
				_str = newstr;
				_capacity = newcapacity - 1;
			}
		}

		//前面的 const：函数返回 const char*，即指向常量字符的指针。调用者不能通过这个指针去修改它指向的字符内容。
		// 后面的 const：这个成员函数不会修改当前对象的任何成员变量（_str、_size、_capacity）。因此它可以被 const string对象调用。
		const char* c_str() const
		{
			return _str;
		}

		void push_back(char ch)
		{
			if (_size == _capacity)
			{
				reserve(_capacity * 2);
			}
			_str[_size++] = ch;
			_str[_size] = '\0';
			
		}

		void append(const char ch[])
		{
			size_t len = strlen(ch);
			while (_size + len >= _capacity)
			{
				reserve(_capacity * 2);
			}

			for (int i = 0; i < len; i++)
			{
				_str[_size++] = ch[i];
			}
			_str[_size] = '\0';
		}

		void append(const string& str)
		{
			size_t len = str._size;
			while (_size + len >= _capacity)
			{
				reserve(_capacity * 2);
			}

			for (int i = 0; i < len; i++)
			{
				_str[_size++] = str._str[i];
			}
			_str[_size] = '\0';
		}

		string substr(size_t pos = 0, size_t n = npos) const
		{
			assert(pos < _size);
			if (n > _size - pos)
				n = _size - pos;

			string str;
			str._size = n;
			str._capacity = str._size;
			delete[] str._str;
			str._str = new char[str._capacity + 1];

			int i = 0;
			for (int j = 0; j < n; j++)
			{
				str._str[i++] = _str[pos++];
			}
			str._str[str._size] = '\0';

			return str;
		}

		size_t find(const char* ch, size_t pos = 0) const
		{
			assert(ch);
			size_t len = strlen(ch);
			for (size_t t = pos; t + len <= _size; t++)   // t 从 pos 开始，加边界保护
			{
				if (_str[t] == *ch)
				{
					size_t i = 0;
					for (; i < len; i++)
						if (_str[t + i] != ch[i])
							break;
					if (i == len)
						return t;
				}
			}
			return npos;
		}

		size_t find(const string& str, size_t pos = 0) const
		{
			assert(str._size != 0);
			for (size_t t = pos; t + str._size <= _size; t++)   // t 从 pos 开始，加边界保护
			{
				if (_str[t] == str._str[0])
				{
					size_t i = 0;
					for (; i < str._size; i++)
						if (_str[t + i] != str._str[i])
							break;
					if (i == str._size)
						return t;
				}
			}
			return npos;
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);
			return _str[pos];
		}

		char& operator[](size_t pos) const
		{
			assert(pos < _size);
			return _str[pos];
		}

		void clear()
		{
			_size = 0;
		}

		void operator+=(const char ch)
		{
			push_back(ch);
		}

		void operator+=(const char ch[])
		{
			append(ch);
		}

		void operator+=(const string& str)
		{
			append(str);
		}

		~string()
		{
			delete[] _str;
			_size = 0;
			_capacity = 0;
		}

		static const size_t npos;
		void insert(const char* ch, size_t pos);
		void insert(const string& str, size_t pos);
		void erase(size_t pos, size_t n);
		void replace(size_t pos, size_t n, const char* ch);
		void replace(size_t pos, size_t n, const string& str);


	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};

	ostream& operator<<(ostream& out, const string& str);
	istream& operator>>(istream& in, const string& str);

	void test_my_string1();
	void test_my_string2();
	void test_my_string3();
	void test_my_string4();
	void test_my_string5();


}