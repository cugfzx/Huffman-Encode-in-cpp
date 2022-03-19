#pragma once
#include "heap.h"
#include <vector>

template<class T>
class HuffmanNode
{
public:
	//����㶨��
	T data;//����

	//�����ӽ��ָ�룬˫�׽��ָ��
	HuffmanNode<T> *leftChild, * rightChild, *parent;

	//���캯��
	HuffmanNode():leftChild(NULL),rightChild(NULL),parent(NULL){}
	HuffmanNode(T elem, HuffmanNode* left=NULL, HuffmanNode* right=NULL, HuffmanNode* pr=NULL)
		:data(elem), leftChild(NULL), rightChild(NULL), parent(NULL){}

	//����<=��>
	bool operator<=(HuffmanNode& R) { return data <= R.data; }
	bool operator>(HuffmanNode& R) { return data > R.data; }

};

typedef struct HuffmanTableNode
{
	char c;
	string code;
}HuffmanTableNode;

template<class T>
class HuffmanTree//Huffman������
{
public:
	HuffmanTree(const T w[], int n);//���캯�����������齨����������
	void GetHuffmanCode() { _GetHuffmanCode(this->root, 0); }
	void _GetHuffmanCode(HuffmanNode<T>* root=this->root, int depth=0);
	void displayTable();
	void encode(string& s);
	~HuffmanTree() { deleteTree(root); }
private:
	HuffmanNode<T>* root;//����
	vector<HuffmanTableNode> HuffmanCodeTable;
	//�ϲ���
	void mergeTree(HuffmanNode<T>& bt1, HuffmanNode<T>& bt2, HuffmanNode<T>*& parent);
	void deleteTree(HuffmanNode<T>* root);
};

template<class T>
void HuffmanTree<T>::encode(string& s)
{
	char* origin = new char [size(s)];
	strcpy_s(origin, size(s), s.c_str());
	unsigned int j = 0;
	for (unsigned int i = 0;i < s.size();++i)
	{
		for (j = 0;j < HuffmanCodeTable.size();++j)
			if (HuffmanCodeTable[j].c == origin[i])
				cout << HuffmanCodeTable[j].code << " ";

		if (j == HuffmanCodeTable.size())
			cout << "����û�и��ַ��ļ�¼" << endl;
	}
			
}

template<class T>
void HuffmanTree<T>::displayTable()
{
	for (vector<HuffmanTableNode>::iterator iter = HuffmanCodeTable.begin();iter != HuffmanCodeTable.end();iter++)//c++11������
		cout << (*iter).c << "  " << (*iter).code << endl;
}

template<class T>
void  HuffmanTree<T>::_GetHuffmanCode(HuffmanNode<T>* root, int depth)
{
	static char code[512];
	HuffmanTableNode temp;//��ʱ
	//�ж������
	if (root->leftChild != NULL)
	{
		code[depth] = '0';
		code[depth + 1] = '\0';
		_GetHuffmanCode(root->leftChild, depth + 1);
	}
	if (root->rightChild != NULL)
	{
		code[depth] = '1';
		code[depth + 1] = '\0';
		_GetHuffmanCode(root->rightChild, depth + 1);
	}
	else
	{
		int codelength = 0;
		for (int j = 0; code[j] != '\0'; j++)
		{
			codelength++;
		}
		temp.c = root->data.c;
		temp.code = code;
		HuffmanCodeTable.push_back(temp);
	}

}

template<class T>
HuffmanTree<T>::HuffmanTree(const T w[], int n)//ͨ�����鹹���������
{
	MinHeap<HuffmanNode<T>> heap;//����װ������С��
	HuffmanNode<T>* parent, 
		first, //��Ÿ�Ȩֵ��С����������
		second, //��Ÿ�Ȩֵ��С����������
		temp;//������ʱ����

	for (int i = 0;i < n;++i)//ɭ�ָ�������ʼ��
	{
		temp.data = w[i];
		heap.Insert(temp);
	}

	for (int i = 0;i < n-1;++i)//��n����㣬������n-1�κϲ�
	{
		heap.GetMin(first);//ѡ�����Ȩֵ��С������
		heap.GetMin(second);//ѡ�����Ȩֵ��С������
		mergeTree(first, second, parent);
		heap.Insert(*parent);
	}
	root = parent;
}

//�ϲ���
template<class T>
void HuffmanTree<T>::mergeTree(HuffmanNode<T>& bt1, HuffmanNode<T>& bt2, HuffmanNode<T>*& parent)
{
	parent = new HuffmanNode<T>;
	parent->leftChild = &bt1;//���������������Ϊbt1
	parent->rightChild = &bt2;//����������Һ�����Ϊbt2
	parent->data = bt1.data + bt2.data;//�¸�����ֵ��Ϊ�������ֵ�ĺ�
	bt1.root->parent = bt2.root->parent = parent;//���������ĸ����Ϊparent
}

//ɾ����rootΪ���ڵ������
template<class T>
void HuffmanTree<T>::deleteTree(HuffmanNode<T>* root)
{
	if (root == NULL)return;
	else
	{
		deleteTree(root->leftChild);
		deleteTree(root->rightChild);//�ݹ�ɾ��
	}
}