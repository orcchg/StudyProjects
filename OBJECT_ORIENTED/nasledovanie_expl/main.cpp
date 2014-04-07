#include <iostream>
#include <conio.h>
using std::cout;
using std::endl;

class Domestic
{
	private:
		int itsAge;
	
	public:
		Domestic():itsAge(1) {}
		virtual ~Domestic() {}
		
		void Move() const 
		{
			cout << "Domestic moves\n";
		}
		
		virtual void Speak() const
		{
			cout << "Domestic speaks\n";
		}
};

class Dog : public Domestic
{
	public:
		Dog() {}
		virtual ~Dog() {}
		
		void WagTail() const
		{
			cout << "Dog wagging tail\n";
		}
		
		void Speak() const
		{
			cout << "Woof!\n";
		}
		
		void Move() const
		{
			cout << "Dog running\n";
		}
};

class Cat : public Domestic
{
	public:
		Cat() {}
		virtual ~Cat() {}
		
		void Jump() const
		{
			cout << "Cats jumps\n";
		}
		
		void Speak() const
		{
			cout << "Meow!\n";
		}
		
		void Move() const
		{
			cout << "Cat walks\n";
		}
};


int main()
{
	Domestic* pDom = new Domestic();
	pDom->Speak();
	pDom->Move();
	
	Dog* ptrDog = new Dog();
	ptrDog->Move();
	ptrDog->Speak();
	ptrDog->WagTail();
	
	Domestic* pDog = new Dog;
	pDog->Move(); // NOT VIRTUAL
	pDog->Speak();
//	pDog->WagTail();

	Domestic* pCat = new Cat;
//	pCat->Jump();
	pCat->Move(); // NOT VIRTUAL
	pCat->Speak();

	Cat* ptrCat = new Cat();
	ptrCat->Move();
	ptrCat->Jump();

	_getch();
	return 0;
}