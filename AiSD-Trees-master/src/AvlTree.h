#pragma once
#include <iostream>
#include <cassert>
#include <algorithm>

template<typename T>
class AvlNode 
{
public:
	AvlNode<T> *left, *right;
	int height;
	T value;

	AvlNode() : left(nullptr), right(nullptr), height(0), value(T())
	{

	}
protected:
	int _print_t(AvlNode<T> *tree, int is_left, int offset, int depth, char s[20][255]) const
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
	void Print(AvlNode<T> *tree) const
	{
		char s[20][255];
		for (int i = 0; i < 20; i++)
			sprintf(s[i], "%80s", " ");

		_print_t(tree, 0, 0, 0, s);

		for (int i = 0; i < 20; i++)
			printf("%s\n", s[i]);
	}
public:
	void Print()
	{
		Print(this);
	}
};

template<typename T>
class AvlTree 
{
protected:	
	AvlNode<T> *MinSubTree(AvlNode<T> *iter) const
	{
		assert(iter != nullptr);
		while (iter->left != nullptr)
		{
			iter = iter->left;
		}
		return iter;
	}
	int RemoveMin(AvlNode<T> * &p)
	{
		int c;
		if (p->left == nullptr)
		{
			c = p->value;
			p = p->right;
			return c;
		}
		else
		{
			c = RemoveMin(p->left);
			return c;
		}
	}
	int BsHeight(AvlNode<T> *p)
	{
		int t;
		if (p == nullptr)
		{
			return -1;
		}
		else
		{
			t = p->height;
			return t;
		}
	}
	void Remove(T x, AvlNode<T> * &p)
	{
		AvlNode<T> * d;
		if (p == nullptr)
		{
			//cout << "Sorry! value not found\n" << endl;
		}
		else if (x < p->value)
		{
			Remove(x, p->left);
		}
		else if (x > p->value)
		{
			Remove(x, p->right);
		}
		else if ((p->left == nullptr) && (p->right == nullptr))
		{
			d = p;
			//free (d);
			p = nullptr;
			//cout << "value deleted successfully\n" << endl;
		}
		else if (p->left == nullptr)
		{
			d = p;
			//free (d);
			p = p->right;
			//cout << "value deleted successfully\n" << endl;
		}
		else if (p->right == nullptr)
		{
			d = p;
			p = p->left;
			//free(d);
			//cout << "value deleted successfully\n" << endl;
		}
		else
		{
			p->value = RemoveMin(p->right);
		}
	}
	void ReleaseBackend(AvlNode<T>* node)
	{
		if (node == nullptr)
			return;
		ReleaseBackend(node->left);
		ReleaseBackend(node->right);
		Remove(node->value);
	}

	AvlNode<T> * srl(AvlNode<T> * &p1)
	{
		AvlNode<T> * p2;
		p2 = p1->left;
		p1->left = p2->right;
		p2->right = p1;
		p1->height = max(BsHeight(p1->left), BsHeight(p1->right)) + 1;
		p2->height = max(BsHeight(p2->left), p1->height) + 1;
		return p2;
	}
	AvlNode<T> * srr(AvlNode<T> * &p1)
	{
		AvlNode<T> * p2;
		p2 = p1->right;
		p1->right = p2->left;
		p2->left = p1;
		p1->height = max(BsHeight(p1->left), BsHeight(p1->right)) + 1;
		p2->height = max(p1->height, BsHeight(p2->right)) + 1;
		return p2;
	}
	AvlNode<T> * drl(AvlNode<T> * &p1)
	{
		p1->left = srr(p1->left);
		return srl(p1);
	}
	AvlNode<T> * drr(AvlNode<T> * &p1)
	{
		p1->right = srl(p1->right);
		return srr(p1);
	}

	void Add(T val, AvlNode<T> *&p)
	{
		if (p == nullptr)
		{
			p = new AvlNode<T>();
			p->value = val;
			p->left = nullptr;
			p->right = nullptr;
			p->height = 0;
			if (p == nullptr)
			{
				cout << "Out of Space\n" << endl;
			}
		}
		else
		{
			if (val < p->value)
			{
				Add(val, p->left);
				if ((BsHeight(p->left) - BsHeight(p->right)) == 2)
				{
					if (val < p->left->value)
					{
						p = srl(p);
					}
					else
					{
						p = drl(p);
					}
				}
			}
			else if (val>p->value)
			{
				Add(val, p->right);
				if ((BsHeight(p->right) - BsHeight(p->left)) == 2)
				{
					if (val > p->right->value)
					{
						p = srr(p);
					}
					else
					{
						p = drr(p);
					}
				}
			}
			else
			{
				//cout << "value Exists\n" << endl;
			}
		}
		int m, n, d;
		m = BsHeight(p->left);
		n = BsHeight(p->right);
		d = max(m, n);
		p->height = d + 1;
	}

	void PrintAscendingBackend(AvlNode<T> *iter)
	{
		if (iter == nullptr)
			return;

		PrintAscendingBackend(iter->left);
		//std::cout << iter->value << ' ';
		volatile static int xd = 0;
		xd++;
		PrintAscendingBackend(iter->right);
	}
public:
	AvlTree() 
	{
		this->avlRoot = nullptr;
	}
	AvlNode<T> *avlRoot;

	inline void Print()
	{
		if (avlRoot == nullptr)
			puts("Empty tree\n");
		else
			avlRoot->Print();
	}
	
	void Add(T val)
	{
		Add(val, avlRoot);
	}

	void Remove(T val)
	{
		Remove(val, avlRoot);
		if (avlRoot != nullptr)
		{
			T tmp = GetRootValue();
			Remove(tmp, avlRoot);
			Add(tmp);
		}
	}

	inline bool IsEmpty() const
	{
		return avlRoot == nullptr;
	}

	inline T GetMinimumValue() const
	{
		if (IsEmpty())
			throw exception("Tree is empty");

		return MinSubTree(avlRoot)->value;
	}

	inline T GetRootValue()
	{
		if (IsEmpty())
			throw exception("Tree is empty");

		return avlRoot->value;
	}

	void PrintAscending()
	{
		if (IsEmpty())
			puts("Tree is empty");
		else
		{
			PrintAscendingBackend(avlRoot);
			putchar('\n');
		}
	}

	void Release()
	{
		ReleaseBackend(avlRoot);
	}

	~AvlTree()
	{
		Release();
	}

};
