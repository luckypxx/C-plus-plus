#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <windows.h>

using namespace std;

class Base
{
public:
	virtual void Test1(int test)
	{
		cout << "Base::Test1()" << endl;
	}

	void Test2(int test)
	{
		cout << "Base::Test2()" << endl;
	}

	int  b;
};

class Derived:public Base
{
public:
	virtual void Test1(int test)
	{
		cout << "Derived::Test1()" << endl;
	}

	virtual void Test2(int test)
	{
		cout << "Base::Test2()" << endl;
	}

	int d;
};

void TestFun(Base& b)
{
	b.Test1(0);
	b.Test2(0);
}

int main()
{
	Base b;
	Derived d;
	cout << sizeof(b) << endl;
	TestFun(b);
	TestFun(d);
	system("pause");
	return 0;
}

