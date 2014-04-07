// Added ::C for Clang 2.9

#include <cassert>
#include <iostream>
#include <vector>

/* Policies declaration */
template <typename T> class DefaultStoragePolicy;
template <typename T> class ArrayStoragePolicy;

template <typename T, template <typename U> class StoragePolicy>
  class NoCopyOwnershipPolicy;
template <typename T, template <typename U> class StoragePolicy>
  class RefCounterOwnershipPolicy;
template <typename T, template <typename U> class StoragePolicy>
  class RefListedOwnershipPolicy;
template <typename T, template <typename U> class StoragePolicy>
  class ChangeOwnerCopyingOwnershipPolicy;

  
/* Smart pointer implementation */
template <typename T,
  template <typename U> class StoragePolicy = DefaultStoragePolicy,
  template <typename, template <typename> class StoragePolicy>
  class OwnershipPolicy = NoCopyOwnershipPolicy>
class SmartPointer {
public:
  typedef T StoredType;
  typedef T* PointerType;
  typedef T& ReferenceType;

  SmartPointer() {}

  explicit SmartPointer(PointerType pointer) : m_pointer(pointer) {}

  SmartPointer(SmartPointer& other) {
    m_pointer = 0;
    m_ownership_policy.Assign(*this, other);
  }

  SmartPointer& operator = (const SmartPointer& other) {
    if (m_pointer != other.m_pointer) {
      m_ownership_policy.Assign(*this, other);
    }
    return *this;
  }

  // Ambigious casting to prevent delete:
  operator StoredType* () {
    return m_pointer;
  }

  operator void* () {
    return m_pointer;
  }

  // Comparsion operators:
  bool operator ! () const {  // For cases "if (!sp) ..."
    return m_pointer == 0;
  }

  inline friend bool operator == (const SmartPointer& lhs, const SmartPointer& rhs) {
    return lhs.m_pointer == rhs.m_pointer;
  }

  inline friend bool operator == (const SmartPointer& lhs, const StoredType* rhs) {
    return lhs.m_pointer == rhs;
  }

  inline friend bool operator == (const StoredType* lhs, const SmartPointer& rhs) {
    return lhs == rhs.m_pointer;
  }

  inline friend bool operator != (const SmartPointer& lhs, const SmartPointer& rhs) {
    return lhs.m_pointer != rhs.m_pointer;
  }

  inline friend bool operator != (const SmartPointer& lhs, const StoredType* rhs) {
    return lhs.m_pointer != rhs;
  }

  inline friend bool operator != (const StoredType* lhs, const SmartPointer& rhs) {
    return lhs != rhs.m_pointer;
  }

  // And template comparsion operators for cases like:
  //
  // SmartPointer<Base> sp;
  // Derived* p;
  // ...
  // if (sp == p) {}
  template <typename R>
  inline friend bool operator == (const SmartPointer& lhs, const R* rhs) {
    return lhs.m_pointer == rhs;
  }

  template <typename R>
  inline friend bool operator == (const R* lhs, const SmartPointer& rhs) {
    return lhs == rhs.m_pointer;
  }

  template <typename R>
  inline friend bool operator != (const SmartPointer& lhs, const R* rhs) {
    return lhs.m_pointer != rhs;
  }

  template <typename R>
  inline friend bool operator != (const R* lhs, const SmartPointer& rhs) {
    return lhs != rhs.m_pointer;
  }

  ~SmartPointer() {
    m_ownership_policy.Release(*this);
  }

  ReferenceType operator*() const {
    return *m_pointer;
  }

  PointerType operator->() const {
    return m_pointer;
  }

  friend PointerType GetImplPtr(SmartPointer& sp) {
    return sp.m_pointer;
  }

  friend void SetImplPtr(SmartPointer& dst, SmartPointer& src) {
    dst.m_pointer = src.m_pointer;
  }

  friend void SetImplPtr(SmartPointer& sp, StoredType* ptr) {
    sp.m_pointer = ptr;
  }

  friend OwnershipPolicy<T, StoragePolicy>& GetImplOwn(SmartPointer& sp) {
    return sp.m_ownership_policy;
  }

private:
  StoredType* m_pointer;
  OwnershipPolicy<T, StoragePolicy> m_ownership_policy;
};


/* Storage policies */
template <typename T>
class DefaultStoragePolicy {
 public:
  static void Delete(T* ptr) {
    delete ptr;
  }
};

template <typename T>
class ArrayStoragePolicy {
 public:
  static void Delete(T* ptr) {
    delete[] ptr;
  }
};


/* Ownership policies */
/// NoCopy - forbits copying of an object refenced by smart pointer
template <typename T, template <typename U> class StoragePolicy>
class NoCopyOwnershipPolicy {
 public:
  // Assign is not defined because it is prohibited in this Policy.
  void Assign(
      SmartPointer<T, StoragePolicy, ::NoCopyOwnershipPolicy>& dst,
      SmartPointer<T, StoragePolicy, ::NoCopyOwnershipPolicy>& src
      );

  void Release(SmartPointer<T, StoragePolicy, ::NoCopyOwnershipPolicy>& smart_ptr) {
    StoragePolicy<T>::Delete(GetImplPtr(smart_ptr));
  }
};


/// RefCounter - counting of references to the object
template <typename T, template <typename U> class StoragePolicy>
class RefCounterOwnershipPolicy {
 private:
  unsigned int* counter_;
 public:
  RefCounterOwnershipPolicy() : counter_(new unsigned int(1)) {}

  void Assign(
      SmartPointer<T, StoragePolicy, ::RefCounterOwnershipPolicy>& dst,
      SmartPointer<T, StoragePolicy, ::RefCounterOwnershipPolicy>& src
      ) {
    SetImplPtr(dst, src);
    ++*(GetImplOwn(src).counter_);
    delete GetImplOwn(dst).counter_;
    GetImplOwn(dst).counter_ = GetImplOwn(src).counter_;
  }

  void Release(SmartPointer<T, StoragePolicy, ::RefCounterOwnershipPolicy>& smart_ptr) {
    if (--*(GetImplOwn(smart_ptr).counter_) == 0) {
      StoragePolicy<T>::Delete(GetImplPtr(smart_ptr));
      delete counter_;
    }
  }
};


/// RefListed - adding references to the object into double-linked list
template <typename T, template <typename U> class StoragePolicy>
class RefListedOwnershipPolicy {
 private:
  RefListedOwnershipPolicy<T, StoragePolicy> *prev_, *next_;
 public:
  RefListedOwnershipPolicy() : prev_(0), next_(0) {}

  /* Assign implementation */
  void Assign(
      SmartPointer<T, StoragePolicy, ::RefListedOwnershipPolicy>& dst,
      SmartPointer<T, StoragePolicy, ::RefListedOwnershipPolicy>& src
      ) {
    RefListedOwnershipPolicy<T, StoragePolicy> *last_ptr =
        &(GetImplOwn(src));

    while (last_ptr->next_ != 0) {
      last_ptr = last_ptr->next_;
    }

    last_ptr->next_ = this;

    if (prev_ != 0) {
      prev_->next_ = next_;
    }

    if (next_ != 0) {
      next_->prev_ = prev_;
    }

    prev_ = last_ptr;
    next_ = 0;
    SetImplPtr(dst, src);
  }
  /* end assign implementation */

  /* Release implementation */
  void Release(SmartPointer<T, StoragePolicy, ::RefListedOwnershipPolicy>& smart_ptr) {
    RefListedOwnershipPolicy<T, StoragePolicy> *own_ptr =
        &GetImplOwn(smart_ptr);

    if (own_ptr->prev_ == 0 && own_ptr->next_ == 0) {
      StoragePolicy<T>::Delete(GetImplPtr(smart_ptr));
    }

    if (own_ptr->prev_ != 0) {
      own_ptr->prev_->next_ = own_ptr->next_;
    }

    if (own_ptr->next_ != 0) {
      own_ptr->next_->prev_ = own_ptr->prev_;
    }
  }
  /* end release implementation */
};


/// ChangeOwner - a la std::auto_ptr
template <typename T, template <typename U> class StoragePolicy>
class ChangeOwnerCopyingOwnershipPolicy {
 public:
  void Assign(
      SmartPointer<T, StoragePolicy, ::ChangeOwnerCopyingOwnershipPolicy>& dst,
      SmartPointer<T, StoragePolicy, ::ChangeOwnerCopyingOwnershipPolicy>& src
      ) {
    StoragePolicy<T>::Delete(GetImplPtr(dst));
    SetImplPtr(dst, src);
    SetImplPtr(src, 0);
  }

  void Release(SmartPointer<T, StoragePolicy, ::ChangeOwnerCopyingOwnershipPolicy>& smart_ptr) {
    StoragePolicy<T>::Delete(GetImplPtr(smart_ptr));
  }
};


///
const int CONSTANT = 10000;

/* Demo */
int main() {
  // NoCopyOwnershipPolicy:
  std::cout << "Testing NoCopyOwnershipPolicy...";
  {
    int *my_int = new int(35);
    SmartPointer<int> sp1(new int(15));
    SmartPointer<int> sp2(my_int);
    assert(*sp1 == 15);
    assert(*sp2 == *my_int);
    assert(sp1 != sp2);
  }
  std::cout << "done" << std::endl;

  // RefCounterOwnershipPolicy:
  std::cout << "Testing RefCounterOwnershipPolicy...";
  {
    SmartPointer<int,
        DefaultStoragePolicy,
        RefCounterOwnershipPolicy> sp1(new int(15));
    SmartPointer<int,
        DefaultStoragePolicy,
        RefCounterOwnershipPolicy> sp2(sp1);
    assert(*sp1 == 15);
    assert(sp1 == sp2);
    std::vector<SmartPointer<int, DefaultStoragePolicy, RefCounterOwnershipPolicy>* > my_vec;
    for (int i = 0; i < CONSTANT; ++i) {
      my_vec.push_back(new SmartPointer<int, DefaultStoragePolicy,
          RefCounterOwnershipPolicy>(new int(i)));
    }
    for (int i = 0; i < CONSTANT; ++i) {
      delete my_vec[i];
    }
  }
  std::cout << "done" << std::endl;

  // RefListedOwnershipPolicy:
  std::cout << "Testing RefListedOwnershipPolicy...";
  {
    SmartPointer<int,
        DefaultStoragePolicy,
        RefListedOwnershipPolicy> sp1(new int(15));
    SmartPointer<int,
        DefaultStoragePolicy,
        RefListedOwnershipPolicy> sp2(sp1);
    assert(*sp1 == 15);
    assert(sp1 == sp2);
    std::vector<SmartPointer<int, DefaultStoragePolicy, RefListedOwnershipPolicy>* > my_vec;
    for (int i = 0; i < CONSTANT; ++i) {
      my_vec.push_back(new SmartPointer<int, DefaultStoragePolicy,
          RefListedOwnershipPolicy>(new int(i)));
    }
    for (int i = 0; i < CONSTANT; ++i) {
      delete my_vec[i];
    }
  }
  std::cout << "done" << std::endl;

  // ChangeOwnerCopyingOwnershipPolicy
  std::cout << "Testing ChangeOwnerCopyingOwnershipPolicy...";
  {
    SmartPointer<int,
        DefaultStoragePolicy,
        ChangeOwnerCopyingOwnershipPolicy> sp1(new int(15));
    SmartPointer<int,
        DefaultStoragePolicy,
        ChangeOwnerCopyingOwnershipPolicy> sp2(sp1);
    assert(sp2 != sp1);
    assert(!sp1);
  }
  std::cout << "done" << std::endl;
  std::cout << "All tests successfully passed." << std::endl;
  return 0;
}
