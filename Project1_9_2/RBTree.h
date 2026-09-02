#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

enum Color
{
	black,
	red
};

template<class K>
struct TreeNode
{
	TreeNode(const K& key)
		:_key(key)
		,_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,_col(red)
	{}

	K _key;
	TreeNode* _parent;
	TreeNode* _left;
	TreeNode* _right;
	Color _col;
};

template<class K>
class RBTree
{
public:
	typedef TreeNode<K> Node;

	void insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
			_root->_col = black;
			return;
		}

		Node* cur = _root;
		Node* parent = _root;

		while (cur)
		{
			if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return;
			}
		}

		cur = new Node(key);
		if (cur->_key < parent->_key)
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		else
		{
			parent->_right = cur;
			cur->_parent = parent;

		}

		while (parent && parent->_col == red)
		{
			Node* grand = parent->_parent;
			if (grand && parent == grand->_left)
			{
				Node* uncle = grand->_right;
				if (uncle && uncle->_col == red)
				{
					grand->_col = red;
					parent->_col = black;
					uncle->_col = black;
					cur = grand;
					parent = grand->_parent;
				}
				else 
				{
					if (cur == parent->_left)
					{
						RotateR(grand);
						parent->_col = black;
						grand->_col = red;
					}

					else
					{
						RotateL(parent);
						RotateR(grand);
						cur->_col = black;
						grand->_col = red;
					}
				}
			}
			else if (grand && parent == grand->_right)
			{
				Node* uncle = grand->_left;
				if (uncle && uncle->_col == red)
				{
					grand->_col = red;
					parent->_col = black;
					uncle->_col = black;
					cur = grand;
					parent = grand->_parent;
				}
				else
				{
					if (cur == parent->_right)
					{
						RotateL(grand);
						parent->_col = black;
						grand->_col = red;
					}
					else
					{
						RotateR(parent);
						RotateL(grand);
						cur->_col = black;
						grand->_col = red;
					}
				}
			}
		}

		_root->_col = black;
	}

	void RotateR(Node* parent)
	{
		Node* subl = parent->_left;
		Node* sublr = subl->_right;

		parent->_left = sublr;
		if (sublr)
			sublr->_parent = parent;
		subl->_right = parent;

		if (parent->_parent)
		{
			if (parent == parent->_parent->_left)
			{
				parent->_parent->_left = subl;
			}
			else
			{
				parent->_parent->_right = subl;
			}
		}

		subl->_parent = parent->_parent;
		parent->_parent = subl;

		if (parent == _root)
		{
			_root = subl;
			subl->_parent = nullptr;
		}
	}

	void RotateL(Node* parent)
	{
		Node* subr = parent->_right;
		Node* subrl = subr->_left;

		parent->_right = subrl;
		if (subrl)
			subrl->_parent = parent;
		subr->_left = parent;

		if (parent->_parent)
		{
			if (parent == parent->_parent->_right)
			{
				parent->_parent->_right = subr;
			}
			else
			{
				parent->_parent->_left = subr;
			}
		}

		subr->_parent = parent->_parent;
		parent->_parent = subr;

		if (parent == _root)
		{
			_root = subr;
			subr->_parent = nullptr;
		}
	}

	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	bool isValid() const
	{
		const Node* prev = nullptr;
		if (!_isBST(_root, prev)) 
			return false;   // 中序严格递增
		if (_root && _root->_col != black) 
			return false;
		return _check(_root) != -1;
	}

private:
	void _inorder(const Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_inorder(root->_left);
		cout << root->_key << ",";
		_inorder(root->_right);
	}

	bool _isBST(const Node* n, const Node*& prev) const
	{
		if (n == nullptr) 
			return true;
		if (!_isBST(n->_left, prev)) 
			return false;
		if (prev && !(prev->_key < n->_key))
			return false;
		prev = n;
		return _isBST(n->_right, prev);
	}

	int _check(const Node* n) const
	{
		if (n == nullptr)
			return 1;                 // 空叶子(NIL)算 1 个黑
		int lh = _check(n->_left);
		if (lh == -1) 
			return -1;
		int rh = _check(n->_right);
		if (rh == -1 || lh != rh) 
			return -1;        // 黑高必须一致
		if (n->_col == red)                          // 红节点不能有红孩子
		{
			if (n->_left && n->_left->_col == red) 
				return -1;
			if (n->_right && n->_right->_col == red) 
				return -1;
		}
		return lh + (n->_col == black ? 1 : 0);
	}

private:
	Node* _root = nullptr;
};