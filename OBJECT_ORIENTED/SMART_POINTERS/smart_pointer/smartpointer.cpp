#include <algorithm>
#include <iostream>
#include <ostream>
using std::cout;
using std::ostream;

/* Storage Policies */
//-----------------------------------------------------------------------------
/// DefaultStoragePolicy - to represent smart pointer as a raw pointer
template <class T>
class DefaultStoragePolicy {
public:
  typedef T* StoredType;    // the type of the mp_pointer object
  typedef T* InitPointerType; /// type used to declare OwnershipPolicy type.
  typedef T* PointerType;   // type returned by operator->
  typedef T& ReferenceType; // type returned by operator*

  DefaultStoragePolicy() : mp_pointer(Default())
  {}

  // The storage policy doesn't initialize the stored pointer
  //     which will be initialized by the OwnershipPolicy's Clone fn
  DefaultStoragePolicy(const DefaultStoragePolicy&) : mp_pointer(0)
  {}

  template <class U>
  DefaultStoragePolicy(const DefaultStoragePolicy<U>&) : mp_pointer(0)
  {}

  DefaultStoragePolicy(const StoredType& p) : mp_pointer(p) {}

  PointerType operator->() const { 
    return mp_pointer; 
  }

  ReferenceType operator*() const { 
    return *mp_pointer; 
  }

  void Swap(DefaultStoragePolicy& rhs) { 
    std::swap(mp_pointer, rhs.mp_pointer); 
  }

  // Accessors
  template <class F>
  friend typename DefaultStoragePolicy<F>::PointerType GetImpl(const DefaultStoragePolicy<F>& sp);

  template <class F>
  friend const typename DefaultStoragePolicy<F>::StoredType& GetImplRef(const DefaultStoragePolicy<F>& sp);

  template <class F>
  friend typename DefaultStoragePolicy<F>::StoredType& GetImplRef(DefaultStoragePolicy<F>& sp);

protected:
  // Destroys the data stored
  // (Destruction might be taken over by the OwnershipPolicy)
  void Destroy() {
    delete mp_pointer;
  }

  // Default value to initialize the pointer
  static StoredType Default() { 
    return 0; 
  }

private:
  // Data
  StoredType mp_pointer;
};

template <class T>
inline typename DefaultStoragePolicy<T>::PointerType GetImpl(const DefaultStoragePolicy<T>& sp) { 
  return sp.mp_pointer; 
}

template <class T>
inline const typename DefaultStoragePolicy<T>::StoredType& GetImplRef(const DefaultStoragePolicy<T>& sp) { 
  return sp.mp_pointer; 
}

template <class T>
inline typename DefaultStoragePolicy<T>::StoredType& GetImplRef(DefaultStoragePolicy<T>& sp) { 
  return sp.mp_pointer; 
}

//-----------------------------------------------

/// ArrayStoragePolicy - to represent smart pointer as a raw pointer referenced to an array
template <class T>
class ArrayStoragePolicy {
public:
  typedef T* StoredType;    // the type of the mp_pointer object
  typedef T* InitPointerType; /// type used to declare OwnershipPolicy type.
  typedef T* PointerType;   // type returned by operator->
  typedef T& ReferenceType; // type returned by operator*

  ArrayStoragePolicy() : mp_pointer(Default())
  {}

  // The storage policy doesn't initialize the stored pointer
  //     which will be initialized by the OwnershipPolicy's Clone fn
  ArrayStoragePolicy(const ArrayStoragePolicy&) : mp_pointer(0)
  {}

  template <class U>
  ArrayStoragePolicy(const ArrayStoragePolicy<U>&) : mp_pointer(0)
  {}

  ArrayStoragePolicy(const StoredType& p) : mp_pointer(p) {}

  PointerType operator->() const { 
    return mp_pointer; 
  }

  ReferenceType operator*() const { 
    return *mp_pointer; 
  }

  void Swap(ArrayStoragePolicy& rhs) { 
    std::swap(mp_pointer, rhs.mp_pointer); 
  }

  // Accessors
  template <class F>
  friend typename ArrayStoragePolicy<F>::PointerType GetImpl(const ArrayStoragePolicy<F>& sp);

  template <class F>
  friend const typename ArrayStoragePolicy<F>::StoredType& GetImplRef(const ArrayStoragePolicy<F>& sp);

  template <class F>
  friend typename ArrayStoragePolicy<F>::StoredType& GetImplRef(ArrayStoragePolicy<F>& sp);

protected:
  // Destroys the data stored
  // (Destruction might be taken over by the OwnershipPolicy)
  void Destroy() { 
    delete [] mp_pointer; 
  }

  // Default value to initialize the pointer
  static StoredType Default() { 
    return 0; 
  }

private:
  // Data
  StoredType mp_pointer;
};

template <class T>
inline typename ArrayStoragePolicy<T>::PointerType GetImpl(const ArrayStoragePolicy<T>& sp) { 
  return sp.mp_pointer; 
}

template <class T>
inline const typename ArrayStoragePolicy<T>::StoredType& GetImplRef(const ArrayStoragePolicy<T>& sp) { 
  return sp.mp_pointer; 
}

template <class T>
inline typename ArrayStoragePolicy<T>::StoredType& GetImplRef(ArrayStoragePolicy<T>& sp) { 
  return sp.mp_pointer; 
}

//-----------------------------------------------------------------------------

/* Ownership policies */
//-----------------------------------------------------------------------------
///RefCountedPolicy - counts number of references to the object
template <class T>
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
  enum { change_owner_copy = false };

private:
  unsigned int* mp_counter;
};

//-----------------------------------------------

//-----------------------------------------------

/// ChangeOwnerCopyPolicy - destructive copy a la std::auto_ptr
template <class P>
class ChangeOwnerCopyPolicy {
public:
  ChangeOwnerCopyPolicy() {}

  template <class P1>
  ChangeOwnerCopyPolicy(const ChangeOwnerCopyPolicy<P1>&)
  {}

  template <class P1>
  static P Clone(P1& val) {
    P result(val);
    val = P1();
    return result;
  }

  static bool Release(const P&) { 
    return true; 
  }

  static void Swap(ChangeOwnerCopyPolicy&)
  {}

  enum { change_owner_copy = true };
};

//-----------------------------------------------

/// NoCopyPolicy - restiction of copy of an object stored in smart pointer
template <class P>
class NoCopyPolicy {
public:
  NoCopyPolicy() {}

  template <class P1>
  NoCopyPolicy(const NoCopyPolicy<P1>&)
  {}

  static P Clone(const P&) {}

  static bool Release(const P&) { 
    return true; 
  }

  static void Swap(NoCopyPolicy&) {}

  enum { change_owner_copy = false };
};

//-----------------------------------------------------------------------------

///////////////////////////////////////////////////////////////////////////////
// Selects one of two types based upon a boolean constant
// Invocation: Select<flag, T, U>::Result
// where:
// flag is a compile-time boolean constant
// T and U are types
// Result evaluates to T if flag is true, and to U otherwise.
///////////////////////////////////////////////////////////////////////////////
template <bool flag, typename T, typename U>
struct Select {
  typedef T Result;
};

template <typename T, typename U>
struct Select<false, T, U> {
  typedef U Result;
};


///////////////////////////////////////////////////////////////////////////////
/// class SmartPointer
/// Release() returns a boolean saying if that was the last release
///     so the pointer can be deleted by the StoragePolicy
////////////////////////////////////////////////////////////////////////////////
template
<
  typename T,
  template <class> class OwnershipPolicy = NoCopyPolicy,
  template <class> class StoragePolicy = DefaultStoragePolicy
>
class SmartPointer
  : public StoragePolicy<T>
  , public OwnershipPolicy<typename StoragePolicy<T>::InitPointerType>
{
private:
  T* m_pointer;
  typedef StoragePolicy<T> SP;
  typedef OwnershipPolicy<typename StoragePolicy<T>::InitPointerType> OP;

public:
  typedef typename SP::PointerType PointerType;
  typedef typename SP::StoredType StoredType;
  typedef typename SP::ReferenceType ReferenceType;

  typedef typename Select<OP::change_owner_copy, SmartPointer, const SmartPointer>::Result CopyArg;

public:
  SmartPointer() {}
  explicit SmartPointer(T* ptr) : m_pointer(ptr) {}

  SmartPointer(CopyArg& rhs) : SP(rhs), OP(rhs) {
    GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  SmartPointer(const SmartPointer<T1, OP1, SP1>& rhs)
  : SP(rhs) 
  , OP(rhs) 
  { 
    GetImplRef(*this) = OP::Clone(GetImplRef(rhs)); 
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  SmartPointer(SmartPointer<T1, OP1, SP1>& rhs)
  : SP(rhs) 
  , OP(rhs) 
  {
    GetImplRef(*this) = OP::Clone(GetImplRef(rhs));
  }

  SmartPointer& operator=(CopyArg& rhs) {
    SmartPointer temp(rhs);
    temp.Swap(*this);
    return *this;
  }

  template
  <
    typename T1,
    template <class> class OP1,
     template <class> class SP1
  >
  SmartPointer& operator=(const SmartPointer<T1, OP1, SP1>& rhs) {
    SmartPointer temp(rhs);
    temp.Swap(*this);
    return *this;
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  SmartPointer& operator=(SmartPointer<T1, OP1, SP1>& rhs) {
    SmartPointer temp(rhs);
    temp.Swap(*this);
    return *this;
  }

  void Swap(SmartPointer& rhs) {
    OP::Swap(rhs);
    SP::Swap(rhs);
  }

  ~SmartPointer() {
    if (OP::Release(GetImpl(*static_cast<SP*>(this)))) {
      SP::Destroy();
    }
  }

  friend inline void Release(SmartPointer& sp, typename SP::StoredType& p) {
    p = GetImplRef(sp);
    GetImplRef(sp) = SP::Default();
  }

  friend inline void Reset(SmartPointer& sp, typename SP::StoredType p) { 
    SmartPointer(p).Swap(sp); 
  }

  PointerType operator->() {
    return SP::operator->();
  }

  ReferenceType operator*() {
    return SP::operator*();
  }

  bool operator!() const {  // Enables "if (!sp) ..." 
    return GetImpl(*this) == 0; 
  }

  static inline T * GetPointer( const SmartPointer & sp ) { 
    return GetImpl( sp ); 
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  bool operator==(const SmartPointer<T1, OP1, SP1>& rhs) const { 
    return GetImpl(*this) == GetImpl(rhs); 
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  bool operator!=(const SmartPointer<T1, OP1, SP1>& rhs) const { 
    return !(*this == rhs); 
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  bool operator<(const SmartPointer<T1, OP1, SP1>& rhs) const { 
    return GetImpl(*this) < GetImpl(rhs); 
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  inline bool operator > ( const SmartPointer<T1, OP1, SP1> & rhs ) {
    return ( GetImpl( rhs ) < GetImpl( *this ) );
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  inline bool operator <= ( const SmartPointer<T1, OP1, SP1> & rhs ) {
    return !( GetImpl( rhs ) < GetImpl( *this ) );
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  inline bool operator >= ( const SmartPointer<T1, OP1, SP1> & rhs ) {
    return !( GetImpl( *this ) < GetImpl( rhs ) );
  }

  template
  <
    typename T1,
    template <class> class OP1,
    template <class> class SP1
  >
  friend void Release(SmartPointer<T1, OP1, SP1>& sp, typename SP1<T1>::StoredType& p);
};

////////////////////////////////////////////////////////////////////////////////
// free comparison operators for class template SmartPointer
////////////////////////////////////////////////////////////////////////////////
template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator==(const SmartPointer<T, OP, SP>& lhs, U* rhs) { 
  return GetImpl(lhs) == rhs; 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator==(U* lhs, const SmartPointer<T, OP, SP>& rhs) { 
  return rhs == lhs; 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator!=(const SmartPointer<T, OP, SP>& lhs, U* rhs) { 
  return !(lhs == rhs); 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator!=(U* lhs, const SmartPointer<T, OP, SP>& rhs) { 
  return rhs != lhs; 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator<(const SmartPointer<T, OP, SP>& lhs, U* rhs) {
  return ( GetImpl( lhs ) < rhs );
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator<(U* lhs, const SmartPointer<T, OP, SP>& rhs) {
  return ( GetImpl( rhs ) < lhs );
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator>(const SmartPointer<T, OP, SP>& lhs, U* rhs) { 
  return rhs < lhs; 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator>(U* lhs, const SmartPointer<T, OP, SP>& rhs) { 
  return rhs < lhs; 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator<=(const SmartPointer<T, OP, SP>& lhs, U* rhs) { 
  return !(rhs < lhs); 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator<=(U* lhs, const SmartPointer<T, OP, SP>& rhs) { 
  return !(rhs < lhs); 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator>=(const SmartPointer<T, OP, SP>& lhs, U* rhs) { 
  return !(lhs < rhs); 
}

template
<
  typename T,
  template <class> class OP,
  template <class> class SP,
  typename U
>
inline bool operator>=(U* lhs, const SmartPointer<T, OP, SP>& rhs) { 
  return !(lhs < rhs); 
} 

template
<
  typename T,
  template <class> class OP,
  template <class> class SP
>
inline void Release(SmartPointer<T, OP, SP>& sp, typename SP<T>::StoredType& p) {
  p = GetImplRef(sp);
  GetImplRef(sp) = SP<T>::Default();
}

//-----------------------------------------------------------------------------

/* Demo */
//-----------------------------------------------------------------------------
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

  SmartPointer<C, ChangeOwnerCopyPolicy> sp_5(new C(40));
  SmartPointer<C, ChangeOwnerCopyPolicy> sp_5x = sp_5;
  SmartPointer<C, ChangeOwnerCopyPolicy, ArrayStoragePolicy> sp_5a(new C[45]);
  SmartPointer<C, ChangeOwnerCopyPolicy, ArrayStoragePolicy> sp_5ax = sp_5a;
  return 0;
}
