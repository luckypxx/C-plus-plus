#define _CRT_SECURE_NO_WARNINGS 1
/*********************第一种auto_ptr*************************/
#include <iostream>

template <class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
	{}

	//将ap对象中的资源转移到当前对象上去
	AutoPtr(AutoPtr<T>& ap)
		:_ptr(ap._ptr)
	{
		ap._ptr = NULL;
	}

	AutoPtr<T>& operator = (AutoPtr<T>& ap)
	{
		if (this != &ap)
		{
			delete _ptr;
			_ptr = ap._ptr;
			ap._ptr = NULL;
		}

		return *this;
	}

	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}

	~AutoPtr()
	{
		if (_ptr)
			delete _ptr;
	}
private:
	T* _ptr;
};

void TestAutoPtr()
{
	AutoPtr<int> ap1(new int);
	AutoPtr<int> ap11(ap1);
	*ap11 = 10;
}

int main()
{
	TestAutoPtr();
	return 0;
}
/****************************第二种auto_ptr******************************/
#include <stdlib.h>
#include<iostream>

using namespace std;
template<class T>

class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL)
		:_ptr(ptr)
		, _owner(NULL)
	{
		if (_ptr)
			_owner = true;
	}

	AutoPtr(const AutoPtr<T>& ap)
		:_ptr(ap._ptr)
		, _owner(ap._owner)
	{
		ap._owner = false;
	}

	T& operator* ()
	{
		return *_ptr;
	}

	AutoPtr<T>& operator=(const AutoPtr<T>& ap)
	{
		if (&ap != this)
		{
			if (_owner && _ptr)
				delete _ptr;
			_ptr = ap._ptr;
			_owner = ap._owner;
			ap._owner = false;
		}

		return *this;
	}

	~AutoPtr()
	{
		if (_owner && _ptr)
		{
			delete _ptr;
		}
	}

	

private:
	T* _ptr;
	mutable bool _owner;//是否对指针有释放的权力
};

void Test2()
{
	AutoPtr<int> ap1(new int);
	AutoPtr<int> ap2(ap1);

	*ap1 = 10;
	*ap2 = 20;

	if (true)
	{
		AutoPtr<int> ap3(ap2);

	}
	*ap1 = 30;

}

int main()
{
	
	Test2();
	return 0;
}