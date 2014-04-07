#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "array_smart_ptr.hpp"
#include "class_smart_ptr.hpp"

void Bar(MyClass* myClass, int* array, int N) 
{
	throw std::runtime_error;
}

void Foo(int N)
{
	auto_ptr<MyClass> ptr_0(new MyClass());
	SmartMyClassPointer ptr(new MyClass());
	SmartArrayPointer pArr(new int[N]); 
	
	try {
		Bar(ptr.get(), pArr, N);
	} catch (std::runtime_error) {}
}

int main()
{
	return 0;
}