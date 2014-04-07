#include <stdio.h>
#include <vector>
using std::vector;

#ifndef TEMPLATE_STACK_VECTOR_H

#define TEMPLATE_STACK_VECTOR_H

template <class T>
class Stack
{
	private:
		vector<T> data;
		int next;
		int size;
	
	public:
		Stack();
		~Stack();
		
		void push(T item);
		
		void pop();
		
		int getsize() const;
		
		T& take();
		
		bool empty() const;
};
//------------------------------------------------------

//------------------------------------------------------
template <class T>
Stack<T>::Stack() 
{
	next = 0;
	size = 0;
	data.clear();
}
//------------------------------------------------------

//------------------------------------------------------
template <class T>
Stack<T>::~Stack()
{
	data.clear();
}
//------------------------------------------------------

//------------------------------------------------------
template <class T>
void Stack<T>::push(T item)
{
	data.push_back(item);
	++size;
	++next;
}
//------------------------------------------------------

//------------------------------------------------------
template <class T>
void Stack<T>::pop()
{
	if (data.empty()) {
		printf("\aStack is empty!\n");
	} else {
		data.pop_back();
		--size;
		--next;
	}
}
//------------------------------------------------------

//------------------------------------------------------
template <class T>
int Stack<T>::getsize() const
{
	return data.size();
}
//------------------------------------------------------

//------------------------------------------------------
template <class T>
T& Stack<T>::take()
{
	if (data.empty()) {
		printf("\aStack is empty!\n");
		// ...
	}
	return data.back();
}
//------------------------------------------------------

//------------------------------------------------------
template <class T>
bool Stack<T>::empty() const
{
	return data.empty();
}
//------------------------------------------------------

//------------------------------------------------------

#endif