
#include <iostream> //stream and string libraries
#include <string>
using namespace std;

template <typename T>
class AVL_Node // basic node class
{
public:
	T data;          // name of student
	AVL_Node *left;  // left child pointer
	AVL_Node *right; // right child pointer
	int height;      // height of each node
};

template <typename T>
class AVL // avl class
{
public:
	AVL_Node<T> *root; // root of tree
	int length;
	AVL() // constructor sets root to null
	{
		root = NULL;
		length = 0;
	}

	int height(AVL_Node<T> *node) // height of a node calculator
	{
		if (node == NULL) // if node is a leaf node
			return -1;
		else
		{
			int lDepth = height(node->left); // compute the height of each subtree
			int rDepth = height(node->right);

			if (lDepth > rDepth) // height of a tree is one more than max of its two subtrees
				return (lDepth + 1);
			else
				return (rDepth + 1);
		}
	}

	int getBalance(AVL_Node<T> *node) // gets balance factor
	{
		if (node == NULL)
			return 0;
		else
			return height(node->left) - height(node->right); // balance factor is the difference between two subtree heights
	}
	// right rotation
	AVL_Node<T> *rrotation(AVL_Node<T> *node)
	{
		AVL_Node<T> *temp = node->left; // performing right rotation
		node->left = temp->right;
		temp->right = node;
		node->height = max(height(node->left), height(node->right)) + 1; // updating height of node
		temp->height = max(height(node->left), node->height) + 1;
		return temp;
	}
	AVL_Node<T> *lrotation(AVL_Node<T> *node) // left rotation
	{
		AVL_Node<T> *temp = node->right; // performing left rotation
		node->right = temp->left;
		temp->left = node;
		node->height = max(height(node->left), height(node->right)) + 1; // updating height of node
		temp->height = max(height(node->right), node->height) + 1;
		return temp;
	}
	AVL_Node<T> *rlrotation(AVL_Node<T> *node) // right left rotation
	{
		node->right = rrotation(node->right); // right rotation on subchild of unbalanced node
		return lrotation(node);               // left rotation unbalanced node
	}
	AVL_Node<T> *lrrotation(AVL_Node<T> *node) // left right rotation
	{
		node->left = lrotation(node->left); // left rotation on subchild of unbalanced node
		return rrotation(node);             // right rotation unbalanced node
	}
	void insert(T val, AVL_Node<T> *(&root)) // inserts value in the node
	{
		if (root == NULL) // node always inserted as a leaf node
		{
			AVL_Node<T> *newnode = new AVL_Node<T>();
			newnode->data = val;
			newnode->height = 0;
			newnode->left = NULL;
			newnode->right = NULL;
			root = newnode;
		}
		else if (val < root->data) // if inserted id is greater than node id
		{
			insert(val, root->left); // recursive call
			if (getBalance(root) == 2)            // checking balance factor
			{
				if (val < root->left->data)
					root = rrotation(root);
				else
					root = lrrotation(root);
			}
		}
		else if (val > root->data) // if inserted id is larger than node id
		{
			insert(val, root->right); // recursive call
			if (getBalance(root) == -2)             // getting balance factor
			{
				if (val > root->right->data)
					root = lrotation(root);
				else
					root = rlrotation(root);
			}
		}
		length++;
		root->height = max(height(root->left), height(root->right)) + 1; // updating height of the inserted node
	}
	void InOrder(AVL_Node<T> *root)
	{
		if (root != NULL)
		{
			InOrder(root->left);
			cout << root->data.event_id<<endl;
			InOrder(root->right);
		}
	}
};