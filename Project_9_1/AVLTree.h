#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<class K>
struct TreeNode
{
	TreeNode(const K& key)
		:_key(key)
		,_parent(nullptr)
		,_left(nullptr)
		,_right(nullptr)
		,df(0)
	{ }

	K _key;
	TreeNode* _parent;
	TreeNode* _left;
	TreeNode* _right;
	int df;
};

template<class K>
class AVLTree
{
public:
	typedef TreeNode<K> Node;

	void insert(const K& key)
	{
		if (_root == nullptr)
		{
			_root = new Node(key);
		}

		Node* parent = _root;
		Node* node = _root;
		while (node)
		{
			if (key > node->_key)
			{
				parent = node;
				node = node->_right;
			}
			else if (key < node->_key)
			{
				parent = node;
				node = node->_left;
			}
			else
			{
				return;
			}
		}
		node = new Node(key);
		if (node->_key > parent->_key)
		{
			parent->_right = node;
			parent->df++;
			node->_parent = parent;
			node = node->_parent;
			parent = parent->_parent;
		}

		else if (node->_key < parent->_key)
		{
			parent->_left = node;
			parent->df--;
			node->_parent = parent;
			node = node->_parent;
			parent = parent->_parent;
		}

		while (parent)
		{
			if (parent->df == 0)
				break;
			else if (parent->df == 1 || parent->df == -1)
			{
				node = parent;
				parent = parent->_parent;
				if (node == parent->_right)
				{
					parent->df++;
					node = node->_parent;
					parent = parent->_parent;
				}

				if (node == parent->_left)
				{
					parent->df--;
					node = node->_parent;
					parent = parent->_parent;
				}
			}

			else if (parent->df == 2 || parent->df == -2)
			{
				if (parent->df == -2 && node->df == -1)
				{
					RotateR(parent);
				}
				else if (parent->df == 2 && node->df == 1)
				{
					RotateL(parent);
				}
				else if (parent->df == -2 && node->df == 1)
				{
					RotateLR(parent);
				}
				else if (parent->df == 2 && node->df == -1)
				{
					RotateRL(parent);
				}
			}
			else
			{
				assert(false);
			}
		}
	}

	void RotateR(Node* root)
	{
		Node* subl = root->_left;
		Node* sublr = subl->_right;
		Node* parent = root->_parent;

		root->_left = sublr;
		if (sublr)
			sublr->_parent = root;
		subl->_right = root;

		if (root == _root)
		{
			_root = subl;
		}
		else
		{
			if (parent->_left == root)
				parent->_left = subl;
			else
				parent->_right = subl;
		}
		subl->_parent = parent;
		subl->_right = root;
		root->_parent = subl;

		subl->df = 0;
		root->df = 0;
	}

	void RotateL(Node* root)
	{
		Node* subr = root->_right;
		Node* subrl = subr->_left;
		Node* parent = root->_parent;

		root->_right = subrl;
		if (subrl)
			subrl->_parent = root;
		subr->_left = root;

		if (root == _root)
		{
			_root = subr;
		}
		else
		{
			if (parent->_left == root)
				parent->_left = subr;
			else
				parent->_right = subr;
		}
		subr->_parent = parent;
		subr->_left = root;
		root->_parent = subr;

		subr->df = 0;
		root->df = 0;
	}

	void RotateLR(Node* root)
	{
		Node* subl = root->_left;
		Node* sublr = subl->_right;
		int _df = sublr->df;

		RotateL(subl);
		RotateR(root);

		if (_df == 1)
		{
			sublr->df = 0;
			root->df = 0;
			subl->df = -1;
		}

		else if (_df == -1)
		{
			sublr->df = 0;
			root->df = 1;
			subl->df = 0;
		}

		else if (_df == 0)
		{
			sublr->df = 0;
			root->df = 0;
			subl->df = 0;
		}
	}

	void RotateRL(Node* root)
	{
		Node* subr = root->_right;
		Node* subrl = subr->_left;
		int _df = subrl->df;

		RotateL(subr);
		RotateR(root);

		if (_df == 1)
		{
			subrl->df = 0;
			root->df = -1;
			subr->df = 0;
		}

		else if (_df == -1)
		{
			subrl->df = 0;
			root->df = 0;
			subr->df = 1;
		}

		else if (_df == 0)
		{
			subrl->df = 0;
			root->df = 0;
			subr->df = 0;
		}

		else
		{
			assert(false);
		}
	}

	void inorder()
	{
		_inorder(_root);
		cout << endl;
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
private:
	Node* _root = nullptr;
};