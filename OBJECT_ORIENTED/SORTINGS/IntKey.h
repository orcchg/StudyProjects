#pragma once

#include <iostream>
using namespace std;

#ifndef SORTINGS_INTKEY_H

#define SORTINGS_INTKEY_H

class IntKey {
private:
	friend ostream & operator << (ostream & out, const IntKey & v);
	
	int value;

public:
		IntKey(int v = 0) : value(v) {}
		IntKey(const IntKey & key) : value(key.value) {}
		int getValue() { return value; }
		int length() { return 8; }
		int power() { return 16; }
		int operator [] (int i) const { return (value >> (4*(7 - i))) & 15; }
};

ostream & operator << (ostream & out, const IntKey & v) {
	return out << v.value;
}

#endif