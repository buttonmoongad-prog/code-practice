#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class K, class V>
struct HashNode
{
	HashNode(const pair<K,V>& kv)
		:_kv(kv)
		,_next(nullptr)
	{}

	pair<K, V> _kv;
	HashNode<K, V>* _next;
};

template<class K, class V>
class HashTable
{
public:
	typedef HashNode<K,V> Node;
	HashTable(const size_t& size = 10)
		:_table(size, nullptr)
		,_n(0)
	{}

	bool insert(const pair<K, V>& kv)
	{
		if (_n == _table.size())
		{
			size_t newsize = _table.size() * 2;
			vector<Node*> newtable(newsize, nullptr);

			for (int i = 0; i < _table.size(); i++)
			{
				Node* cur = _table[i];
				while (cur)
				{
					Node* next = cur->_next;
					int hashi = cur->_kv.first % newsize;

					cur->_next = newtable[hashi];
					newtable[hashi] = cur;

					cur = next;
				}
			}
			_table.swap(newtable);
		}

		Node* cur = new Node(kv);
		int hashi = cur->_kv.first % _table.size();

		cur->_next = _table[hashi];
		_table[hashi] = cur;

		_n++;
		return true;
	}

	bool Find(const K& key)
	{
		int hashi = key % _table.size();
		Node* cur = _table[hashi];

		while (cur)
		{
			if (cur->_kv.first == key)
				return true;
		}

		return false;
	}

	bool Erase(const K& key)
	{
		if (!Find(key))
			return false;

		int hashi = key % _table.size();
		Node* cur = _table[hashi];
		Node* prev = nullptr;

		while (cur)
		{
			if (cur->_kv.first == key)
			{
				if (prev == nullptr)
				{
					_table[hashi] = cur->_next;
					break;
				}
				prev->_next = cur->_next;
			}
			else
			{
				prev = cur;
				cur = cur->_next;
			}
		}
		delete cur;
		_n--;
		
	}
private:
	vector<Node*> _table;
	size_t _n;
};