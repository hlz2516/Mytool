#pragma once
#include <iostream>
#include <queue>
using namespace std;
//该树结构及方法参照《数据结构》何钦铭  二叉搜索树

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int n) {
		data = n;
		left = NULL;
		right = NULL;
	}
};

Node* Init_BinTree(int data)
{
	Node* x = new Node(data);
	return x;
}

Node* insert(int data,Node* tree)
{
	if (!tree) {
		Node* x = new Node(data);
		return x;
	}
	if (data < tree->data)
	{
		tree->left = insert(data, tree->left);
	}
	else if (data > tree->data)
	{
		tree->right = insert(data, tree->right);
	}
	return tree;
}

Node* find_max(Node* tree)
{
	if (!tree) return NULL;
	while (tree->right)
		tree = tree->right;	
	return tree;
}

Node* find_min(Node* tree)
{
	if (!tree) return NULL;
	while (tree->left)
		tree = tree->left;
	return tree;
}

Node* remove(int data, Node* tree)
{
	if (!tree) return NULL;
	Node* tmp;
	if (data < tree->data)
		tree->left = remove(data, tree->left);
	else if (data > tree->data)
		tree->right = remove(data, tree->right);
	else {
		if (tree->left && tree->right)
		{
			tmp = find_max(tree->left);
			tree->data = tmp->data;
			tree->left = remove(tree->data, tree->left);
		}
		else {
			tmp = tree;
			if (!tree->left)
				tree = tree->right;
			else if (!tree->right)
				tree = tree->left;
			delete tmp;
		}
	}
	return tree;
}

Node* find(int data, Node* tree)
{
	if (!tree) return NULL;
	Node* tmp;
	while (tree)
	{
		if (data < tree->data)
			tree = tree->left;
		else if (data > tree->data)
			tree = tree->right;
		else {
			tmp = tree;
			return tmp;
		}
	}
	return NULL;
}
int get_height(Node* root)
{
	if (!root)
		return 0;
	int hl = 0, hr = 0, max = 0;
	if (root->left)
		hl = get_height(root->left);
	if (root->right)
		hr = get_height(root->right);
	max = hl > hr ? hl + 1 : hr + 1;
	return max;
}

void pre_order_traversal(Node* tree) {
	if (tree) {
		cout << tree->data << " ";
		pre_order_traversal(tree->left);
		pre_order_traversal(tree->right);
	}
}

void in_order_traversal(Node* tree) {
	if (tree) {
		in_order_traversal(tree->left);
		cout << tree->data << " ";
		in_order_traversal(tree->right);
	}
}

void post_order_traversal(Node* tree) {
	if (tree) {
		post_order_traversal(tree->left);
		post_order_traversal(tree->right); 
		cout << tree->data << " ";
	}
}

void level_order_traversal(Node* root)
{
	Node* tmp = root;
	queue<Node*> Q;
	Q.push(tmp);
	while (!Q.empty())
	{
		if (Q.front()->left)
			Q.push(Q.front()->left);
		if (Q.front()->right)
			Q.push(Q.front()->right);
		cout << Q.front()->data << " ";
		Q.pop();
	}
}

int get_Node_Num(Node* root, int n = 1)  //得到节点个数，n默认为1
{
	if (!root)
		return n;
	else {
		if (root->left)
			n = get_Node_Num(root->left, ++n);
		if (root->right)
			n = get_Node_Num(root->right, ++n);
	}
	return n;
}

int get_leave_num(Node* root, int n = 0)//得到叶节点个数
{
	if (!root)
		return n;
	else {
		if (!root->left && !root->right)
			return ++n;
		if (root->left)
			n = get_leave_num(root->left, n);
		if (root->right)
			n = get_leave_num(root->right, n);
	}
	return n;
}

Node* InitByArray(char* arr, int length, Node* root, int index = 0) {  //用数组生成树
	if (!root)
		return root;
	else {
		if ((index * 2 + 1)<length && arr[index * 2 + 1] != '0')  //说明有左孩子
		{
			root->left = new Node(arr[index * 2 + 1]);
			InitByArray(arr, length, root->left, index * 2 + 1);
			InitByArray(arr, length, root->right, index * 2 + 2);
		}
		if ((index * 2 + 2)<length && arr[index * 2 + 2] != '0') //说明有右孩子
		{
			root->right = new Node(arr[index * 2 + 2]);
			InitByArray(arr, length, root->left, index * 2 + 1);
			InitByArray(arr, length, root->right, index * 2 + 2);
		}
	}
	return root;
}