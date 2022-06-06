#pragma once
#include <string>
#include <list>
#include <QVariantMap>
#include "SmartPtr.h"

// ------------------------------------------------

class Delegate 
{
public:
      virtual void Invoke(QVariantMap& args)=0;
protected:
      Delegate(){}
      virtual ~Delegate(){}
}; 

typedef std::list<Delegate*>	DelegateList;
typedef DelegateList::iterator	DelegateListItr;

// ------------------------------------------------

class NonTypeDelegate : public Delegate  
{
public:
   void Invoke(QVariantMap& args);
   NonTypeDelegate(void (*pFunc)(QVariantMap&));
   virtual ~NonTypeDelegate(){}
private:
   void (*mpFunc)(QVariantMap&);
};

// ------------------------------------------------

template <typename T>
class TypeDelegate : public Delegate  
{
public:
   void Invoke(QVariantMap& args);
   TypeDelegate(T *obj, void (T::*pfn)(QVariantMap&));
   ~TypeDelegate(){}

private:
   T* mObject;
   void (T::*m_pfn)(QVariantMap&);
};

// ------------------------------------------------

template<typename T>
TypeDelegate<T>::TypeDelegate(T *obj, void (T::*pfn)(QVariantMap&))
    : mObject(obj), m_pfn(pfn)
{
}

template<typename T>
void TypeDelegate<T>::Invoke(QVariantMap& args)
{
   (mObject->*m_pfn)(args);
}
#define DeclareDelegate(_CLASS_,_METHOD_) \
    TypeDelegate<_CLASS_> delegate_##_METHOD_;\
    void _METHOD_(QVariantMap &args)

#define ConstructDelegate(_CLASS_,_METHOD_) delegate_##_METHOD_(this, &_CLASS_::_METHOD_)

#define NewDelegate(_CLASS_,_METHOD_)	new TypeDelegate<_CLASS_>(this, &_CLASS_::_METHOD_)
