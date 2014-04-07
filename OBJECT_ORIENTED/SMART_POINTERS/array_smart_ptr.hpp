#ifndef OBJECT_ORIENTED_ARRAY_SMART_PTR_H

#define OBJECT_ORIENTED_ARRAY_SMART_PTR_H

class SmartArrayPointer
{
	public:
		SmartArrayPointer(int* numbers) : numbers_(numbers)
		{}
		~SmartArrayPointer() 
		{ delete [] numbers_; }
		
		int* get() 
		{ return numbers_; }
		
	private:
		int* numbers_;
};
//-------------------------------------------------------------------------

#endif