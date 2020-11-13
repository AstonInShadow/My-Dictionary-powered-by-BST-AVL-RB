
// MFCECDictionaryDlg.h: 头文件
//
#include<iostream>
#include<fstream>
#include <cstring>
#include <vector>
#include <map>
#include <array>
#include <sstream>
#include "MyNode.h"
#pragma once
// CMFCECDictionaryDlg 对话框
class CMFCECDictionaryDlg : public CDialogEx
{
// 构造
public:
	CMFCECDictionaryDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCECDICTIONARY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int BSTtracer= 0;
	vector<Node>M_Buffer;
	CArray<Node, Node&>M_Array;
	vector<Node>::iterator it;
	vector<Node>::iterator bufferit;
	vector<Node>M_ShowBuffer;
	map<string, string>M_Map;
	CEdit M_INBOX;
	CListCtrl M_OUTLIST;
	afx_msg void OnBnClickedCreatdictionary();
	afx_msg void OnBnClickedBstsearch();
	void DataInPut();
	void CreatBST(int len, int pos, BinTreeNode*& p);
	void BSTSearch(BinTreeNode* ptr, string Keys);
	afx_msg void OnEnChangeEditinbox();
	CArray<pairs, pairs&> m_arr;
	CArray<pairs, pairs&> show;
	BinaryTree tree;
	afx_msg void OnBnClickedButtonINOFF();
	void UTFtoASIC(CString& strUTF8);
	afx_msg void OnBnClickedAvlsearch();
	afx_msg void OnBnClickedRbsearch();
	void RBSearch(RBTNode* ptr, string str);
	CButton m_MapOrNot;
	BOOL  m_MapOrN;
	BOOL  m_RouteOrN;
	afx_msg void OnBnClickedCheckmap();
	afx_msg void OnBnClickedCheckROUTE();
	CButton m_RouteorNot;
};
