#include <stdio.h>

#ifndef TEMPLATE_STACK_H

#define TEMPLATE_STACK_H

template <class T>
class Stack
{
	private:
		int size;
		int position; // index of next item
		T* data;
		
		T* Realloc(T* dt);
		
	public:
		Stack(int s);
		~Stack() {
			delete [] data;
		}
		
		void push(T item);
		void pop();
		int getsize() const;
		T& take() const;
		bool empty() const;
};
//--------------------------------------------------

//--------------------------------------------------
template <class T>
Stack<T>::Stack(int s) : 
				size(s), 
				position(0)
{
	data = new T[size];
	for(int i = 0; i < size; ++i) {
		data[i] = 0;
	}
}
//--------------------------------------------------

//--------------------------------------------------		
template <class T>
T* Stack<T>::Realloc(T* dt)
{
	T* data_new = new T[size];
	
	for (int i = 0; i < size; ++i) {
		data_new[i] = data[i];
	}
	delete [] data;
		
	int size_new = size * 2 + 10;	
	T* data = new T[size_new];
	for(int i = 0; i < size_new; ++i) {
		data[i] = 0;
	}
	
	for(int i = 0; i < size; ++i) {
		data[i] = data_new[i];
	}
	delete [] data_new;
	
	size = size_new;
	
	return data;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
void Stack<T>::push(T item)
{
	if (position >= size) {
		data = Realloc(data);
	}
	data[position++] = item;
}
//--------------------------------------------------
		
//--------------------------------------------------
template <class T>
void Stack<T>::pop()
{
	if (position) {
		data[--position] = 0;
	} else {
		printf("\aStack is empty!\n");
	}
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
int Stack<T>::getsize() const
{
	return this->position;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
T& Stack<T>::take() const
{
	if (position) {
		return data[position - 1];
	}
	printf("\aStack is empty!\n");
	return data[0];
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
bool Stack<T>::empty() const
{
	return (position == 0);
}
//--------------------------------------------------

#endif