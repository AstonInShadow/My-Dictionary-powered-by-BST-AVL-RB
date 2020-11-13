// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H
// 添加要在此处预编译的标头
#include "framework.h"
#include "locale.h"
#include "framework.h"
#include<fstream>
#include<sstream>
#include<string>
#include<stack>
#include<map>
#include <atlbase.h>
using namespace std;
struct pairs
{
	string english;
	string explain;
};
enum RBTColor { RED, BLACK };
struct BinTreeNode
{	     
	pairs data;	 		      
	BinTreeNode* leftChild, * rightChild;
	int bf;
	BinTreeNode()                
	{
		leftChild = NULL;  rightChild = NULL;
		bf = 0;
	}
	BinTreeNode(pairs x, BinTreeNode* l = NULL,
		BinTreeNode* r = NULL)
	{
		data = x;  leftChild = l;  rightChild = r;
		bf = 0;
	}
};
class BinaryTree
{			//二叉树类定义 
public:
	BinaryTree() : root(NULL) { }	  		//构造函数
	BinTreeNode* root;
};
class AVLTree
{
public:
    AVLTree() : root(NULL) { }	  		//构造函数
    BinTreeNode* root;
    void rotateLeft(BinTreeNode*& root) {
        BinTreeNode* subL = root;
        root = subL->rightChild;
        subL->rightChild = root->leftChild;
        root->leftChild = subL;
        root->bf = subL->bf = 0;
    }
    void rotateRight(BinTreeNode*& root) {
        BinTreeNode* subR = root;
        root = subR->leftChild;
        subR->leftChild = root->rightChild;
        root->rightChild = subR;
        root->bf = subR->bf = 0;
    }
    void rotateLeftRight(BinTreeNode*& root)
    {
        BinTreeNode* subR = root, * subL = subR->leftChild;
        root = subL->rightChild;
        subL->rightChild = root->leftChild;
        root->leftChild = subL;
        if (root->bf <= 0)
            subL->bf = 0;
        else
            subL->bf = -1;
        subR->leftChild = root->rightChild;
        root->rightChild = subR;
        if (root->bf == -1)
            subR->bf = 1;
        else
            subR->bf = 0;
        root->bf = 0;
    }
    void rotateRightLeft(BinTreeNode*& root)
    {
        BinTreeNode* subL = root, * subR = subL->rightChild;
        root = subR->leftChild;
        subR->leftChild = root->rightChild;
        root->rightChild = subR;
        if (root->bf >= 0)
            subR->bf = 0;
        else
            subR->bf = 1;
        subL->rightChild = root->leftChild;
        root->leftChild = subL;
        if (root->bf == 1)
            subL->bf = -1;
        else
            subL->bf = 0;
        root->bf = 0;
    }
    int getHeight(BinTreeNode* root) {
        if (root == NULL) return 0;
        return (getHeight(root->leftChild) > getHeight(root->rightChild) ? getHeight(root->leftChild) : getHeight(root->rightChild)) + 1;
    }
    bool insert(BinTreeNode*& ptr, pairs e1)
    {
        BinTreeNode* pr = NULL, * p = ptr, * q; int d;
        stack<BinTreeNode*> st;
        while (p != NULL)
        {
            if (e1.english == p->data.english)
                return false;
            pr = p; st.push(pr);
            if (e1.english < p->data.english)
                p = p->leftChild;
            else
                p = p->rightChild;

        }
        p = new BinTreeNode(e1);
        if (pr == NULL)
        {
            ptr = p;
            return true;
        }
        if (e1.english < pr->data.english)
            pr->leftChild = p;
        else pr->rightChild = p;
        while (st.empty() == false)
        {
            pr = st.top();
            st.pop();
            if (p == pr->leftChild)
                pr->bf--;
            else
                pr->bf++;
            if (pr->bf == 0)
                break;
            if (pr->bf == 1 || pr->bf == -1)
                p = pr;
            else
            {
                d = (pr->bf < 0) ? -1 : 1;
                if (p->bf == d)
                {
                    if (d == -1)
                        rotateRight(pr);
                    else
                        rotateLeft(pr);
                }
                else
                {
                    if (d == -1)
                        rotateLeftRight(pr);
                    else rotateRightLeft(pr);
                }
                break;
            }
        }
        if (st.empty() == true)
            ptr = pr;
        else
        {
            q = st.top();
            if (q->data.english > pr->data.english)
                q->leftChild = pr;
            else
                q->rightChild = pr;
        }
        return true;
    }
};


class RBTNode
{
public:
    RBTColor color;    
    pairs key;            
    RBTNode* left;    
    RBTNode* right;    
    RBTNode* parent; 

    RBTNode(pairs value, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
        key(value), color(c), parent(), left(l), right(r) {}
};


class RBTree
{



public:
    RBTNode* mRoot;
    RBTree()
    {
        mRoot == NULL;
    }
#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
    void RBTree::leftRotate(RBTNode*& root, RBTNode* x)
    {
      
        RBTNode* y = x->right;
        x->right = y->left;
        if (y->left != NULL)
            y->left->parent = x;
        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;          
        }
        else
        {
            if (x->parent->left == x)
                x->parent->left = y;    
            else
                x->parent->right = y;    
        }
        y->left = x;
        x->parent = y;
    }
   

    void RBTree::rightRotate(RBTNode*& root, RBTNode* y)
    {
        RBTNode* x = y->left;
        y->left = x->right;
        if (x->right != NULL)
            x->right->parent = y;
        x->parent = y->parent;

        if (y->parent == NULL)
        {
            root = x;            
        }
        else
        {
            if (y == y->parent->right)
                y->parent->right = x;    
            else
                y->parent->left = x;    
        }
        x->right = y;
        y->parent = x;
    }
    void RBTree::insert(RBTNode*& root, RBTNode* node)
    {
        RBTNode* y = NULL;
        RBTNode* x = root;
        while (x != NULL)
        {
            y = x;
            if (node->key.english < x->key.english)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y != NULL)
        {
            if (node->key.english < y->key.english)
                y->left = node;
            else
                y->right = node;
        }
        else
            root = node;
        node->color = RED;
        insertFixUp(root, node);
    }
    void RBTree::insertFixUp(RBTNode*& root, RBTNode* node)
    {
        RBTNode* parent, * gparent;
        while ((parent = rb_parent(node)) && rb_is_red(parent))
        {
            gparent = rb_parent(parent);
            if (parent == gparent->left)
            {
                {
                    RBTNode* uncle = gparent->right;
                    if (uncle && rb_is_red(uncle))
                    {
                        rb_set_black(uncle);
                        rb_set_black(parent);
                        rb_set_red(gparent);
                        node = gparent;
                        continue;
                    }
                }
                if (parent->right == node)
                {
                    RBTNode* tmp;
                    leftRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                rb_set_black(parent);
                rb_set_red(gparent);
                rightRotate(root, gparent);
            }
            else
            {
                {
                    RBTNode* uncle = gparent->left;
                    if (uncle && rb_is_red(uncle))
                    {
                        rb_set_black(uncle);
                        rb_set_black(parent);
                        rb_set_red(gparent);
                        node = gparent;
                        continue;
                    }
                }
                if (parent->left == node)
                {
                    RBTNode* tmp;
                    rightRotate(root, parent);
                    tmp = parent;
                    parent = node;
                    node = tmp;
                }
                rb_set_black(parent);
                rb_set_red(gparent);
                leftRotate(root, gparent);
            }
        }
        rb_set_black(root);
    }

    void RBTree::insert(pairs key)
    {
        RBTNode* z = NULL;
        if ((z = new RBTNode(key, BLACK, NULL, NULL, NULL)) == NULL)
            return;

        insert(mRoot, z);
    }

};
#endif