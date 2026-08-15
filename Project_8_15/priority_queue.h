#pragma once
#include<iostream>
#include<vector>
using namespace std;

namespace button
{
	template<class T, class Container = vector<T>, class Compare = Less<T>>
	class priority_queue
	{
	public:
		void Adjustup()
		{
			size_t child = _con.size() - 1;
			size_t parent = (child - 1) / 2;

			while (child > 0 && com(_con[parent], _con[child]))
			{
				swap(_con[child], _con[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
		}

		//void Adjustdown()
		//{
		//	size_t parent = 0;
		//	size_t max = parent * 2 + 1;
		//	
		//	if (max + 1 < _con.size() && _con[max] < _con[max + 1])
		//	{
		//		max++;
		//	}

		//	while (max < _con.size() && _con[parent] < _con[max])
		//	{
		//		swap(_con[parent], _con[max]);
		//		parent = max;
		//		max = parent * 2 + 1;
		//		if (max + 1 < _con.size() && _con[max] < _con[max + 1])
		//		{
		//			max++;
		//		}
		//	}
		//}

		void Adjustdown()
		{
			size_t parent = 0;
			size_t child = parent * 2 + 1;
			size_t n = _con.size();

			while (child < n)
			{
				if (child + 1 < n && com(_con[child], _con[child + 1]))
					child++;
				if (com(_con[parent], _con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}

		void print()
		{
			while (!empty())
			{
				cout << _con[0] << " ";
				pop();
			}
			cout << endl;
		}

		void push_back(const T& x)
		{
			_con.push_back(x);
			Adjustup();
		}

		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();
			Adjustdown();
		}

		bool empty() const
		{
			return _con.empty();
		}

	private:
		Compare com;
		Container _con;
	};

	template<class T>
	struct Less
	{
		bool operator()(const T& x, const T& y)
		{
			return x < y;
		}
	};

	template<class T>
	struct Greater
	{
		bool operator()(const T& x, const T& y)
		{
			return x > y;
		}
	};


	void test()
	{
		priority_queue<int, vector<int>, Greater<int>> pq;
		
		pq.push_back(0);
		pq.push_back(3);
		pq.push_back(9);
		pq.push_back(7);
		pq.push_back(5);
		pq.push_back(10);
		pq.push_back(30);
		pq.push_back(22);
		pq.push_back(12);
		pq.push_back(6);

		pq.print();
	}
}
