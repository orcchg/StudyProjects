#include <conio.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "stack_TC.hpp"

int main()
{
	Stack<int> stack(1);
	
	stack.push(100);
	stack.push(20);
	stack.push(50);
	stack.push(40);
	stack.push(10);
	
	cout << "Size:  " << stack.getsize() << endl;
	cout << "Take top:  " << stack.take() << endl;
	
	stack.pop();
	cout << "Pop and top:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop and top:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop and top:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop and top:  " << stack.take() << endl;	
	stack.pop();
	cout << "Pop and top:  " << stack.take() << endl;
	
	if (stack.empty()) {
		cout << "EMPTY\n";
	}
	
	stack.push(214);
	stack.push(352);
	stack.push(678);
	stack.push(244);
	stack.push(199);
	
	cout << "Take top:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop and top:  " << stack.take() << endl;
	
	cin.ignore();
	return 0;
}