#include <stdio.h>

#ifndef TEMPLATE_QUEUE_H

#define TEMPLATE_QUEUE_H

template <class T>
class Queue
{
	private:
		int size;
		int tail;
		int head;
		T* data;
		
		T* Realloc(T* dt);
		
	public:
		Queue(int s);
		~Queue() {
			delete [] data;
		}
		
		void enqueue(T item);
		void dequeue();
		int getsize() const;
		T& take() const;
		bool empty() const;
};
//--------------------------------------------------

//--------------------------------------------------
template <class T>
Queue<T>::Queue(int s) :
				size(s),
				tail(0),
				head(0)
{
	data = new T[size];
	for(int i = 0; i < size; ++i) {
		data[i] = 0;
	}
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
T* Queue<T>::Realloc(T* dt)
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
void Queue<T>::enqueue(T item)
{
	if (tail >= size - 1) {
		data = Realloc(data);
	}
	data[tail++] = item;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
void Queue<T>::dequeue()
{
	if (head != tail) {
		data[head++] = 0;
	} else {
		printf("\aQueue is empty!\n");
	}
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
int Queue<T>::getsize() const
{
	return (tail - head);
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
T& Queue<T>::take() const
{
	if (head != tail) {
		return data[head];
	}
	printf("\aQueue is empty!\n");
	return data[0];	
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
bool Queue<T>::empty() const
{
	return (head == tail);
}
//--------------------------------------------------

#endif