#include <conio.h>
#include "class_tree.h"

int main()
{
	Tree<int> tree;
	
	tree.Add(987,12);
	tree.Add(665,5);
	tree.Add(714,3);
	tree.Add(215,10);
	tree.Add(890,7);
	tree.Add(531,11);
	tree.Add(920,6);
	tree.Add(110,9);
	
	cout << "Tree height : " << tree.GetHeight() << endl
	<< "There are " << tree.GetNodesOnLevel(2) << " nodes on 3rd level." << endl;
	
	cout << "Tree element with key " << 7 << " is: " << endl;
	tree.PrintInfo(7);
	
	_getch();
	return 0;
}