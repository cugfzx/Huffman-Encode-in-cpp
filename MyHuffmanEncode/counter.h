#pragma once
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

struct node
{
	char c;
	int num;
};

struct node*& countResult(string& s,int& n)
{
	map<char, int> m;

	for (auto& i : s)
	{
		m[i]++;
	}

	n = m.size();
	struct node* arr = new struct node[n];
	int k = 0;

	for (auto& i : m)
	{
		arr[k].c = i.first; 
		arr[k++].num=i.second;
	}
	return arr;
}
