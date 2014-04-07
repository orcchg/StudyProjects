#pragma once

#ifndef SORTINGS_ELEMENT_H

#define SORTINGS_ELEMENT_H

template <class Key>
struct Element {
	Key value;
	int next;
	
	Element() {
		next = -1;
	}
	
	Element(const Element<Key> & src) : value(src.value), next(src.next)
	{}
	
	Element(const Key & val, int n = -1) : value(val), next(n)
	{}
	
	Element & operator = (const Element<Key> & src) {
		value = src.value;
		next = src.next;
		return *this;
	}
};

#endif