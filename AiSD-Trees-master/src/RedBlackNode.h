#pragma once
#include <cassert>
#include <string>

enum class NodeColor { Red, Black };

template<typename T>
class RBNode
{
public:
	RBNode<T> *left, *right;
	T value;
	NodeColor color;
	size_t n;

protected:
	int _print_t(RBNode<T> *tree, int is_left, int offset, int depth, char s[20][255]) const
	{
		char b[20];
		int width = 6;

		if (!tree) return 0;
		if(tree->IsBlack())
			sprintf(b, "(%03dB)", tree->value);
		else
			sprintf(b, "(%03dR)", tree->value);

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
	void Print(RBNode<T> *tree) const
	{
		char s[20][255];
		for (int i = 0; i < 20; i++)
			sprintf(s[i], "%80s", " ");

		_print_t(tree, 0, 0, 0, s);

		for (int i = 0; i < 20; i++)
			printf("%s\n", s[i]);
	}

public:
	RBNode() : left(nullptr), right(nullptr), n(1), value(T()), color(NodeColor::Red)
	{

	}
	RBNode(T val) : left(nullptr), right(nullptr), n(1), value(val), color(NodeColor::Red)
	{

	}
	void Print()
	{
		Print(this);
	}

	inline bool IsLeaf() const
	{
		return left == nullptr && right == nullptr;
	}
	inline bool IsBlack() const
	{
		return color == NodeColor::Black;
	}
	inline bool IsRed() const
	{
		return color == NodeColor::Red;
	}
	/*RBNode<T> *GetGrandparent()
	{
		if (parent == nullptr)
			return nullptr;
		else
			return parent->parent;
	}
	RBNode<T> *GetUncle()
	{
		RBNode<T> *grandpa = GetGrandparent();
		if (grandpa == nullptr)
			return nullptr;
		if (parent == grandpa->left)
			return grandpa->right;
		else
			return grandpa->left;
	}*/


};



