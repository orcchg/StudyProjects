#include <iostream>
#include <cstring>
#include "BinSearch.h"
#include "InsertSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "QuickSort.h"
#include "DigitSort.h"
#include "IntKey.h"

using namespace std;

template <class Element>
void PrintArray(Element *array, int low, int high) {
	for (int i = low; i <= high; ++i) {
		cout << array[i] << (i < high ? "," : "");
	}
	cout << endl;
}

int main()
{
	int test1[] = {
		0,  4,  5,  6,  9,  12, 19, 20, 29, 32,
		37, 40, 43, 44, 46, 52, 58, 65, 67, 70,
		73, 76, 77, 88 ,89, 0,  0
	};
	int len1 = sizeof(test1)/sizeof(int);
	
	PrintArray<int>(test1, 0, len1 - 3);
	
	cout << BinSearch<int>(test1, 0, len1 - 3, 58) << endl << endl;
	
	Insert<int>(test1, 0, len1 - 3, 10);
	Insert<int>(test1, 0, len1 - 2, 95);
	PrintArray<int>(test1, 0, len1 - 1); cout << endl;
	
	int len2 = 25;
	int* test2 = new int[len2];
	
	int seed = 13;
	for (int i = 0; i < len2; ++i) {
		test2[i] = (seed = (837*seed + 1079) % 2313) % 1000;
	}
	PrintArray<int>(test2, 0, len2 - 1);
	
	InsertSort<int>(test2, 0, len2 - 1);
	PrintArray<int>(test2, 0, len2 - 1);
	
	for (int i = 0; i < len2; ++i) {
		test2[i] = (seed = (837*seed + 1079) % 213) % 100;
	}
	PrintArray<int>(test2, 0, len2 - 1);
	
	BinInsertSort<int>(test2, 0, len2 - 1);
	PrintArray<int>(test2, 0, len2 - 1); cout << endl;
	
	string sTest1[] = {
		"the", "final", "step", "in", "the", "deployment",
		"process", "occurs", "when", "the", "software", "is",
		"installed", "on", "individual", "user", "system.",
		"installation", "consists", "of", "copying", "software",
		"onto", "the", "user\'s", "system", "then", "configuring",
		"the", "user\'s"
	};
	int lenT1 = sizeof(sTest1)/sizeof(string);
	
	string sTest2[] = {
		"system", "to", "support", "that", "software", "you",
		"should", "ensure", "that", "your", "installation",
		"procedure", "does", "not", "overwrite", "existing",
		"jre", "installations", "as", "they", "may", "be",
		"required", "by", "other", "applications"
	};
	int lenT2 = sizeof(sTest2)/sizeof(string);
	
	string *sTest = new string[lenT1 + lenT2];
	
	BinInsertSort<string>(sTest1, 0, lenT1 - 1);
	PrintArray<string>(sTest1, 0, lenT1 - 1); cout << endl;
	BinInsertSort<string>(sTest2, 0, lenT2 - 1);
	PrintArray<string>(sTest2, 0, lenT2 - 1); cout << endl;
	
	Merge<string>(sTest1, 0, lenT1 - 1, sTest2, 0, lenT2 - 1, sTest, 0);
	PrintArray<string>(sTest, 0, lenT1 + lenT2 - 1); cout << endl;
	
	string sMerge[] = {
		"we", "are", "pleased", "to", "announce", "a", "new",
		"release", "of", "hugs98", "an", "interpreter", "and",
		"programming", "environment", "for", "developing",
		"haskell", "programs", "sources", "and", "binaries",
		"are", "freely", "available", "on", "the", "world",
		"wide", "web"
	};
	int lenMerge = sizeof(sMerge)/sizeof(string);
	
	MergeSort<string>(sMerge, 0, lenMerge - 1);
	PrintArray<string>(sMerge, 0, lenMerge - 1); cout << endl;
	
	string sHeap[] = {
		"the", "java", "runtime", "environment", "contains", "the",
		"java", "virtual", "machine", "runtime", "class", "libraries",
		"and", "java", "application", "launcher", "that", "are",
		"necessary", "to", "run", "programs", "written", "in", "the",
		"java", "programming", "language", "it", "is", "not", "a",
		"development", "environment", "and", "does", "not", "contain",
		"development", "tools", "such", "as", "compilers", "or",
		"debuggers", "for", "development", "tools", "see", "the",
		"java", "sdk", "standart", "edition"
	};
	int lenHeap = sizeof(sHeap)/sizeof(string);
	
	HeapSort<string>(sHeap, 0, lenHeap - 1);
	PrintArray<string>(sHeap, 0, lenHeap - 1); cout << endl;
	
	string sQuick[] = {
		"when", "you", "register", "we", "ask", "for", "information",
		"such", "as", "your", "name", "email", "address", "birth", "date",
		"gender", "zip", "code", "occupation", "industry", "and", "personal",
		"interests", "for", "some", "financial", "products", "and",
		"services", "we", "may", "also", "ask", "for", "your", "address",
		"social", "security", "number", "and", "information", "about",
		"your", "assets", "once", "you", "register", "with", "yahoo!", "and",
		"sign", "in", "to", "our", "services", "you", "are", "not",
		"anonymous", "to", "us"
	};
	int lenQuick = sizeof(sQuick)/sizeof(string);
	
	QuickSort<string>(sQuick, 0, lenQuick - 1);
	PrintArray<string>(sQuick, 0, lenQuick - 1); cout << endl;
	
	const int len3 = 100;
	IntKey test3[len3];
	seed = 13;
	for (int i = 0; i < len3; ++i) {
		test3[i] = IntKey(seed = (837*seed + 1079) & 0x7FFFFFFF);
	}
	PrintArray<IntKey>(test3, 0, len3 - 1);
	cout << endl;
	
	DigitSort<IntKey>(test3, 0, len3 - 1);
	PrintArray<IntKey>(test3, 0, len3 - 1);

	cin.ignore();
	return 0;
}
	
	