#include <stdio.h>

#ifndef TEMPLATE_DECK_H

#define TEMPLATE_DECK_H

template <class T>
class Deck
{
	private:
		int size_tail;
		int size_head;
		int tail;
		int head;
		T* data;
		
		T* Realloc_Head(T* dt);
		T* Realloc_Tail(T* dt);
		
	public:
		Deck(int s);
		~Deck() {
			delete [] data;
		}
		
		void add_head(T item);
		void add_tail(T item);
		void del_head();
		void del_tail();
		int getsize() const;
		T& take_head() const;
		T& take_tail() const;
		bool empty() const;
};
//--------------------------------------------------

//--------------------------------------------------
template <class T>
Deck<T>::Deck(int size) :
				size_tail(size),
				size_head(size),
				tail(0),
				head(0)
{
	data = new T[size];
	for(int i = 0; i < size; ++i) {
		data[i] = 0;
	}
}				
//--------------------------------------------------

#include <cstdlib>
//--------------------------------------------------
template <class T>
T* Deck<T>::Realloc_Tail(T* dt)
{
	size_tail = size_tail * 2 + 10;	
	data = (T*)realloc(data, size_tail*sizeof(T));
	
	return data;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
T* Deck<T>::Realloc_Head(T* dt)
{
	size_head = size_head * 2 + 10;	
	data = (T*)realloc(data, size_head*sizeof(T));
	
	return data;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
void Deck<T>::add_head(T item) {
	
	if (head == 0) {
		data = Realloc_Head(data);
	}
	data[--head] = item;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
void Deck<T>::add_tail(T item) {
	
	if (tail >= size_tail - 1) {
		data = Realloc_Tail(data);
	}
	data[tail++] = item;
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
void Deck<T>::del_head() {
	
	if (head != tail) {
		data[head++] = 0;
	} else {
		printf("\aDeck is empty!\n");
	}
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
void Deck<T>::del_tail() {

	if (head != tail) {
		data[--tail] = 0;
	} else {
		printf("\aDeck is empty!\n");
	}
}
//--------------------------------------------------

#include <math.h>
//--------------------------------------------------
template <class T>
int Deck<T>::getsize() const {

	return fabs(tail - head);
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
T& Deck<T>::take_head() const {

	if (head != tail) {
		return data[head];
	} 
	printf("\aDeck is empty!\n");
	return data[0];
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
T& Deck<T>::take_tail() const {

	if (head != tail) {
		return data[tail - 1];
	}
	printf("\aDeck is empty!\n");
	return data[0];
}
//--------------------------------------------------

//--------------------------------------------------
template <class T>
bool Deck<T>::empty() const {
	return (head == tail);
}
//--------------------------------------------------

#endif