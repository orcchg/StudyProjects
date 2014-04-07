#include <algorithm>
#include <iostream>
#include <functional>
using std::cerr;
using std::endl;
using std::binary_function;

/* Storage policies */
/// T* GetImpl(SmartPointer<T>& smart_ptr) - returns pointer to an object, referenced with smart pointer
/// T*& GetImplRef(SmartPointer<T>& smart_ptr) - returns reference to the native pointer in smart pointer
//-------------------------------------------------------
template <typename T>
class DefaultStoragePolicy {
public:
  typedef T* storage_type;       // the type of the pointee_ object
  typedef T* pointer_type;       // type returned by operator->
  typedef T* init_pointer_type;  // type used to declare OwnershipPolicy type
  typedef T& reference_type;     // type returned by operator*

public:
  DefaultStoragePolicy() : m_pointer(Default()) {}
  DefaultStoragePolicy(const storage_type& rhs) : m_pointer(rhs) {}
  DefaultStoragePolicy(const DefaultStoragePolicy&) : m_pointer(0) {}
  template <class U> DefaultStoragePolicy(const DefaultStoragePolicy<U>&) : m_pointer(0) {}

  pointer_type operator -> () const { return m_pointer; }
  reference_type operator * () const { return *m_pointer; }

  //-------------------------------------------------------
  friend inline pointer_type GetImpl(const DefaultStoragePolicy& smart_ptr) {
    return smart_ptr.m_pointer;
  }
  friend inline const storage_type& GetImplRef(const DefaultStoragePolicy& smart_ptr) {
    return smart_ptr.m_pointer;
  }
  friend inline storage_type& GetImplRef(DefaultStoragePolicy& smart_ptr) {
    return smart_ptr.m_pointer;
  }
  //-------------------------------------------------------
  inline void Swap(DefaultStoragePolicy& rhs) {
    std::swap(m_pointer, rhs.m_pointer);
  }

protected:
  void Destroy() { delete m_pointer; }
  static storage_type Default() { return 0; }  // Default value to initialize the pointer

private:
  storage_type m_pointer;
};

///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------
template <typename T>
class ArrayStoragePolicy {
public:
  typedef T* storage_type;       // the type of the pointee_ object
  typedef T* pointer_type;       // type returned by operator->
  typedef T* init_pointer_type;  // type used to declare OwnershipPolicy type
  typedef T& reference_type;     // type returned by operator*

public:
  ArrayStoragePolicy() : m_pointer(Default()) {}
  ArrayStoragePolicy(const storage_type& rhs) : m_pointer(rhs) {}
  ArrayStoragePolicy(const ArrayStoragePolicy&) : m_pointer(0) {}
  template <class U> ArrayStoragePolicy(const ArrayStoragePolicy<U>&) : m_pointer(0) {}

  pointer_type operator -> () const { return m_pointer; }
  reference_type operator * () const { return *m_pointer; }

  //-------------------------------------------------------
  friend inline pointer_type GetImpl(const ArrayStoragePolicy& smart_ptr) {
    return smart_ptr.m_pointer;
  }
  friend inline const storage_type& GetImplRef(const ArrayStoragePolicy& smart_ptr) {
    return smart_ptr.m_pointer;
  }
  friend inline storage_type& GetImplRef(ArrayStoragePolicy& smart_ptr) {
    return smart_ptr.m_pointer;
  }
  //-------------------------------------------------------
  inline void Swap(ArrayStoragePolicy& rhs) {
    std::swap(m_pointer, rhs.m_pointer);
  }

protected:
  void Destroy() { delete [] m_pointer; }
  static storage_type Default() { return 0; }  // Default value to initialize the pointer

private:
  storage_type m_pointer;
};

//-----------------------------------------------------------------------------

/* Ownership policies */
/// T Clone(const T& rhs) - copies an object stored in smart pointer into free memory area in heap
/// bool Release(const T&) - releases smart pointer referenced to object, user must handle object by himself
///        TRUE - if the last reference to an object has been released, in the other hand - FALSE
//-----------------------------------------------------------------------------
template <typename T>
class NoCopyPolicy {
public:
  NoCopyPolicy() {}
  template <class U> NoCopyPolicy(const NoCopyPolicy<U>&) {}
  static T Clone(const T&) {
    throw NoCopyException();
  }
  static bool Release(const T&) { return true; }
  static void Swap(NoCopyPolicy&) {}

  //-------------------------------------------------------
  class NoCopyException {
  public:
    NoCopyException() { cerr << "Ownership policy disallows copy!" << endl; }
  };
  //-------------------------------------------------------
  enum { destructiveCopy = false };

private:
  NoCopyPolicy(const NoCopyPolicy&);
  NoCopyPolicy& operator = (const NoCopyPolicy&);
};

///////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------
template <typename T>
class RefCountedPolicy {
public:
  RefCountedPolicy() : mp_counter(new unsigned int(1)) {}
  RefCountedPolicy(const RefCountedPolicy& rhs) : mp_counter(rhs.mp_counter) {}

  //-------------------------------------------------------
  inline T Clone(const T& rhs) {
    ++*mp_counter;
    return rhs;
  }
  inline bool Release(const T&) {
    if (!--*mp_counter) {
      delete mp_counter;
      return true;  // last reference to an object has been released
    }
    return false;  // last reference to an object hasn't been released
  }
  //-------------------------------------------------------
  inline void Swap(RefCountedPolicy& rhs) {
    std::swap(mp_counter, rhs.mp_counter);
  }
  enum { destructiveCopy = false };

private:
  unsigned int* mp_counter;
};

///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------
class RefLinkedBase {
public:
  RefLinkedBase() { mp_prev = mp_next = this; }
  RefLinkedBase(const RefLinkedBase& rhs);
  bool Release();
  void Swap(RefLinkedBase& rhs);
  bool Merge(RefLinkedBase& rhs);

  enum { destructiveCopy = false };

private:
  static unsigned int CountPrevCycle(const RefLinkedBase* p_this);
  static unsigned int CountNextCycle(const RefLinkedBase* p_this);
  bool HasPrevNode(const RefLinkedBase* ptr) const;
  bool HasNextNode(const RefLinkedBase* ptr) const;
  
  mutable const RefLinkedBase* mp_prev;
  mutable const RefLinkedBase* mp_next;
};

template <typename T>
class RefLinkedPolicy : public RefLinkedBase {
public:
  RefLinkedPolicy() {}
  template <class U> RefLinkedPolicy(const RefLinkedPolicy<U>& rhs)
  : RefLinkedBase(rhs)
  {}

  //-------------------------------------------------------
  bool Release(const T&) { return RefLinkedBase::Release(); }
  template <class U> bool Merge(RefLinkedPolicy<U>& rhs) {
    return RefLinkedBase::Merge(rhs);
  }
  static T Clone(const T& value){ return value; }
  //-------------------------------------------------------
};

///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------
template <typename T>
class ChangeOwnerCopyPolicy {  // a la std::auto_ptr
public:
  ChangeOwnerCopyPolicy() {}
  template <class U> ChangeOwnerCopyPolicy(const ChangeOwnerCopyPolicy<U>&) {}

  //-------------------------------------------------------
  template <class U>
  static T Clone(U& value) {
    T result(value);
    value = U();
    return result;
  }
  static bool Release(const T&) { return true; }
  static void Swap(ChangeOwnerCopyPolicy&) {}
  //-------------------------------------------------------
  enum { destructiveCopy = true };
};

//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Selects one of two types based upon a boolean constant
// Invocation: Select<flag, T, U>::Result
// where:
// flag is a compile-time boolean constant
// T and U are types
// Result evaluates to T if flag is true, and to U otherwise.
////////////////////////////////////////////////////////////////////////////////
template <bool flag, typename T, typename U>
struct Select {
  typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U> {
  typedef U Result;
};

/* Smart Pointer implementation */
//-----------------------------------------------------------------------------
template <typename T, 
    template <typename> class OwnershipPolicy = NoCopyPolicy,
    template <typename> class StoragePolicy = DefaultStoragePolicy
    >
class SmartPointer
    : public OwnershipPolicy<typename StoragePolicy<T>::init_pointer_type> 
    , public StoragePolicy<T>
{
private:
  /* typedefs */
  typedef StoragePolicy<T> SP;
  typedef OwnershipPolicy<typename StoragePolicy<T>::init_pointer_type> OP;

public:
  typedef typename SP::pointer_type PointerType;
  typedef typename SP::storage_type StoredType;
  typedef typename SP::reference_type ReferenceType;
  
  typedef typename Select<OP::destructiveCopy, SmartPointer, const SmartPointer>::Result CopyArg;

  /* Basic functional */
  SmartPointer() : m_pointer(0) {}

  SmartPointer(CopyArg& rhs)
  : SP(rhs) 
  , OP(rhs) 
  { GetImplRef(*this) = OP::Clone(GetImplRef(rhs)); }

  explicit SmartPointer(T* ptr) : m_pointer(ptr) {
    if (!ptr) {
       throw NullPointerException(); /// Optional
    }
  }
  ~SmartPointer() {
    if (OP::Release(GetImpl(*static_cast<SP*>(this)))) {
      SP::Destroy();
    }
  }
  /* end basic functional */

  /* Copy functional */
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  SmartPointer(const SmartPointer<U, OP1, SP1>& rhs) 
  : SP(rhs) 
  , OP(rhs)
  { GetImplRef(*this) = OP::Clone(GetImplRef(rhs)); }

  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  SmartPointer& operator = (const SmartPointer<U, OP1, SP1>& rhs) {
    SmartPointer temp(rhs);
    temp.Swap(*this);
    return *this;
  }

  void Swap(SmartPointer& rhs) {
    OP::Swap(rhs);
    SP::Swap(rhs);
  }
  /* end copy functional */

  /* Operations: *, ->, !, ... */
  ReferenceType operator * () const { return SP::operator*(); }
  PointerType operator -> () const { return SP::operator->(); }
  bool operator ! () const { return GetImpl(*this) == 0; }  // Allows if (!sp)
  static inline T* GetPointer(const SmartPointer& smart_ptr) { return GetImpl(smart_ptr); }
  /* end operations */

  /* Compare operators: ==, !=, <, >, <=, >= */
  /// equal_to '=='
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool operator == (const SmartPointer<U, OP1, SP1>& rhs) const {
    return GetImpl(*this) == GetImpl(rhs);
  }

  /// not_equal_to '!='
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool operator != (const SmartPointer<U, OP1, SP1>& rhs) const {
    return !(*this == rhs);
  }

  /// less '<'
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool operator < (const SmartPointer<U, OP1, SP1>& rhs) const {
    return GetImpl(*this) < GetImpl(rhs);
  }
  
  /// greater '>'
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool operator > (const SmartPointer<U, OP1, SP1>& rhs) const {
    return GetImpl(rhs) < GetImpl(*this);
  }

  /// less_equal '<='
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool operator <= (const SmartPointer<U, OP1, SP1>& rhs) const {
    return !(GetImpl(rhs) < GetImpl(*this));
  }
  
  /// greater_equal '>='
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool operator >= (const SmartPointer<U, OP1, SP1>& rhs) const {
    return !(GetImpl(*this) < GetImpl(rhs));
  }
  /* end compare operators */

  /* Friends */
  friend inline void Release(SmartPointer& smart_ptr, StoredType& obj) {
    obj = GetImplRef(smart_ptr);
    GetImplRef(smart_ptr) = SP::Default();
  }
  /* end friends */

  /* Advanced functional */
  template <typename U,
      template <typename> class OP1,
      template <typename> class SP1
      >
  bool Merge(const SmartPointer<U, OP1, SP1>& rhs) {
    if (GetImpl(*this) != GetImpl(rhs)) {
      return false;
    }
    return OP::template Merge(rhs);
  }
  
    /* Allows if (sp) */
    private:
      class Tester {
        void operator delete(void*);
      };
      
    public:
      operator Tester*() const {
        if (!m_pointer) {
          return 0;
        }
        static Tester test;
        return &test;
      }
    /* end allows if (sp) */
  /* end advanced functional */

  /* Class exception */
  class NullPointerException {
  public:
    NullPointerException() { cerr << "Smart pointer disallows NULL value!" << endl; }
  };
  /* end class exception */
private:
  StoredType m_pointer;
};

//-----------------------------------------------------------------------------

/* Friends for comparisons between SmartPointer and raw pointer */ 
/// equal_to '=='
template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator == (const SmartPointer<T1, OP1, SP1>& lhs, U* rhs) {
    return GetImpl(lhs) == rhs;
  }
  template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator == (U* lhs, const SmartPointer<T1, OP1, SP1>& rhs) {
    return rhs == lhs;
  }

/// not_equal_to '!='  
template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator != (const SmartPointer<T1, OP1, SP1>& lhs, U* rhs) {
    return !(lhs == rhs);
  }
  template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator != (U* lhs, const SmartPointer<T1, OP1, SP1>& rhs) {
    return rhs != lhs;
  }

/// less '<'  
template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator < (const SmartPointer<T1, OP1, SP1>& lhs, U* rhs) {
    return GetImpl(lhs) < rhs;
  }
  template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator < (U* lhs, const SmartPointer<T1, OP1, SP1>& rhs) {
    return GetImpl(rhs) < lhs;
  }

/// greater '>'
template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator > (const SmartPointer<T1, OP1, SP1>& lhs, U* rhs) {
    return rhs < lhs;
  }
  template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator > (U* lhs, const SmartPointer<T1, OP1, SP1>& rhs) {
    return rhs < lhs;
  }

/// less_equal '<='  
template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator <= (const SmartPointer<T1, OP1, SP1>& lhs, U* rhs) {
    return !(rhs < lhs);
  }
  template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator <= (U* lhs, const SmartPointer<T1, OP1, SP1>& rhs) {
    return !(rhs < lhs);
  }

/// greater_equal '>='  
template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator >= (const SmartPointer<T1, OP1, SP1>& lhs, U* rhs) {
    return !(lhs < rhs);
  }
  template <typename T1,
      template <typename> class OP1,
      template <typename> class SP1,
      typename U
      >
  bool operator >= (U* lhs, const SmartPointer<T1, OP1, SP1>& rhs) {
    return !(lhs < rhs);
  }

namespace std {
  /* Special allow std::less for SmartPointer */
  template <typename T,
      template <typename> class OP1,
      template <typename> class SP1
      >
    struct less<SmartPointer<T, OP1, SP1> > 
    : public binary_function<SmartPointer<T, OP1, SP1>, SmartPointer<T, OP1, SP1>, bool>
    {
      bool operator () (const SmartPointer<T, OP1, SP1>& lhs, const SmartPointer<T, OP1, SP1>& rhs) const {
        return less<T*>()(GetImpl(lhs), GetImpl(rhs));
      }
    };
    /* end special allow */
}
/* end friends for comparisons */

//-----------------------------------------------------------------------------
///////////////////////////////////////////////////////////////////////////////

///
/// SmartPointer<T, OwnershipPolicy<U>, StoragePolicy<X> >
///
/// Ownership Policies: NoCopyPolicy<T>, RefCountedPolicy<T>, RefLinkedPolicy<T>, ChangeOwnerCopyPolicy<T>
///
/// Storage Policies: DefaultStoragePolicy<T>, ArrayStoragePolicy<T>
///

/* Demo */
//-----------------------------------------------------------------------------
#include <ostream>
using std::ostream;

class C {
public:
  C() : a(0) {}
  C(int a) : a(a) {}
  friend ostream& operator << (ostream& out, const C& rhs) {
    out << rhs.a;
    return out;
  }
private:
  int a;
};

using std::cout;

int main() {
  SmartPointer<C> sp_1(new C(5));
  SmartPointer<C, NoCopyPolicy> sp_2(new C(10));
  SmartPointer<C, NoCopyPolicy, ArrayStoragePolicy> sp_2a(new C[15]);
  /* Cannot copy this SmartPointers *//*
   SmartPointer<C> sp_1x = sp_1;
   SmartPointer<C, NoCopyPolicy, ArrayStoragePolicy> sp_1xx;
   sp_1xx = sp_2;
  */

  /* block 1 */ {
    SmartPointer<C, RefCountedPolicy> sp_3(new C(20));
    SmartPointer<C, RefCountedPolicy, ArrayStoragePolicy> sp_3a(new C[25]);
  }

  /* block 2 */ {
    SmartPointer<C, RefCountedPolicy> sp_3x(new C(50));
    /* block 3 */ {
      SmartPointer<C, RefCountedPolicy> sp_3xx = sp_3x;
      SmartPointer<C, RefCountedPolicy> sp_3xxx;
      sp_3xxx = sp_3x;
    }
  }
  // SmartPointer<C, RefLinkedPolicy> sp_4(new C(30));
  // SmartPointer<C, RefLinkedPolicy, ArrayStoragePolicy> sp_4a(new C[35]);

  SmartPointer<C, ChangeOwnerCopyPolicy> sp_5(new C(40));
  SmartPointer<C, ChangeOwnerCopyPolicy> sp_5x = sp_5;
  SmartPointer<C, ChangeOwnerCopyPolicy, ArrayStoragePolicy> sp_5a(new C[45]);
  SmartPointer<C, ChangeOwnerCopyPolicy, ArrayStoragePolicy> sp_5ax = sp_5a;
  cout << *sp_5 /*<< ' ' << *sp_5 << ' ' << *sp_5a*/ << ' ' /*<< *sp_5ax*/ << endl;
  return 0;
}
