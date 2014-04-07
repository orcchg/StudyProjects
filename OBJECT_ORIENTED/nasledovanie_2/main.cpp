#include <iostream>
#include <conio.h>
using std::cout;
using std::endl;

class Ancestor
{
public:
  virtual void  function1 () { cout << "Ancestor::function1()" << endl; }
  void          function2 () { cout << "Ancestor::function2()" << endl; }
};
 
class Descendant : public Ancestor
{
public:
  virtual void  function1 () { cout << "Descendant::function1()" << endl; }
  void          function2 () { cout << "Descendant::function2()" << endl; }
  void			function3 () { cout << "Descendant::function3()" << endl; }
};

int main()
{

Descendant*  pointer      = new Descendant ();
Ancestor*    pointer_copy = new Descendant; //pointer;
 
pointer->function1 ();
pointer->function2 ();
pointer->function3 ();
 
pointer_copy->function1 ();
pointer_copy->function2 ();
//pointer_copy->function3 ();

	_getch();
	return 0;
}