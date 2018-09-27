#define _CRT_SECURE_NO_WARNINGS 1
#include "Vector.hpp"
#include <vector>
#include <windows.h>

using namespace std;
int main()
{
	int arr[10] = { 0, 2, 3, 5, 7, 8 };
	Vector<int> v1(arr + 1, arr + 5);
	Vector<int> v2;
	v2.SeqListPushFront(5);
	v2.PrintSeqList();
	v1.PrintSeqList();
	cout << endl;
	v1.SeqListPopBack();
	v1.PrintSeqList();
	cout << endl;
	v1.SeqListErase(1);
	v1.PrintSeqList();
	cout << endl;
	v1.SeqListInsert(1, 3);
	v1.PrintSeqList();
	v1.SeqListPopBack();
	v1.PrintSeqList();
	cout << "3的下标是：" <<v1.SeqListFind(3) <<endl;
	v1.SeqListPopFront();
	v1.PrintSeqList();
	v1.SeqListPushBack(0);
	v1.PrintSeqList();
	v1.SeqListPushFront(1);
	v1.PrintSeqList();
	v1.SeqListRemove(3);
	v1.PrintSeqList();
	system("pause");
	return 0;
}
