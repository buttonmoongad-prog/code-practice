#define _CRT_SECURE_NO_WARNINGS 1
#include"string.h"

namespace button
{
	const size_t string::npos = -1;
	
	void string::insert(const char* ch,size_t pos = 0)
	{
		assert(pos <= _size);

		if (pos == _size)
			*this += ch;
		else
		{
			//截断pos后的作为子串，再分别尾插ch和子串
			size_t len = strlen(ch);
			reserve(_size + len);
			string s = substr(pos);
			_size = pos;
			*this += ch;
			*this += s;

			//手动移位
			//size_t len = strlen(ch);
			//if (len == 0)
			//	return;
			//reserve(_size + len);
			//iterator it = end() + 1;
			//while (it != begin() + pos)
			//{
			//	*(it + len - 1) = *(it - 1);
			//	it--;
			//}
			//for (size_t i = pos; i < pos + len; i++)
			//{
			//	_str[i] = *ch;
			//	ch++;
			//}
			//_size += len;
		}
	}

	void string::insert(const string& str, size_t pos = 0)
	{
		assert(pos <= _size);

		if (pos == _size)
			*this += str;

		else
		{
			string s = substr(pos);
			_size = pos;
			*this += str;
			*this += s;
		}
	}

	void string::erase(size_t pos = 0, size_t n = npos)
	{
		if (n >= _size - pos)
		{
			_str[pos] = '\0';
			_size = pos;
		}
		else
		{
			string s = substr(pos + n);
			_size = pos;
			*this += s;
		}
	}

	void string::replace(size_t pos, size_t n, const char* ch)
	{
		assert(pos <= _size);

		erase(pos, n);
		insert(ch, pos);
	}

	void string::replace(size_t pos, size_t n, const string& str)
	{
		assert(pos <= _size);

		erase(pos, n);
		insert(str, pos);
	}

	ostream& operator<<(ostream& out, const string& str)
	{
		for (auto ch : str)
		{
			out << ch;
		}

		return out;
	}
	
	istream& operator>>(istream& in, string& str)
	{
		str.clear();

		char buff[256];
		int i = 0;

		char ch = in.get();
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == 255)
			{
				buff[255] = '\0';
				str += buff;

				i = 0;
			}
			ch = in.get();
		}

		if (i != 0)
		{
			buff[i] = '\0';
			str += buff;
		}
		return in;
	}


	void test_my_string1()
	{
		string s1;
		string s2("hello world");
		string s3(s2, 5);

		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		cout << s3.c_str() << endl;

	}
	
	void test_my_string2()
	{
		string s1("hello world");
		s1.reserve(16);
		cout << s1.capacity() << endl;
		
		s1.reserve(32);
		cout << s1.capacity() << endl;

		s1.reserve(100);
		cout << s1.capacity() << endl;

		s1.reserve(100);
		cout << s1.capacity() << endl;
	}

	void test_my_string3()
	{
		string s1("hello");
		s1.push_back(' ');
		cout << s1.c_str() << endl;

		s1.append("world");
		cout << s1.c_str() << endl;

		s1 += " hello";
		cout << s1.c_str() << endl;

		s1 += " button";
		cout << s1.c_str() << endl;
	}

	void test_my_string4()
	{
		string s1("hello world");
		string s2 = s1.substr(5);
		cout << s2.c_str() << endl;

		s1.insert("abcd ", 6);
		cout << s1.c_str() << endl;

		s1.insert(s2, 15);
		cout << s1.c_str() << endl;

		s1.erase(0, 6);
		cout << s1.c_str() << endl;

		s1.erase(4);
		cout << s1.c_str() << endl;

		s1.replace(4, 1, "cc");
		cout << s1.c_str() << endl;

		s1.replace(4, 2, s2);
		cout << s1.c_str() << endl;

	}

	void test_my_string5()
	{
		string s1("abcdefghijklgimn");
		s1.replace(s1.find("gi"), 2, " ");
		cout << s1.c_str() << endl;

		string s2("efg");
		s1.replace(s1.find(s2), 3, " ");
		cout << s1.c_str() << endl;

		cout << s1 << endl;
		cin >> s2;
		cout << s2 << endl;
	}
}