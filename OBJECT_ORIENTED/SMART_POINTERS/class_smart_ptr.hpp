#ifndef OBJECT_ORIENTED_CLASS_SMART_PTR_H

#define OBJECT_ORIENTED_CLASS_SMART_PTR_H

class SmartMyClassPointer
{
	public:
		SmartMyClassPointer(MyClass* myClass) : instance_(myClass);
		{}
		~SmartMyClassPointer()
		{ delete instance_; }
		
		MyClass* get()
		{	return instance_; }
		
	private:
		MyClass* instance_;

};
//-------------------------------------------------------------------------

#endif