#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

template<typename T>
class Node
{
private:
	int _print_t(Node<T> *tree, int is_left, int offset, int depth, char s[20][255]) const
	{
		char b[20];
		int width = 5;

		if (!tree) return 0;

		sprintf(b, "(%03d)", tree->value);

		int left = _print_t(tree->left, 1, offset, depth + 1, s);
		int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);
		for (int i = 0; i < width; i++)
			s[2 * depth][offset + left + i] = b[i];

		if (depth && is_left) {

			for (int i = 0; i < width + right; i++)
				s[2 * depth - 1][offset + left + width / 2 + i] = '-';

			s[2 * depth - 1][offset + left + width / 2] = '+';
			s[2 * depth - 1][offset + left + width + right + width / 2] = '+';

		}
		else if (depth && !is_left) {

			for (int i = 0; i < left + width; i++)
				s[2 * depth - 1][offset - width / 2 + i] = '-';

			s[2 * depth - 1][offset + left + width / 2] = '+';
			s[2 * depth - 1][offset - width / 2 - 1] = '+';
		}


		return left + width + right;
	}
	void Print(Node<T> *tree) const
	{
		char s[20][255];
		for (int i = 0; i < 20; i++)
			sprintf(s[i], "%80s", " ");

		_print_t(tree, 0, 0, 0, s);

		for (int i = 0; i < 20; i++)
			printf("%s\n", s[i]);
	}
public:
	T value;
	Node<T> *left;
	Node<T> *right;
	Node<T> *parent;

	Node() : left(nullptr), right(nullptr), parent(nullptr), value(T())
	{
	}

	Node(T val, Node<T> *par = nullptr) : left(nullptr), parent(par), right(nullptr), value(val)
	{

	}

	void SetLeft(Node<T> *node)
	{
		assert(node != nullptr);
		left = node;
		node->parent = this;
	}
	void SetRight(Node<T> *node)
	{
		assert(node != nullptr);
		right = node;
		node->parent = this;
	}

	size_t GetHeight() const
	{
		unsigned leftSubTree = left != nullptr ? left->GetHeight() : 0;
		unsigned rightSubTree = right != nullptr ? right->GetHeight() : 0;
		return 1 + std::max(leftSubTree, rightSubTree);
	}
	size_t GetCount() const
	{
		unsigned leftSubTree = left != nullptr ? left->GetCount() : 0;
		unsigned rightSubTree = right != nullptr ? right->GetCount() : 0;
		return 1 + leftSubTree + rightSubTree;
	}

	inline bool IsLeaf() const
	{
		return left == nullptr && right == nullptr;
	}

	inline bool IsLeftChild() const
	{
		return parent->left == this;
	}
	inline bool IsRightChild() const
	{
		return parent->right == this;
	}

	void SetFrom(const Node<T> *src)
	{
		assert(src != nullptr);
		left = src->left;
		right = src->right;
		parent = src->parent;
		value = src->value;
	}	

	void Print()
	{
		Print(this);
	}
};
