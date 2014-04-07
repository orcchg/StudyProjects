#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;

#include "deck_TC.hpp"

int main()
{
	Deck<int> deck(1);
	
	deck.add_tail(10);
	deck.add_tail(75);
	deck.add_tail(20);
	deck.add_head(349);
	deck.add_tail(45);
	deck.add_head(921);
	deck.add_head(555);
	deck.add_head(673);
	deck.add_tail(81);
	
	cout << "Size:  " << deck.getsize() << endl;
	cout << "Take Head:  " << deck.take_head() << endl;
	cout << "Take Tail:  " << deck.take_tail() << endl;
	
//	deck.del_head();
//	cout << "Del & Take Head:  " << deck.take_head() << endl;
	deck.del_tail();
	cout << "Del & Take Tail:  " << deck.take_tail() << endl;
//	deck.del_head();
//	cout << "Del & Take Head:  " << deck.take_head() << endl;
	deck.del_tail();
	cout << "Del & Take Tail:  " << deck.take_tail() << endl;
//	deck.del_head();
//	cout << "Del & Take Head:  " << deck.take_head() << endl;
	deck.del_tail();
	cout << "Del & Take Tail:  " << deck.take_tail() << endl;
//	deck.del_head();
//	cout << "Del & Take Head:  " << deck.take_head() << endl;
	deck.del_tail();
	cout << "Del & Take Tail:  " << deck.take_tail() << endl;
	
	if (deck.empty()) {
		cout << "EMPTY\n";
	}
	
/*	deck.add_tail(5);
	deck.add_tail(2);
	deck.add_head(9999);
	deck.add_tail(4);
	deck.add_head(8888);
	deck.add_head(5567);
	deck.add_head(2345);
	deck.add_tail(8);
	
	deck.del_head();
	cout << "Del & Take Head:  " << deck.take_head() << endl;
	deck.del_tail();
	cout << "Del & Take Tail:  " << deck.take_tail() << endl;*/
	
	_getch();
	return 0;
}