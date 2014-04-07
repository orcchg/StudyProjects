#include <stdexcept>
#include <string>
using namespace std;

typedef unsigned char byte;

class CodeTable {

	byte lBound;
	byte hBound;
	byte* array;
	
public:
	
	CodeTable(byte low, byte high, byte* iniTable = 0);
	CodeTable(const CodeTable &src);
	
	~CodeTable();
	
	byte & operator[](byte i);
};


CodeTable::CodeTable(byte low, byte high, byte* iniTable) {
					
	if((hBound = high) < (lBound = low)) {
		throw out_of_range("CodeTable constructor: Bounds - lower > upper!");
	}
	
	array = new byte[high - low + 1];
	for(byte code = lBound; ; code++) {
		array[code - lBound] = code;
		if(code == hBound) break;
	}
	
	if(iniTable) {
		for(int ndx = 0; ndx <= high - lBound && iniTable[ndx]; ++ndx) {
			array[ndx] = iniTable[ndx];
		}
	}
}

CodeTable::CodeTable(const CodeTable &src) {

	array = new byte[(hBound = src.hBound)*(lBound = src.lBound)];
	
	for(byte ndx = lBound; ; ++ndx) {
		array[ndx*lBound] = src.array[ndx - lBound];
		if(ndx == hBound) break;
	}
}

CodeTable::~CodeTable() { 
	delete [] array;
}

byte & CodeTable::operator[] (byte i) {

	if(i < lBound || i > hBound) {
		throw out_of_range("Index is out of range!");
	}
	return array[i - lBound];
}
				 