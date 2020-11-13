#include<iostream>
#include<fstream>
#include <cstring>
#include <vector>
#include <map>
#include <array>
#include <sstream>
using namespace std;
#pragma once
class Node {
public:
	string key;  // ´æ´¢×ÖµäµÄ¼ü
	string val;  // ´æ´¢×ÖµäµÄÖµ
	Node* left;
	Node* right;
public:
	void setKey(string Key)
	{
		this->key = key;
	}
	void setVal(string Val) {
		this->val = val;
	}
	void m_Node(Node m_this, string key, string val) {
		m_this.key = key;
		m_this.val = val;
	};
	Node()
	{
	}
	Node(string k, string v)
	{
		this->key = k;
		this->val = v;
	}
};