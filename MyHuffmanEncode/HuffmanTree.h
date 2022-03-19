#pragma once
#include "heap.h"
#include <vector>

template<class T>
class HuffmanNode
{
public:
	//树结点定义
	T data;//数据

	//左右子结点指针，双亲结点指针
	HuffmanNode<T> *leftChild, * rightChild, *parent;

	//构造函数
	HuffmanNode():leftChild(NULL),rightChild(NULL),parent(NULL){}
	HuffmanNode(T elem, HuffmanNode* left=NULL, HuffmanNode* right=NULL, HuffmanNode* pr=NULL)
		:data(elem), leftChild(NULL), rightChild(NULL), parent(NULL){}

	//重载<=和>
	bool operator<=(HuffmanNode& R) { return data <= R.data; }
	bool operator>(HuffmanNode& R) { return data > R.data; }

};

typedef struct HuffmanTableNode
{
	char c;
	string code;
}HuffmanTableNode;

template<class T>
class HuffmanTree//Huffman树定义
{
public:
	HuffmanTree(const T w[], int n);//构造函数，根据数组建立哈夫曼树
	void GetHuffmanCode() { _GetHuffmanCode(this->root, 0); }
	void _GetHuffmanCode(HuffmanNode<T>* root=this->root, int depth=0);
	void displayTable();
	void encode(string& s);
	~HuffmanTree() { deleteTree(root); }
private:
	HuffmanNode<T>* root;//树根
	vector<HuffmanTableNode> HuffmanCodeTable;
	//合并树
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
			cout << "出错，没有该字符的记录" << endl;
	}
			
}

template<class T>
void HuffmanTree<T>::displayTable()
{
	for (vector<HuffmanTableNode>::iterator iter = HuffmanCodeTable.begin();iter != HuffmanCodeTable.end();iter++)//c++11新特性
		cout << (*iter).c << "  " << (*iter).code << endl;
}

template<class T>
void  HuffmanTree<T>::_GetHuffmanCode(HuffmanNode<T>* root, int depth)
{
	static char code[512];
	HuffmanTableNode temp;//临时
	//判断左儿子
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
HuffmanTree<T>::HuffmanTree(const T w[], int n)//通过数组构造哈夫曼树
{
	MinHeap<HuffmanNode<T>> heap;//建立装结点的最小堆
	HuffmanNode<T>* parent, 
		first, //存放根权值最小的子树树根
		second, //存放根权值次小的子树树根
		temp;//工作临时变量

	for (int i = 0;i < n;++i)//森林各棵树初始化
	{
		temp.data = w[i];
		heap.Insert(temp);
	}

	for (int i = 0;i < n-1;++i)//有n个结点，所以做n-1次合并
	{
		heap.GetMin(first);//选择根的权值最小的子树
		heap.GetMin(second);//选择根的权值次小的子树
		mergeTree(first, second, parent);
		heap.Insert(*parent);
	}
	root = parent;
}

//合并树
template<class T>
void HuffmanTree<T>::mergeTree(HuffmanNode<T>& bt1, HuffmanNode<T>& bt2, HuffmanNode<T>*& parent)
{
	parent = new HuffmanNode<T>;
	parent->leftChild = &bt1;//新树根结点左孩子设为bt1
	parent->rightChild = &bt2;//新树根结点右孩子设为bt2
	parent->data = bt1.data + bt2.data;//新根结点的值设为两根结点值的和
	bt1.root->parent = bt2.root->parent = parent;//设两子树的父结点为parent
}

//删除以root为根节点的子树
template<class T>
void HuffmanTree<T>::deleteTree(HuffmanNode<T>* root)
{
	if (root == NULL)return;
	else
	{
		deleteTree(root->leftChild);
		deleteTree(root->rightChild);//递归删除
	}
}