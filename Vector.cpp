#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <memory.h>
#include <assert.h>
template <class T>
class Vector
{
public:
	// 初始化顺序表 
	Vector()
		:_array(NULL)
		, _size(0)
		, _capacity(0)
	{
		memset(_array, 0, _capacity);
	}

	Vector(size_t size, T value)
		:_size(size)
		, _capacity(size)
	{
		_array = (T*)malloc(sizeof(T)*size);
		for (size_t i = 0; i < size; ++i)
		{
			_array[i] = value;
		}
	}

	Vector(T* begin, T* end)
		:_size(end - begin)
		, _capacity(end - begin)
	{
		_array = (T*)malloc(sizeof(T)*_size);
		for (size_t i = 0; i < _size; ++i)
		{
			_array[i] = *(begin + i);
		}
	}

	Vector(const Vector<T>& v)
		:_size(v._size)
		, _capacity(v._capacity)
	{
		_array = (T*)malloc(sizeof(T)*_size);
		if (NULL == _array)
		{
			assert(0);
		}

		memcpy(_array, v._array, _size);
	}

	Vector<T>& operator= (const Vector<T>& v)
	{
		_size = v._size;
		_capacity = v._capacity;
		_array = (T*)malloc(sizeof(T)*_size);
		memcpy(_array, v._array, _size);
		return *this;
	}



private:
	T* _array;
	size_t _size; // 顺序表中有效元素的个数 
	size_t _capacity;//顺序表容量
};

