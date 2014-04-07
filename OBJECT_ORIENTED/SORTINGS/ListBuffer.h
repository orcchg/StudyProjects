#pragma once

#ifndef SORTINGS_LISTBUFFER_H

#define SORTINGS_LISTBUFFER_H

template <class Key>
class ListBuffer {
private:
	Element<Key> *buffer;
	int size;
	int freePtr;
	
public:
	ListBuffer(int n) {
		buffer = new Element<Key>[size = n];
		Clear();
	}
	
	~ListBuffer() {
		delete [] buffer;
	}
	
	void Clear() {
		freePtr = 0;
	}
	
	Element<Key> & operator [] (int i) {
		return buffer[i];
	}
	
	int get() {
		return freePtr++;
	}
};

#endif