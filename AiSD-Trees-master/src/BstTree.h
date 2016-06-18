#pragma once
#include <cassert>
#include "Node.h"

template <typename T>
class BstTree
{
protected:
	mutable unsigned balancer;

	Node<T> *MinSubTree(Node<T> *iter) const
	{
		assert(iter != nullptr);
		while (iter->left != nullptr)
		{
			iter = iter->left;
		}
		return iter;
	}
	Node<T> *MaxSubTree(Node<T> *iter) const
	{
		assert(iter != nullptr);
		while (iter->right != nullptr)
		{
			iter = iter->right;
		}
		return iter;
	}
	bool IsValidBSTBackend(T MIN, T MAX, Node<T> *node) const
	{
		if (node == nullptr)
			return true;
		if (node->value > MIN
			&& node->value < MAX
			&& IsValidBSTBackend(MIN, node->value, node->left)
			&& IsValidBSTBackend(node->value, MAX, node->right))
			return true;
		else
			return false;
	}

	void PrintAscendingBackend(Node<T> *node) const
	{
		volatile static int xd = 0;
		if (node == nullptr)
			return;

		PrintAscendingBackend(node->left);
		//std::cout << node->value << ' ';
		xd++;
		PrintAscendingBackend(node->right);


	}

	void ReleaseBackend(Node<T> *node)
	{
		if (node == nullptr)
			return;

		ReleaseBackend(node->left);
		ReleaseBackend(node->right);

		Remove(node);
	}

public:
	Node<T> *root;

	BstTree() : root(nullptr), balancer(0) { }

	void RotateLeft(T val)
	{
		Node<T> *node = find(val);
		if (node != nullptr)
			RotateLeft(node);
	}

	void RotateRigth(T val)
	{
		Node<T> *node = find(val);
		if (node != nullptr)
			RotateRight(node);
	}

	void RotateRigth(Node<T> *lower)
	{
		Node<T> *higher = lower->parent;
		Node<T> *tmp = nullptr;
		if (higher != nullptr && higher->parent != nullptr)
			tmp = higher->parent;
		if (higher != nullptr && higher->left != nullptr)
			lower = higher->left;
		else return;

		higher->left = lower->right;
		if (higher->left != nullptr)
			higher->left->parent = higher;
		lower->right = higher;
		lower->parent = higher->parent;
		higher->parent = lower;
		if (tmp != nullptr)
		{
			if (tmp->left == higher)
				tmp->left = lower;
			else
				tmp->right = lower;
			return;
		}
		else
		{
			if (root != nullptr)
				root = lower;
		}
	}


	void RotateLeft(Node<T> *lower)
	{
		Node<T> *higher = lower->parent;
		if (higher != nullptr && higher->right != nullptr)
			lower = higher->right;
		else
			return;
		Node<T> *tmp = higher->parent;
		higher->right = lower->left;
		if (higher->right != nullptr)
			higher->right->parent = higher;
		lower->left = higher;
		lower->parent = tmp;
		higher->parent = lower;
		if (tmp != nullptr)
		{
			if (tmp->left == higher)
				tmp->left = lower;
			else
				tmp->right = lower;
		}
		else
		{
			if (root != nullptr)
				root = lower;
		}

	}

	void MakeMeList()
	{
		while (root->left != nullptr)
		{
			Node<T> *iter = root;
			while (iter->left != nullptr)
			{
				RotateRigth(iter->left);
				while (iter->left == nullptr)
				{
					if (iter->right != nullptr)
						iter = iter->right;
					else break;
				}
			}
		}
	}

	void Balance()
	{
		MakeMeList();
		int j = 1;
		int z = pow(2, log2(GetCount()));
		for (j; j <= z; j++)
		{
			int i = 1;
			Node<T> *iter = root;
			while (1)
			{
				if (i++ % 2 == 0)
					RotateLeft(iter);
				if (iter->right != nullptr)
					iter = iter->right;
				else break;
			}
		}
		root = root->left;
		Add(root->parent->value);
		delete root->parent;
		root->parent = nullptr;
	}


	inline bool IsEmpty() const
	{
		return root == nullptr;
	}

	void Add(T val)
	{
		if (root == nullptr)
		{
			root = new Node<T>(val);
			return;
		}

		Node<T> *iter = root;
		while (true)
		{
			assert(iter != nullptr);
			if (val < iter->value)
			{
				//append to left sub-tree
				if (iter->left == nullptr)
				{
					iter->left = new Node<T>(val, iter);
					return;
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
					iter->right = new Node<T>(val, iter);
					return;
				}
				else
				{
					iter = iter->right;
				}
			}
			else
			{
				return; //remove duplicates
			}
		}

	}

	Node<T> *Find(T val) const
	{
		if (root == nullptr)
			return nullptr;

		Node<T> *iter = root;
		while (iter != nullptr)
		{
			if (val == iter->value)
				return iter;
			else if (val < iter->value)
			{
				iter = iter->left;
			}
			else
				iter = iter->right;
		}
		return nullptr;

	}

	void Remove(T val)
	{
		auto node = Find(val);
		if (node == nullptr)
			throw exception("Element does not exist in tree");

		Remove(node);
	}

	void Remove(Node<T> *node)
	{
		assert(node != nullptr);

		if (node->IsLeaf())
		{
			//set parent child to null
			if (node != root && node->parent->left == node)
			{
				node->parent->left = nullptr;
				delete node;
			}
			else if (node != root  && node->parent->right == node)
			{
				node->parent->right = nullptr;
				delete node;
			}
			else if (node == root)
			{
				delete node;
				root = nullptr;
			}
			else
				assert(!"STH WRONG");
		}

		//only right child exists so set it as current node
		else if (node->left == nullptr)
		{
			if (node == root)
			{
				root = node->right;
				delete node;
				return;
			}

			Node<T> *parent = node->parent;
			Node<T> *replacement = node->right;
			//set replacement as new child
			if (parent->left == node)
			{
				//we are left son
				parent->SetLeft(replacement);
			}
			else if (parent->right == node)
			{
				//we are right son
				parent->SetRight(replacement);
			}
			else
			{
				assert(!"STH WRONG!");
			}
			delete node;
		}
		//olny left child exists so set it as current node
		else if (node->right == nullptr)
		{
			if (node == root)
			{
				root = root->left;
				delete node;
				return;
			}

			Node<T> *parent = node->parent;
			Node<T> *replacement = node->left;
			//set replacement as new child
			if (parent->left == node)
			{
				//we are left son
				parent->SetLeft(replacement);
			}
			else if (parent->right == node)
			{
				//we are right son
				parent->SetRight(replacement);
			}
			else
			{
				assert(!"STH WRONG!");
			}
			delete node;
		}
		//both children exists, join left max
		else
		{
			Node<T> *replacement = balancer++ % 2 == 0 ? MinSubTree(node->right) : MaxSubTree(node->left);
			node->value = replacement->value;
			Remove(replacement);
		}
	}

	bool IsValid(T MIN, T MAX) const
	{
		return IsValidBSTBackend(MIN, MAX, root);
	}


	inline  void Print() const
	{
		if (root != nullptr)
			root->Print();
		else
			puts("Empty tree\n");
	}

	inline size_t GetHeight() const
	{
		return root != nullptr ? root->GetHeight() : 0;
	}

	inline size_t GetCount() const
	{
		return root != nullptr ? root->GetCount() : 0;
	}

	inline  T MinimumValue() const
	{
		if (root == nullptr)
			throw exception("Tree is empty");

		return MinSubTree(root)->value;
	}

	void PrintAscending() const
	{
		if (IsEmpty())
			puts("Tree is empty");
		else
			PrintAscendingBackend(root);
	}

	inline T Root() const
	{
		if (IsEmpty())
			throw exception("Tree is empty");

		return root->value;
	}

	void Release()
	{
		ReleaseBackend(root);
	}

	~BstTree()
	{
		Release();
	}
};
