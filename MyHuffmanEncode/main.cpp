
#include "heap.h"
#include "HuffmanTree.h"
#include <iostream>
#include<string>
#include "counter.h"
using namespace std;

bool IncludeChinese(string& str);


int main()
{
	string s;
    
    //����Ƿ��������
    do {
        cout << "������һ�β��������ĵ��ַ���" << endl;
        cin >> s;
    } while (IncludeChinese(s));

    cin >> s;
    int n;
    struct node* arr=countResult(s,n);

    cout << "������ͳ�ƽ��" << endl;
    for (int i = 0;i < n;++i)
    {
        cout << arr[i].c << "  " << arr[i].num << endl;
    }

    HuffmanTree<struct node> tree(arr, n);
    tree.GetHuffmanCode();
    cout << "�����ǹ����������" << endl;
    tree.displayTable();
    cout << endl << "�����ǹ���������" << endl;
    tree.encode(s);


        
	return 0;

}

bool IncludeChinese(string& str)
{
    int i=0;
    char c;
    while (c=str.c_str()[i++])
    {
        if (c == 0) break;  //������ַ���β��˵�����ַ���û�������ַ�
        if (c & 0x80)        //����ַ���λΪ1����һ�ַ���λҲ��1���������ַ�
            if (c & 0x80) return 1;
    }
    return 0;
}
