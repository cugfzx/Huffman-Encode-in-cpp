#pragma once
#include <iostream>
#define DefaultSize 10
using namespace std;

template<class E>
class MinHeap
{
public:
	MinHeap(E arr[], int n);
	MinHeap(){}
	~MinHeap() { delete[]heap; }
	void GetMin(E& x);
	void Insert(const E& x);
private:
	E* heap;
	int currentSize;
	int maxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start, int m);
};

template<class E>
MinHeap<E>::MinHeap(E arr[], int n)
{//由数组建立最小堆
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[n];
	if (heap == NULL) 
	{ 
		cout << "空间分配失败" <<endl ;
		exit(1); 
	}
	for (int i = 0;i < n;++i)
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;//设置开始调整的位置为最后分支节点
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);//检查并调整这棵子树
		currentPos--;
	}
}

template<class E>
void MinHeap<E>::siftDown(int start, int m)
{
	/*从节点start开始到m为止，自下向上比较，如果子女的值小于父结点的值，
	则关键码小的上浮，继续向下层比较，这样将一个集合局部调整为最小堆*/
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])
			j++;//让j指向两子女中的最小者

		if (temp <= heap[j])
			break;//小则不做调整
		else 
		{//否则小者上浮，i,j下降
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i]=temp;
}

template<class E>
void MinHeap<E>::siftUp(int start, int m)
{
	/*从结点start开始到结点0为止，自下向上进行比较，如果子女结点的值小于父结点的值
	则相互交换，这样将集合重新调整为最小堆*/
	int j = start, i = (j - 1) / 2;//i指向start的双亲结点
	E temp = heap[j];
	while (j > 0)//沿着start的双亲结点向上直达根
	{
		if (heap[i] <= temp)
			break;//父结点值比插入的结点小，满足最小堆，不调整
		else
		{
			heap[j] = heap[i];//父子结点的值交换

			//上移一层
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class E>
void MinHeap<E>::GetMin(E& x)
{
	if(!currentSize)
	{
		cout << "堆空" << endl;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);//调整
}

template<class E>
void MinHeap<E>::Insert(const E& x)
{
	if (currentSize == maxHeapSize)
	{
		cout << "堆满" << endl;
	}
	heap[currentSize] = x;
	siftUp(currentSize);//调整
	++currentSize;
}