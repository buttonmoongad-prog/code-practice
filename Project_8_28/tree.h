#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

namespace key
{
	template<class K>
	struct BSNode
	{
		K _key;

		BSNode* _left;
		BSNode* _right;

		BSNode(const K& key)
			:_key(key)
			,_left(nullptr)
			,_right(nullptr)
		{}

	};

	template<class K>
	class BSTree
	{
	public:
		typedef BSNode<K> _node;
		
		bool insert(const K& key)
		{
			if (_root == nullptr)
			{
				_root = new _node(key);
				return true;
			}

			_node* parent = _root;
			_node* node = _root;
			
			while (node)
			{
				if (node->_key > key)
				{
					parent = node;
					node = node->_left;
				}
				else
				{
					parent = node;
					node = node->_right;
				}
			}
			
			node = new _node(key);
			if (parent->_key > key)
			{
				parent->_left = node;
			}

			else
			{
				parent->_right = node;
			}
			return true;
		}

		bool Find(const K& key)
		{
			if (_root == nullptr)
				return false;

			_node* node = _root;
			while (node)
			{
				if (node->_key == key)
					return true;

				if (node->_key > key)
					node = node->_left;
				else
					node = node->_right;
			}
			return false;
		}

		bool Erase(const K& key)
		{
			assert(_root != nullptr);

			_node* parent = _root;
			_node* cur = _root;

			while (cur)
			{
				if (cur->_key != key)
				{
					if (cur->_key > key)
					{
						parent = cur;
						cur = cur->_left;
					}

					else
					{
						parent = cur;
						cur = cur->_right;
					}
				}

				else
				{
					if (cur->_left == nullptr && cur->_right == nullptr)
					{
						if (parent->_left == cur)
							parent->_left = nullptr;
						
						if (parent->_right == cur)
							parent->_right = nullptr;
						
						delete cur;
						return true;
					}

					else if (cur->_left == nullptr)
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
							delete cur;
						}

						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
							delete cur;
						}
						return true;

					}

					else if (cur->_right == nullptr)
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
							delete cur;
						}

						if (parent->_right == cur)
						{
							parent->_right = cur->_left;
							delete cur;
						}
						return true;

					}

					else
					{
						_node* tmp = cur->_right;
						parent = cur;
						while (tmp->_left)
						{
							parent = tmp;
							tmp = tmp->_left;
						}

						cur->_key = tmp->_key;
						if (parent->_left == tmp)
						{
							parent->_left = tmp->_right;
							delete tmp;
						}

						if (parent->_right == tmp)
						{
							parent->_right = tmp->_right;
							delete tmp;
						}
						return true;

					}
				}
			}
			return false;
		}

		void inorder()
		{
			_inorder(_root);
			cout << endl;
		}

	private:
		void _inorder(_node* _root)
		{
			if (_root == nullptr)
				return;

			_inorder(_root->_left);
			cout << _root->_key << " ";
			_inorder(_root->_right);
		}

	private:
		_node* _root = nullptr;
	};
}

namespace key_value
{
	template<class K, class V>
	struct BSNode
	{
		K _key;
		V _val;

		BSNode* _left;
		BSNode* _right;

		BSNode(const K& key, const V& val)
			:_key(key)
			,_val(val)
			, _left(nullptr)
			, _right(nullptr)
		{}

	};

	template<class K, class V>
	class BSTree
	{
	public:
		typedef BSNode<K, V> _node;

		bool insert(const K& key, const V& val)
		{
			if (_root == nullptr)
			{
				_root = new _node(key, val);
				return true;
			}

			_node* parent = _root;
			_node* node = _root;

			while (node)
			{
				if (node->_key > key)
				{
					parent = node;
					node = node->_left;
				}
				else
				{
					parent = node;
					node = node->_right;
				}
			}

			node = new _node(key, val);
			if (parent->_key > key)
			{
				parent->_left = node;
			}

			else
			{
				parent->_right = node;
			}
			return true;
		}

		bool Find(const K& key)
		{
			if (_root == nullptr)
				return false;

			_node* node = _root;
			while (node)
			{
				if (node->_key == key)
					return true;

				if (node->_key > key)
					node = node->_left;
				else
					node = node->_right;
			}
			return false;
		}

		bool Erase(const K& key)
		{
			assert(_root != nullptr);

			_node* parent = _root;
			_node* cur = _root;

			while (cur)
			{
				if (cur->_key != key)
				{
					if (cur->_key > key)
					{
						parent = cur;
						cur = cur->_left;
					}

					else
					{
						parent = cur;
						cur = cur->_right;
					}
				}

				else
				{
					if (cur->_left == nullptr && cur->_right == nullptr)
					{
						if (parent->_left == cur)
							parent->_left = nullptr;

						if (parent->_right == cur)
							parent->_right = nullptr;

						delete cur;
						return true;
					}

					else if (cur->_left == nullptr)
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_right;
							delete cur;
						}

						if (parent->_right == cur)
						{
							parent->_right = cur->_right;
							delete cur;
						}
						return true;

					}

					else if (cur->_right == nullptr)
					{
						if (parent->_left == cur)
						{
							parent->_left = cur->_left;
							delete cur;
						}

						if (parent->_right == cur)
						{
							parent->_right = cur->_left;
							delete cur;
						}
						return true;

					}

					else
					{
						_node* tmp = cur->_right;
						parent = cur;
						while (tmp->_left)
						{
							parent = tmp;
							tmp = tmp->_left;
						}

						cur->_key = tmp->_key;
						if (parent->_left == tmp)
						{
							parent->_left = tmp->_right;
							delete tmp;
						}

						if (parent->_right == tmp)
						{
							parent->_right = tmp->_right;
							delete tmp;
						}
						return true;

					}
				}
			}
			return false;
		}

		void inorder()
		{
			_inorder(_root);
			cout << endl;
		}

	private:
		void _inorder(_node* _root)
		{
			if (_root == nullptr)
				return;

			_inorder(_root->_left);
			cout << _root->_key << " ";
			_inorder(_root->_right);
		}

	private:
		_node* _root = nullptr;
	};
}