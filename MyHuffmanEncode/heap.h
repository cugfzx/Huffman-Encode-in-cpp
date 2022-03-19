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
{//�����齨����С��
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[n];
	if (heap == NULL) 
	{ 
		cout << "�ռ����ʧ��" <<endl ;
		exit(1); 
	}
	for (int i = 0;i < n;++i)
	{
		heap[i] = arr[i];
	}
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;//���ÿ�ʼ������λ��Ϊ����֧�ڵ�
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);//��鲢�����������
		currentPos--;
	}
}

template<class E>
void MinHeap<E>::siftDown(int start, int m)
{
	/*�ӽڵ�start��ʼ��mΪֹ���������ϱȽϣ������Ů��ֵС�ڸ�����ֵ��
	��ؼ���С���ϸ����������²�Ƚϣ�������һ�����Ͼֲ�����Ϊ��С��*/
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])
			j++;//��jָ������Ů�е���С��

		if (temp <= heap[j])
			break;//С��������
		else 
		{//����С���ϸ���i,j�½�
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
	/*�ӽ��start��ʼ�����0Ϊֹ���������Ͻ��бȽϣ������Ů����ֵС�ڸ�����ֵ
	���໥�������������������µ���Ϊ��С��*/
	int j = start, i = (j - 1) / 2;//iָ��start��˫�׽��
	E temp = heap[j];
	while (j > 0)//����start��˫�׽������ֱ���
	{
		if (heap[i] <= temp)
			break;//�����ֵ�Ȳ���Ľ��С��������С�ѣ�������
		else
		{
			heap[j] = heap[i];//���ӽ���ֵ����

			//����һ��
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
		cout << "�ѿ�" << endl;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);//����
}

template<class E>
void MinHeap<E>::Insert(const E& x)
{
	if (currentSize == maxHeapSize)
	{
		cout << "����" << endl;
	}
	heap[currentSize] = x;
	siftUp(currentSize);//����
	++currentSize;
}