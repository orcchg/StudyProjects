#include "list.h"

int main() {
 {
  ilist mylist;

  for (int ix = 0; ix < 10; ++ix) {
    mylist.insert_front(ix);
    ,ylist.insert_end(ix);
  }
  cout << "OK: after \'insert_front()\' and \'insert_end\'\n";
  mylist.display();

  ilist_item* it = mylist.find(8);
  cout << "\nFinding \'8\', got?" << (it ? " yes!\n" : " no!\n");

  mylist.insert(it, 1024);
  cout << "\nInserting \'1024\' after \'8\'\n";
  mylist.display();

  int elem_cnt = mylist.remove(8);
  cout << "\nRemoved " << elem_cnt << " elements with value \'8\'\n";
  mylist.display();

  cout << "\nRemoved 1st element\n";
  mylist.remove_front();
  mylist.display();

  cout << "\nList has been cleaned\n";
  mylist.remove_all();
  mylist.display();
 }
  //---------------------------------------------
 {
  cout << "\n\n\nREMOVE DEMO\n";
  ilist mylist;
  cout << "\nTest 1: elements at end\n";
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.insert_front(2);
  mylist.insert_front(3);
  mylist.insert_front(4);
  mylist.display();

  int elem_cnt = mylist.remove(1);
  cout << "\nRemoved " << elem_cnt << " elements with value \'1\'\n";
  mylist.display();

  mylist.remove_all();
  cout << "\nTest 2: elements at front\n";
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.display();

  elem_cnt = mylist.remove(1);
  cout << "\nRemoved " << elem_cnt << " elements with value \'1\'\n";
  mylist.display();

  mylist.remove_all();
  cout << "\nTest 3: elements are absent\n";
  mylist.insert_front(2);
  mylist.insert_front(3);
  mylist.insert_front(4);
  mylist.display();

  elem_cnt = mylist.remove(1);
  cout << "\nRemoved " << elem_cnt << " elements with value \'1\'\n";
  mylist.display();

  mylist.remove_all();
  cout << "\nTest 4: elements at end and at front\n";
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.insert_front(2);
  mylist.insert_front(3);
  mylist.insert_front(4);
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.insert_front(1);
  mylist.display();

  elem_cnt = mylist.remove(1);
  cout << "\nRemoved " << elem_cnt << " elements with value \'1\'\n";
  mylist.display();
 }
 //----------------------------------------------
 {
  cout << "\n\n\nALGO DEMO\n";
  ilist mylist;

  for (int ix = 0; ix < 10; ++ix) {
    mylist.insert_front(ix);
  }
  mylist.display();
  cout << "\nInverted list\n";
  mylist.reverse();
  mylist.display();

  ilist mylist_too;
  mylist_too.insert_end(0);
  mylist_too.insert_end(1);
  mylist_too.insert_end(2);
  mylist_too.insert_end(3);
  mylist_too.insert_end(4);
  mylist_too.insert_end(5);
  mylist_too.insert_end(6);

  cout << "\n\'mylist_too\':\n";
  mylist_too.display();
  mylist.concat(mylist_too);
  cout << "\n\'mylist'\ after \'concat\' with \'mylist_too\':\n";
  mylist.display();
 }
 //----------------------------------------------
 {
  cout << "\n\n\nCONSTRUCTOR DEMO\n";
  ilist mylist;

  for (int ix = 0; ix < 10; ++ix) {
    mylist.insert_front(ix);
    mylist.insert_end(ix);
  }

  cout << "\nUsage \'init_iter\' and \'next_iter\' to iterate through list\n";
  ilist_item* iter;
  for (iter = mylist.init_iter(); iter; iter = mylist.next_iter()) {
    cout << iter->value() << " ";
  }

  cout << "\nUsage copy constructor\n";
  ilist mylist2(mylist);
  mylist.remove_all();
  for (iter = mylist2.init_iter(); iter; iter = mylist2.next_iter()) {
    cout << iter->value() << " ";
  }

  cout << "\nUsage assignment operator\n";
  mylist = mylist2;
  for (iter = mylist.init_iter(); iter; iter = mylist.next_iter()) {
    cout << iter->value() << " ";
  }
  cout << endl;
 }
  return 0;
}
