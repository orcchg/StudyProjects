#include "list.h"

//-----------------------------------------------------------------------------
class ilist_item {
public:
  ilist_item(int value, ilist_item* item_to_link_to = 0);
  inline int value() const { return _value; }
  inline ilist_item* next() const { return _next; }

  inline void next(ilist_item* link) { _next = link; }
  inline void value(int new_value) { _value = new_value; }

private:
  int _value;
  ilist_item* _next;
};

ilist_item::ilist_item(int value, ilist_item* item_to_link_to) 
  : _value(value) 
{ 
  if (item_to_link_to) {
    _next = 0;
  } else {
    _next = item_to_link_to->_next;
    item_to_link_to->_next = this;
  }
}

//-----------------------------------------------------------------------------
class ilist {
public:
  ilist() 
  : _at_front(0) 
  , _at_end(0) 
  , _size(0) 
  {}
  ilist(const ilist& rhs);
  ilist& operator = (const ilist& rhs);

  bool operator == (const ilist& rhs);

  inline int size() { return _size; }
  void insert_front(int value);
  void insert_end(int value);
  void insert(ilist_item* ptr, int value);
  void insert_all(const ilist& rhs);

  void remove_front();
  int remove(int value);
  void remove_all();

  ilist_item* find(int value) const;
  void concat(const ilist& rhs);
  void reverse();

  inline ilist_item* front() const { return _at_front; }
  inline ilist_item* init_iter(ilist_item* it) { return _current = it ? it : _at_front; }
  inline ilist_item* next_iter() { ilist_item* next = _current ? _current = _current->next() : _current; return next; }
  void display(ostream& out = cout) const;

private:
  ilist_item* _at_front;
  ilist_item* _at_end;
  int _size;
  ilist_item* _current;

  inline void bump_up_size() { ++_size; }
  inline void bump_down_size() { --_size; }
};

ilist::ilist(const ilist& rhs) 
  : _at_front(0) 
  , _at_end(0) 
{
  insert_all(rhs);
}

ilist& ilist::operator = (const ilist& rhs) {
  if (*this == rhs) {
    return *this;
  }
  remove_all();
  insert_all(rhs);
  return *this;
}

void ilist::insert_front(int value) {
  ilist_item* ptr = new ilist_item(value);
  if (!_at_front) {
    _at_front = _at_end = ptr;
  } else {
    ptr->next(_at_front);
    _at_front = ptr;
  }
  bump_up_size();
}

void ilist::insert_end(int value) {
  if (!_at_end) {
    _at_end = _at_front = new ilist_item(value);
  } else {
    _at_end = new ilist_item(value);
  }
  bump_up_size();
}

void ilist::insert(ilist_item* ptr, int value) {
  if (!ptr) {
    insert_front(value);
  } else {
    bump_up_size();
	new ilist_item(value, ptr);
  }
}

void ilist::insert_all(const ilist& rhs) {
  ilist_item* ptr = rhs._at_front;
  while (ptr) {
    insert_end(ptr->value());
    ptr = ptr->next();
  }
}

void ilist::remove_front() {
  if (_at_front) {
    ilist_item* ptr = _at_front;
    _at_front = _at_front->next();
    if (_current == ptr) {
      _current = _at_front;
    }
    bump_down_size();
    delete ptr;
  }
}

int ilist::remove(int value) {
  ilist_item* plist = _at_front;
  int elem_cnt = 0;

  while (plist && plist->value() == value) {
    plist = plist->next();
    remove_front();
    ++elem_cnt;
  }

  if (!plist) {
    return elem_cnt;
  }

  ilist_item* prev = plist;
  plist = plist->next();

  while (plist) {
    if (plist->value() == value) {
      prev->next(plist->next());
      if (_current == plist) {
        _current = prev->next();
      }
      delete plist;
      ++elen_cnt;
      bump_down_size();
      plist = prev->next();
      if (!plist) {
        _at_end = prev;
        return elem_cnt;
      }
    } else {
      prev = plist;
      plist = plist->next();
    }
  }
  return elem_cnt;
}

void ilist::remove_all() {
  while (_at_front) {
    remove_front();
  }
  _size = 0;
  _at_front = _at_end = 0;
}

ilist_item* ilist::find(int value) const {
  ilist_item* ptr = _at_front;
  while (ptr) {
    if (ptr->value() == value) {
      break;
    }
    ptr = ptr->next();
  }
  return ptr;
}

void ilist::concat(const ilist& rhs) {
  ilist_item* ptr = rhs._at_front;
  while (ptr) {
    insert_end(ptr->value());
    ptr = ptr->next();
  }
}

void ilist::remove() {
  ilist_item* ptr = _at_front;
  ilist_item* prev = 0;
  _at_front = _at_end;
  _at_end = ptr;

  while (ptr != _at_front) {
    ilist_item* temp = ptr->next();
    ptr->next(prev);
    prev = ptr;
    ptr = temp;
  }
  _at_front->next(prev);
}

void ilist::display(ostream& out) {
  out << "\n(" << _size << ") (";
  ilist_item* ptr = _at_front;
  while (ptr) {
    out << ptr->value() << " ";
    ptr = ptr->next();
  }
  out << ")\n";
}

//-----------------------------------------------------------------------------

