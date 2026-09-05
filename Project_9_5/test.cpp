#define _CRT_SECURE_NO_WARNINGS 1
#include"Hash.h"

int main()
{
	HashTable<int, int> h;
	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	for (auto& e : a)
	{
		h.insert({ e, e });
	}

	/*h.insert({ 11, 11 });
	h.insert({ 21, 21 });
	h.insert({ 31, 31 });
	h.insert({ 10, 10 });
	h.insert({ 20, 20 });*/

	h.Erase(1);

	return 0;
}