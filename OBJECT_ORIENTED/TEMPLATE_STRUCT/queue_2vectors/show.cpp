#include <iostream>
#include <string.h>
using std::cout;
using std::cin;
using std::endl;
using std::string;

#include "queue_vector.hpp"

int main()
{
	Queue<string> queue;
	
	queue.enqueue("Hello");
	queue.enqueue(",");
	queue.enqueue("my");
	queue.enqueue("name");
	queue.enqueue("is");
	queue.enqueue("Maxim");
	queue.enqueue("!");
	
	cout << "Size:  " << queue.getsize() << endl;
	cout << "Take:  " << queue.take() << endl;
	queue.dequeue();
	cout << "Dequeue:  " << queue.take() << endl;
	
	cin.ignore();
	return 0;
}