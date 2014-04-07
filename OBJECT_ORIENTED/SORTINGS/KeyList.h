#pragma once

#ifndef SORTINGS_KEYLIST_H

#define SORTINGS_KEYLIST_H

template <class Key>
class KeyList {
private:
	ListBuffer<Key> *buffer;
	int first;
	int last;
	
public:
	KeyList(ListBuffer<Key> *buf = NULL) : buffer(buf), first(-1), last(-1)
	{}
	
	void Initialize(ListBuffer<Key> *buf) {
		buffer = buf;
	}
	
	void AddKey(const Key & key) {
		int nextElem = buffer->get();
		(*buffer)[nextElem] = Element<Key>(key);
		
		if (first == -1) {
			first = nextElem;
		} else {
			(*buffer)[last].next = nextElem;
		}
		last = nextElem;
	}
	
	int ToArray(Key *array, int from) {
		int ptr = first;
		
		while (ptr != -1) {
			array[from++] = (*buffer)[ptr].value;
			ptr = (*buffer)[ptr].next;
		}
	}
	
	void Clear() {
		first = last = -1;
	}
};

#endif