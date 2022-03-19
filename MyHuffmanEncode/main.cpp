
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
    
    //检查是否包含中文
    do {
        cout << "请输入一段不包含中文的字符串" << endl;
        cin >> s;
    } while (IncludeChinese(s));

    cin >> s;
    int n;
    struct node* arr=countResult(s,n);

    cout << "以下是统计结果" << endl;
    for (int i = 0;i < n;++i)
    {
        cout << arr[i].c << "  " << arr[i].num << endl;
    }

    HuffmanTree<struct node> tree(arr, n);
    tree.GetHuffmanCode();
    cout << "以下是哈夫曼编码表" << endl;
    tree.displayTable();
    cout << endl << "以下是哈夫曼编码" << endl;
    tree.encode(s);


        
	return 0;

}

bool IncludeChinese(string& str)
{
    int i=0;
    char c;
    while (c=str.c_str()[i++])
    {
        if (c == 0) break;  //如果到字符串尾则说明该字符串没有中文字符
        if (c & 0x80)        //如果字符高位为1且下一字符高位也是1则有中文字符
            if (c & 0x80) return 1;
    }
    return 0;
}
