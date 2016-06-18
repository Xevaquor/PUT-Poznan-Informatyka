#pragma once
#include "RedBlackNode.h"

template<typename T>
class RedBlackTree
{
protected:

	RBNode<T> *AddBstStyle(T val)
	{
		if (root == nullptr)
		{
			root = new RBNode<T>(val);
			root->color = NodeColor::Black;
			return root;
		}

		RBNode<T> *iter = root;
		while (true)
		{
			assert(iter != nullptr);
			if (val < iter->value)
			{
				//append to left sub-tree
				if (iter->left == nullptr)
				{
					iter->left = new RBNode<T>(val);
					return iter->left;
				}
				else
				{
					iter = iter->left;
				}
			}
			else if (val > iter->value)
			{
				//append to right sub-tree
				if (iter->right == nullptr)
				{
					iter->right = new RBNode<T>(val);
					return iter->right;
				}
				else
				{
					iter = iter->right;
				}
			}
			else
			{
				return nullptr; //remove duplicates
			}
		}

	}

	/*void AddCase1(RBNode<T> *node)
	{
		assert(node != nullptr);
		if (node->parent == nullptr)
			node->color = NodeColor::Black;
		else
			AddCase2(node);
	}
	void AddCase2(RBNode<T> *node)
	{
		if (node->parent->color == NodeColor::Black)
			return;
		else
			AddCase3(node);
	}
	void AddCase3(RBNode<T> *node)
	{
		RBNode<T> *uncle = node->GetUncle();
		if ((uncle != nullptr) && (uncle->color == NodeColor::Red))
		{
			node->parent->color = NodeColor::Black;
			uncle->color = NodeColor::Black;
			RBNode<T> *grandpa = node->GetGrandparent();
			grandpa->color = NodeColor::Red;
			AddCase1(grandpa);
		}
		else
		{
			AddCase4(node);
		}
	}
	void AddCase4(RBNode<T> *node)
	{
		auto grandpa = node->GetGrandparent();
		if ((node == node->parent->right) &&
			(node->parent == grandpa->left))
		{
			RotateLeft(node);
		}
		else if ((node == node->parent->left) &&
			(node->parent == grandpa->right))
		{
			RotateRight(node);
		}
		AddCase5(node);
	}*/

	size_t CountChildren(RBNode<T> *node)
	{
		if (node == nullptr)
			return 0;
		else
			return node->n;
	}

	bool IsRed(RBNode<T> *node)
	{
		if (node == nullptr)
			return false;
		return node->color == NodeColor::Red;
	}

	//Na podstawie Sedgewick, Wayne
	RBNode<T> *RotateLeft(RBNode<T> *h)
	{
		assert(h != nullptr);
		RBNode<T> *x = h->right;
		h->right = x->left;
		x->left = h;
		x->color = h->color;
		h->color = NodeColor::Red;
		x->n = h->n;
		h->n = 1 + CountChildren(h->left) + CountChildren(h->right);

		return x;
	}


	//Na podstawie Sedgewick, Wayne
	RBNode<T> *RotateRight(RBNode<T> *h)
	{
		assert(h != nullptr);
		RBNode<T> *x = h->left;
		h->left = x->right;
		x->right = h;
		x->color = h->color;
		h->color = NodeColor::Red;
		x->n = h->n;
		h->n = 1 + CountChildren(h->left) + CountChildren(h->right);

		return x;
	}




public:
	RBNode<T> *root;

	RedBlackTree() : root(nullptr)
	{

	}

	inline bool IsEmpty()
	{
		return root == nullptr;
	}

	void Print()
	{
		if (IsEmpty())
			puts("Tree is empty");
		else
			root->Print();
	}

	void Add(T val)
	{
		RBNode<T> * added = AddBstStyle(val);
	//	AddCase1(added);
	}


	void Insert(T val)
	{
		root = Insert(root, val);
		root->color = NodeColor::Black;
	}

	NodeColor ReverseColor(NodeColor c)
	{
		if (c == NodeColor::Red)
			return NodeColor::Black;
		else
			return NodeColor::Red;
	}

	void FlipColors(RBNode<T> *h)
	{
		h->color = ReverseColor(h->color);
		h->left->color = ReverseColor(h->left->color);
		h->right->color = ReverseColor(h->right->color);
	}

	RBNode<T> *Insert(RBNode<T> *h, T val)
	{
		if (h == nullptr)
			return new RBNode<T>(val);

		if (val < h->value)
			h->left = Insert(h->left, val);
		else if (val > h->value)
			h->right = Insert(h->right, val);
		else
			h->value = val;

		if (IsRed(h->right) & !IsRed(h->left)) h = RotateLeft(h);
		if (IsRed(h->left) && IsRed(h->left->left)) h = RotateRight(h);
		if (IsRed(h->left) && IsRed(h->right)) FlipColors(h);

		h->n = CountChildren(h->left) + CountChildren(h->right) + 1;
		return h;
	}

	RBNode<T> *Find(RBNode<T> *h, T val)
	{
		if (h == nullptr)
			return nullptr;

		if (val < h->value)
		{
			return Find(h->left, val);
		}
		else if (val == h->value)
		{
			return h;
		}
		return Find(h->right, val);
	}

	RBNode<T> *Find(T val)
	{
		return Find(root, val);
	}


};
