#define _CRT_SECURE_NO_WARNINGS 1
#include"AVLTree.h"

int main()
{
	AVLTree<int> t;

	int a[] = { 4,2,6,1,3,5,15,7,16,14 };
	for (auto e : a)
	{
		t.insert(e);
	}
	t.inorder();

	return 0;
}