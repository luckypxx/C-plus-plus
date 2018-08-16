#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}
	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

struct A
{
	int _a;
	int _b;
	int _c;
};

void TestAutoPtr()
{
	AutoPtr<int>ap1(new int);
	*ap1 = 10;
	AutoPtr<int>ap2(new A);
	ap2->_a = 10;
}

int main()
{
	TestAutoPtr();
	system("pause");
	return 0;
}
//#if 0
////利用公有函数给私有成员变量赋值
//class Test1
//{
//private:
//	int x;
//public:
//	void set(int a)
//	{
//		x = a;
//		cout << x << endl;
//	}
//};
//
//
////利用函数访问私有成员
//class Test2
//{
//private:
//	int y = 2;
//public:
//	int set2()
//	{
//		return y;
//	}
//};
//
////利用引用访问私有成员
//class Test3
//{
//private:
//	int m = 3;
//public:
//	void set3(int& a)
//	{
//		a = m;
//	}
//};
//
//
////利用指针访问私有变量
//class Test4
//{
//private:
//	int n = 4;
//public:
//	void set4(int* p)
//	{
//		*p = n;
//	}
//};
//int main()
//{
//	Test1 T1;
//	Test2 T2;
//	Test3 T3;
//	Test4 T4;
//	int a = 0;
//	int b = 0;
//	int* p = &b;
//	T1.set(1);
//	cout << T2.set2() << endl;
//	T3.set3(a);
//	T4.set4(p);
//	cout << a << endl;
//	cout << *p << endl;
//	system("pause");
//
//	return 0;
//}
//#endif
//
//class Solution {
//public:
//	int Fibonacci(int n) {
//		if (n <= 2)
//			return 1;
//		else
//			return Fibonacci(n - 1) + Fibonacci(n - 2);
//	}
//};
//
//int main()
//{
//	int n = 0;
//	cin >> n >> endl;
//	cout << Solution.Fibonacci(n) << endl;
//}