#define _CRT_SECURE_NO_WARNINGS 1
#include"tree.h"

int main()
{
	key::BSTree<int> t;

	int a[] = { 8,3,1,10,1,6,4,7,14,13 };
	for (auto e : a)
	{
		t.insert(e);
	}
	t.inorder();

	/*cout << t.Find(9) << endl;*/
	t.Erase(10);
	t.inorder();


	return 0;
}