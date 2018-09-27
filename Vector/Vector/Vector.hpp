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
		:_size(end - begin + 1)
		, _capacity(end - begin + 1)
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


	// 尾插 
	void SeqListPushBack(T data)
	{
		if (_size == 0)
		{
			_array = (T*)malloc(sizeof(T)* 5);
		}
		else if (_size == _capacity)
		{
			T* arr = _array;
			_array = (T*)malloc(sizeof(T)* 2 * _size);
			memcpy(arr, _array,_size);
			_capacity = _size * 2;
		}
		

		_array[_size++] = data;
	}

	// 尾删 
	void SeqListPopBack()
	{
		if (_size == 0)
			return;
		_size--;
	}

	// 头插 
	void SeqListPushFront(T data)
	{
		if (_size == 0)
		{
			if (_capacity == 0)
			{
				_array = (T*)malloc(sizeof(T)* 5);
				if (NULL == _array)
					assert(0);
			}

			_array[_size++] = data;
			return;
		}

		for (size_t i = _size; i > 0; --i)
		{
			_array[i] = _array[i - 1];
		}
		_array[0] = data;
		_size++;
	}

	// 头删 
	void SeqListPopFront()
	{
		if (_size == 0)
			return;
		for (size_t i = 0; i < _size; ++i)
		{
			_array[i] = _array[i + 1];
		}
		_size--;
	}

	// 任意位置中插入值为data的元素 
	void SeqListInsert(size_t pos, T data)
	{
		if (_size == _capacity)
		{
			T* arr = _array;
			_array = (T*)malloc(sizeof(T)* 2 * _size);
			memcpy(arr, _array,_size);
			_capacity = _size * 2;
		}
		_size++;

		for (size_t i = _size - 1; i > pos; --i)
		{
			_array[i] = _array[i - 1];
		}
		_array[pos] = data;
	}

	// 删除任意位置中的元素 
	void SeqListErase(size_t pos)
	{
		for (size_t i = pos; i < _size + 1; ++i)
		{
			_array[i] = _array[i + 1];
		}
		_size--;
	}

	// 在顺序表中查找值为data的元素，返回该元素在顺序表中的下标 
	int SeqListFind(T data)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_array[i] == data)
				return i;
		}
	}

	// 删除顺序表中值为data的元素 
	void SeqListRemove(T data)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_array[i] == data)
			{
				SeqListErase(i);
				return;
			}
		}
	}

	// 删除顺序表中所有值为data的元素 
	void SeqListRemoveAll(T data)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_array[i] == data)
			{
				SeqListErase(i);
			}
		}
	}

	// 判断顺序表是否为空 
	int SeqListEmpty()
	{
		if (_size == 0)
		{
			return 1;
		}
		else
			return 0;
	}

	// 获取顺序表中元素的个数 
	int SeqListSize()
	{
		return _size;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////// 
	// 辅助操作 
	// 打印顺序表中的元素 
	void PrintSeqList()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _array[i] << " " ;
		}
		cout << endl;
	}


private:
	T* _array;
	size_t _size; // 顺序表中有效元素的个数 
	size_t _capacity;//顺序表容量
};

