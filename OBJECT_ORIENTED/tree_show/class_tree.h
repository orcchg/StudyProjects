#pragma once
#include <iostream>
using std::cout;
using std::endl;

// GENERAL (NOT ONLY BINARY) TREE

template <class T>
class Tree
{
	struct Node
	{
		T item;
		int key;
		Node* son;
		Node* brother;
		Node* first;
		Node* parent;
		
		Node(T i, int k, Node* s = NULL, Node* b = NULL, Node* f = NULL, Node* p = NULL)
		{
			item = i;
			key = k;
			son = s;
			brother = b;
			first = f;
			parent = p;
		}
	};
	
	Node* root;

	public:
	
		Tree()
		{
			root = NULL;
		}
			
		~Tree()
		{
			DeleteSubtree(root);
		}
			
		int GetHeight()
		{
			return GetHeight(root);
		}
			
		int GetNodesOnLevel(int level)
		{
			return GetNodesOnLevel(root, level);
		}
		
		void Add(const T& elem, const int& key)
		{
			Add(root, elem, key);
		}
		
		bool PrintInfo(int key) const;
		
	private:
		void Add(Node*& node, const T& elem, const int& key);
		void DeleteSubtree(Node* node);
		int GetHeight(Node* node) const;
		int GetNodesOnLevel(Node* node, int level) const;
};

template <class T>
void Tree<T>::DeleteSubtree(Node* node)
{
	if (node)
	{
		DeleteSubtree(node->son);
		DeleteSubtree(node->brother);
		delete node;
	}
}

template <class T>
int Tree<T>::GetHeight(Node* node) const
{
	if (node == NULL)
	{
		return 0;
	}
	
	int max = 0;
	for(Node* current = node->son; current; current = current->brother)
	{
		int curHeight = GetHeight(current);
		if (curHeight > max)
		{
			max = curHeight;
		}
	}
	return max + 1;
}

template <class T>
int Tree<T>::GetNodesOnLevel(Node* node, int level) const
{
	if (node == NULL)
	{
		return 0;
	}
	
	if (level <= 0)
	{
		return 0;
	}
	
	return GetNodesOnLevel(node->son, level - 1) +
			(level == 1) + 
		   GetNodesOnLevel(node->brother, level);
}

template <class T>
void Tree<T>::Add(Node*& node, const T& elem, const int& key)
{
	if (node == NULL)
	{
		node = new Node(elem, key);
	}
	else if (key < node->key)
	{
		Add(node->son, elem, key);
	}
	else
	{
		Add(node->brother, elem, key);
	}
}

template <class T>
bool Tree<T>::PrintInfo(int key) const
{
	int level = 1;
	int aux = 0;
	Node* current = this->root;
	current->first = this->root;
	current->parent = NULL;
	
	if (key == current->key)
	{
		cout << "Level: " << level << "  Info: " << current->item << endl;
		return true;
	}
	else
	{
		current = current->son;
		current->first = current;
		current->parent = this->root;
		
		while(current)
		{
			++level;
			int num = GetNodesOnLevel(current, level) - aux;
			
			if (current->son)
			{
				current->first = current->son;
			}
			else
			{
				current->first = NULL;
			}
			
			for(Node* temp = current; temp; temp = temp->brother)
			{
				--num;
				if (key == temp->key)
				{
					cout << "Level: " << level << "  Info: " << temp->item << endl;
					return true;
				}
			}
			
			if (num)
			{
				int aux_num = GetNodesOnLevel(current, level);
				for(Node* temp = current->parent->brother; temp->key > key ; temp = temp->brother)
				{
					if (temp->son && temp->son->key >= key)
					{
						current = temp->son;
						break;
					}
				}
				++aux;
				--level;
				continue;
			}
			else
			{	
				aux = 0;
				current = current->first;
			}
		}
		return false;
	}
}