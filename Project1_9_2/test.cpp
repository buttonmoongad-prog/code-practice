#define _CRT_SECURE_NO_WARNINGS 1
#include"RBTree.h"
#include <random>   // 加在文件顶部 #include 区

int main()
{
    // 单元素
    {
        RBTree<int> t;
        t.insert(1);
        cout << "单元素:      " << (t.isValid() ? "PASS" : "FAIL") << " | ";
        t.inorder();
    }

    // 升序 1..10
    {
        RBTree<int> t;
        for (int i = 1; i <= 10; ++i) t.insert(i);
        cout << "升序 1..10:  " << (t.isValid() ? "PASS" : "FAIL") << " | ";
        t.inorder();
    }

    // 降序 10..1
    {
        RBTree<int> t;
        for (int i = 10; i >= 1; --i) t.insert(i);
        cout << "降序 10..1:  " << (t.isValid() ? "PASS" : "FAIL") << " | ";
        t.inorder();
    }

    // LR 特例
    {
        RBTree<int> t;
        for (int x : {3, 1, 2}) t.insert(x);
        cout << "LR(3,1,2):   " << (t.isValid() ? "PASS" : "FAIL") << " | ";
        t.inorder();
    }

    // RL 特例
    {
        RBTree<int> t;
        for (int x : {1, 3, 2}) t.insert(x);
        cout << "RL(1,3,2):   " << (t.isValid() ? "PASS" : "FAIL") << " | ";
        t.inorder();
    }

    // 重复键（应被忽略，不崩）
    {
        RBTree<int> t;
        for (int i = 1; i <= 5; ++i) t.insert(i);
        t.insert(3); t.insert(1); t.insert(5);
        cout << "重复键:      " << (t.isValid() ? "PASS" : "FAIL") << " | ";
        t.inorder();
    }

    // 随机 1000 个
    {
        RBTree<int> t;
        mt19937 rng(12345);
        uniform_int_distribution<int> dist(1, 100000);
        for (int i = 0; i < 1000; ++i) t.insert(dist(rng));
        cout << "随机 1000 个: " << (t.isValid() ? "PASS" : "FAIL") << endl;
    }

    return 0;
}