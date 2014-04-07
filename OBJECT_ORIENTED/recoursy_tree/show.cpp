#include <iostream>
#include <conio.h>
#include "class_rectree.hpp"

using namespace std;

int main()
{
	Tree<int> *tree =
		new Tree<int>(1, 
			new Tree<int>(2, NULL,
			new Tree<int>(3,
				new Tree<int>(5, NULL,
				new Tree<int>(6,
					new Tree<int>(8, NULL, new Tree<int>(9, NULL, new Tree<int>(10))) //8
							 ) // 6
							 ), // 5
			new Tree<int>(4,
				new Tree<int>(7)
						  ) // 4
						 ) // 3
						 ) // 2
					); // 1
					
	cout << "Tree height: " << tree->GetHeight() << endl;
	
	delete tree;
	_getch();
	return 0;
}
			