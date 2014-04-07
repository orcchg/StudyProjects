#include <stdio.h>
#include <vector>
using std::vector;

#ifndef TEMPLATE_QUEUE_VECTOR_H

#define TEMPLATE_QUEUE_VECTOR_H

template <class T>
class Queue
{
	private:
		vector<T> first;
		vector<T> second;
		int head;
		int tail;
		
	public:
		Queue();
		~Queue();
		
		void enqueue(T item);
		
		void dequeue();
		
		int getsize() const;
		
		T& take();
		
		bool empty() const;
};
//------------------------------------------

//------------------------------------------
template <class T>
Queue<T>::Queue()
{
	head = 0;
	tail = 0;
	first.clear();
	second.clear();
}
//------------------------------------------

//------------------------------------------
template <class T>
Queue<T>::~Queue()
{
	first.clear();
	second.clear();
}
//------------------------------------------

//------------------------------------------
template <class T>
void Queue<T>::enqueue(T item)
{
	first.push_back(item);
	++tail;
}
//------------------------------------------

//------------------------------------------
template <class T>
void Queue<T>::dequeue()
{
	if (second.empty()) {
		if (first.empty()) {
			printf("\aQueue is empty!\n");
		}
		else
		{
			while(!first.empty()) {
				second.push_back(first.back());
				first.pop_back();
			}
			second.pop_back();
		}
	}
	else
	{
		second.pop_back();
	}
}		
//------------------------------------------

//------------------------------------------
template <class T>
int Queue<T>::getsize() const
{
	return (first.size() + second.size());
}
//------------------------------------------

//------------------------------------------
template <class T>
T& Queue<T>::take()
{
	if (second.empty()) {
		if (first.empty()) {
			printf("\aQueue is empty!\n");
			// ...
		}
		else
		{
			while(!first.empty()) {
				second.push_back(first.back());
				first.pop_back();
			}
			return second.back();
		}
	}
	else
	{
		return second.back();
	}
}
//------------------------------------------

//------------------------------------------
template <class T>
bool Queue<T>::empty() const
{
	return (first.empty() && second.empty());
}
//------------------------------------------

//------------------------------------------

#endif
		