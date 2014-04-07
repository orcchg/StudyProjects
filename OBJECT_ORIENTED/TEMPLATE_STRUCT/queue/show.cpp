#include <iostream>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::string;

#include "queue_TC.hpp"

int main()
{
/*	Queue<string> queue(1);
	
	queue.enqueue("Hello");
	queue.enqueue("my");
	queue.enqueue("name");
	queue.enqueue("is");
	queue.enqueue("Maxim!");
	
	cout << "Size:  " << queue.getsize() << endl;
	cout << "Take:  " << queue.take() << endl;
	
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	
	if (queue.empty()) {
		cout << "EMPTY!" << endl;
	}
	
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	
	queue.enqueue("Egor");
	queue.enqueue("Kovarsky");
	queue.enqueue("lives");
	queue.enqueue("with");
	queue.enqueue("me!");
	
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
*/

	Queue<char> queue(1);
	
	queue.enqueue('A');
	queue.enqueue('b');
	queue.enqueue('C');
	queue.enqueue('d');
	queue.enqueue('E');
	
	cout << "Size:  " << queue.getsize() << endl;
	cout << "Take:  " << queue.take() << endl;
	
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	
	if (queue.empty()) {
		cout << "EMPTY!" << endl;
	}
	
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;
	
	queue.enqueue(112);
	queue.enqueue('l');
	queue.enqueue(90);
	queue.enqueue(54);
	queue.enqueue('M');
	
	cout << "Dequeue and top:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue and top:  " << queue.take() << endl;

	cin.ignore();
	return 0;
}