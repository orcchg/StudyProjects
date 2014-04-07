#include <iostream>
using namespace std;

class Base {
private:
  int private_field;

protected:
  double protected_field;

public:
  char public_field;

  Base(int pr = 0, double pro = 0, char pu = 0) 
  : private_field(pr) 
  , protected_field(pro) 
  , public_field(pu) 
  {}

  void show_public() const {
    cout << public_field << endl;
  }

  void show_protected() const {
    cout << protected_field << endl;
  }

  void show_private() const {
    cout << private_field << endl;
  }
};

class Derived_public : public Base {
private:
  int derived_private_field;

public:
  char derived_public_field;

  Derived_public(int pr, char pu)
  : derived_private_field(pr) 
  , derived_public_field(pu) 
  {}
};

class Derived_protected : protected Base {
private:
  int derived_private_field;

public:
  char derived_public_field;

  Derived_protected(int pr, char pu)
  : derived_private_field(pr) 
  , derived_public_field(pu) 
  {}
};

class Derived_private : private Base {
private:
  int derived_private_field;

public:
  char derived_public_field;

  Derived_private(int pr, char pu)
  : derived_private_field(pr) 
  , derived_public_field(pu) 
  {}
};
