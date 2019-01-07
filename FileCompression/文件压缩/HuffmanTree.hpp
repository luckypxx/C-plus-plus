#pragma once
#include <iostream>
#include <functional>
#include <queue>

using namespace std;

template <class W>
struct HuffmanTreeNode
{
public:
	HuffmanTreeNode(const W& weight)
	:_weight(weight)
	, _pLeft(0)
	, _pRight(0)
	, _pParent(0)
	{}

	HuffmanTreeNode<W>* _pLeft;
	HuffmanTreeNode<W>* _pRight;
	HuffmanTreeNode<W>* _pParent;
	W _weight;
};

template <class W>
class Compare
{
public:
	bool operator()(HuffmanTreeNode<W>* pLeft, HuffmanTreeNode<W>* pRight)
	{
		return pLeft->_weight > pRight->_weight ? true : false;
	}

};

template <class W>
class HuffmanTree
{
public:
	HuffmanTree(W* array,size_t size)
		:_array(array)
		, _size(size)
	{
		//�������ȼ�����
		//Huffman���ĵײ�ʵ��Ҫ�����ȼ����У����ȼ����еĵײ��ǶѺ�vector
		priority_queue<HuffmanTreeNode<W>*, vector<HuffmanTreeNode<W>*>, Compare<W>> q;
		//�������е����ݴ����ɸ��ڵ�,�������ȼ�������
		for (size_t i = 0; i < size; ++i)
		{
			if (array[i]._appearCount != 0)
				q.push(new HuffmanTreeNode<W>(array[i]));
			
		}
		
		//�����ȼ������еĸ��ڵ����ӳ���
		while (q.size() > 1)
		{
			HuffmanTreeNode<W>* pLeft = q.top();
			q.pop();

			HuffmanTreeNode<W>* pRight = q.top();
			q.pop();

			HuffmanTreeNode<W>* pParent = new HuffmanTreeNode<W>(pLeft->_weight + pRight->_weight);
			
			pParent->_pLeft = pLeft;
			pParent->_pRight = pRight;
			pLeft->_pParent = pParent;
			pRight->_pParent = pParent;
			q.push(pParent);
		}

		_pRoot = q.top();
	}

	HuffmanTreeNode<W>* GetpRoot()
	{
		return _pRoot;
	}

	void _Destory(HuffmanTreeNode<W>* pRoot)
	{
		if (pRoot->_pLeft)
			_Destory(pRoot->_pLeft);

		if (pRoot->_pRight)
			_Destory(pRoot->_pRight);

		if (pRoot)
			delete[] pRoot;
	}

	~HuffmanTree()
	{
		_Destroy(_pRoot);
	}

	W* _array;
	size_t _size;
	HuffmanTreeNode<W>* _pRoot;
};
