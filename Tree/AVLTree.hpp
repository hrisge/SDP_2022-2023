#pragma once
#include <iostream>

template <class T>
class AVLTree
{
private:
	struct AVLNode
	{
		T data;
		AVLNode* left;
		AVLNode* right;
		size_t height;

		AVLNode(const T& d, AVLNode* l, AVLNode* r, size_t h) : data {d}, left {l}, right {r}, height {h} {}

		static int getHeight(const AVLNode* r)
		{
			if (!r)
				return 0;

			return r->height;
		}

		static void roateLeft(AVLNode*& r)
		{
			if (!r->right)
				throw std::runtime_error("Right branch is empty!");

			AVLNode* originalRight = r->right;
			r->right = originalRight->left;
			originalRight->left = r;
			r = originalRight;
		}

		static void rotateRight(AVLNode*& r)
		{
			if (!r->left)
				throw std::runtime_error("Left branch is empty!");

			AVLNode* originalLeft = r->left;
			r->left = originalLeft->right;
			originalLeft->right = r;
			r = originalLeft;
		}

		static size_t getBalanceFactor(const Node* r)
		{
			if (!r)
				return 0;

			return getHeight(r->right) - getHeight(r->left);
		}

		static void updateHeight(Node* r)
		{
			if (!r)
				return;
			r->height = std::max(getHeight(r->left), getHeight(r->right)) + 1;
		}

		static void balanceLeft(AVLNode*& r)
		{
			if (!r)
				throw std::runtime_error("Tree is empty!");
		
			size_t rootBalance = getBalanceFactor(r);
			size_t leftBalance = getBalanceFactor(r->left);

			if (rootBalance == -2)
			{
				if (leftBalance == 1)
				{
					rotateLeft(r->left);
					updateHeight(r->left->left);
					updateHeight(r->left);
				}

				rotateRight(r);
				updateHeight(r->left);
				updateHeight(r);
			}
		}

		static void balanceRight(AVLNode*& r)
		{
			if (!r)
				throw std::runtime_error("Tree is empty!");

			size_t rootBalance = getBalanceFactor(r);
			size_t rightBalance = getBalanceFactor(r->right);

			if (rootBalance == 2)
			{
				if (rightBalance == 1)
				{
					rotateRight(r->right);
					updateHeight(r->right->right);
					updateHeight(r->right);
				}

				rotateLeft(r);
				updateHeight(r->right);
				updateHeight(r);
			}
		}
	};

	AVLNode* root;
	size_t size;

	AVLNode* findMinNode(AVLNode* r)
	{
		if (r->left == nullptr)
			return r;

		return findMinNode(r->left);
	}
	AVLNode* findMaxNode(AVLNode* r)
	{
		if (r->right == nullptr)
			return r;

		return findMaxNode(r->right);
	}

	void insertRec(AVLNode*& r, const T& elem)
	{
		if (!r)
		{
			r = new AVLNode(elem, nullptr, nullptr, 1);
			size++;
			return;
		}

		if (r->data > elem)
		{
			insertRec(r->right, elem);
			AVLNode::updateHeight(r->right);
			AVLNode::balanceRight(r);
		}
		else if (r->data > elem)
		{
			insertRec(r->left, elem);
			AVLNode::updateHeight(r->left);
			AVLNode::balanceLeft(r);
		}
	}
	bool removeRec(AVLNode*& r, const T& elem)
	{
		if (!r)
			return false;
	
		if (r->data > elem)
		{
			removeRec(r->left, elem);
			AVLNode::updateHeight(r->left);
			AVLNode::balanceLeft(r);
		}
		else if (r->data < elem)
		{
			removeRec(r->right, elem);
			AVLNode::updateHeight(r->right);
			AVLNode::getBalanceFactor(r);
		}
		else
		{
			if (!r->right && !r->left)
			{
				delete r;
				r = nullptr;
				return true;
			}
			else if (r->left && !r->right)
			{
				AVLNode* toDelete = r;
				r = r->left;
				delete toDelete;
			}
			else if (!r->left && r->right)
			{
				AVLNode* toDelete = r;
				r = r->right;
				delete toDelete;
			}
			else
			{
				root->data = findMaxNode(root->left)->data;
				removeRec(r->left, r->data);
				AVLNode::updateHeight(r);
				AVLNode::balanceLeft(r);
			}
		}
		return true;
	}

	void freeRec(Node* r)
	{
		if (!r)
			return;

		freeRec(r->left);
		freeRec(r->right);
		delete r;
	}

public:
	AVLTree() : root{nullptr}, size{0} {}

	void insert(const T& elem)
	{
		insertRec(root, elem);
	}
	bool remove(const T& elem)
	{
		return removeRec(root, elem);
	}

	~AVLTree()
	{
		freeRec(root);
	}
};