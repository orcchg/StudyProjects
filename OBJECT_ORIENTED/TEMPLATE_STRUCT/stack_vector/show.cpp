#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "stack_vector.hpp"

int main()
{
	Stack<string> stack;
	
	stack.push("Hello");
	stack.push(",");
	stack.push("my");
	stack.push("name");
	stack.push("is");
	stack.push("Maxim");
	stack.push("!");
	
	cout << "Take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
//	stack.pop();
//	cout << "Pop & take:  " << stack.take() << endl;
	
	if (stack.empty()) {
		cout << "EMPTY" << endl;
	}
	
	stack.pop();
	
	stack.push("Show must");
	stack.push("go on");
	stack.push("! ! !");
	
	cout << "Take:  " << stack.take() << endl;
	stack.pop();
	cout << "Pop & take:  " << stack.take() << endl;
	
	cin.ignore();
	return 0;
}