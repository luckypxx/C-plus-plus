#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//���ù��к�������˽�г�Ա
class Test1
{
private:
	int x;
public:
	void set(int a)
	{
		x = a;
		cout << x << endl;
	}
};


//���ú�������˽�г�Ա
class Test2
{
private:
	int y = 2;
public:
	int set2()
	{
		return y;
	}
};

//�������÷���˽�г�Ա
class Test3
{
private:
	int m = 3;
public:
	void set3(int& a)
	{
		a = m;
	}
};


//����ָ�����˽�б���
class Test4
{
private:
	int n = 4;
public:
	void set4(int* p)
	{
		*p = n;
	}
};
int main()
{
	Test1 T1;
	Test2 T2;
	Test3 T3;
	Test4 T4;
	int a = 0;
	int b = 0;
	int* p = &b;
	T1.set(1);
	cout << T2.set2() << endl;
	T3.set3(a);
	T4.set4(p);
	cout << a << endl;
	cout << *p << endl;
	system("pause");

	return 0;
}