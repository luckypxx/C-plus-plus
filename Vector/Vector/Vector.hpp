#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <memory.h>
#include <assert.h>
template <class T> 
class Vector
{
public:
	// ��ʼ��˳��� 
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


	// β�� 
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

	// βɾ 
	void SeqListPopBack()
	{
		if (_size == 0)
			return;
		_size--;
	}

	// ͷ�� 
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

	// ͷɾ 
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

	// ����λ���в���ֵΪdata��Ԫ�� 
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

	// ɾ������λ���е�Ԫ�� 
	void SeqListErase(size_t pos)
	{
		for (size_t i = pos; i < _size + 1; ++i)
		{
			_array[i] = _array[i + 1];
		}
		_size--;
	}

	// ��˳����в���ֵΪdata��Ԫ�أ����ظ�Ԫ����˳����е��±� 
	int SeqListFind(T data)
	{
		for (size_t i = 0; i < _size; ++i)
		{
			if (_array[i] == data)
				return i;
		}
	}

	// ɾ��˳�����ֵΪdata��Ԫ�� 
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

	// ɾ��˳���������ֵΪdata��Ԫ�� 
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

	// �ж�˳����Ƿ�Ϊ�� 
	int SeqListEmpty()
	{
		if (_size == 0)
		{
			return 1;
		}
		else
			return 0;
	}

	// ��ȡ˳�����Ԫ�صĸ��� 
	int SeqListSize()
	{
		return _size;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////// 
	// �������� 
	// ��ӡ˳����е�Ԫ�� 
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
	size_t _size; // ˳�������ЧԪ�صĸ��� 
	size_t _capacity;//˳�������
};

