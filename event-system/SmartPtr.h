#ifndef _SMART_PTR_H
#define _SMART_PTR_H

/*
class RefCountBase
{
private:
    mutable long refCounter;
protected:
    virtual ~RefCountBase()     {  }

    RefCountBase() : refCounter(0)        {  }

    void AddRef() const		
	{
		//__sync_fetch_and_add(&refCounter,1); 
		refCounter++;
	}
    void Release() const	
	{ 
		//if(!__sync_fetch_and_sub(&refCounter,1))      
		refCounter--;
		if (refCounter==0)
			delete this;
	}
public:
	friend class ProtectedAddRef;
};

class ProtectedAddRef
{
public:
	ProtectedAddRef()		{}
    void	AddRef(RefCountBase *const refPointer) const	{ if (refPointer) refPointer->AddRef(); }
    void	Release(RefCountBase *const refPointer) const	{ if (refPointer) refPointer->Release(); }
};


template<class T>
class SmartPtr
{
    RefCountBase* refPointer;
    T* objectPointer;
public:
	SmartPtr()
        : refPointer(0), objectPointer(0)
	{}
    SmartPtr(const SmartPtr& eph)
        : refPointer(eph.refPointer), objectPointer(eph.objectPointer)		{ AddRef(); }
    SmartPtr(T* ep) : refPointer(ep), objectPointer(ep)		{ AddRef(); }
    virtual ~SmartPtr()						{ 
		Release(); 
	}

    T* operator->() const			        { return objectPointer; }
    bool operator!()						{ return refPointer==0; }
    bool operator!()const					{ return refPointer==0; }
    bool operator==(const SmartPtr& in)		{ return refPointer==in.refPointer; }
    bool operator!=(const SmartPtr& in)		{ return refPointer!=in.refPointer; }
    SmartPtr& operator=(const SmartPtr& eph)
    {
		eph.AddRef();
		Release();
        refPointer = eph.refPointer; objectPointer=eph.objectPointer;
        return *this;
    }
    SmartPtr& operator=(T* ep)
    {
        if (ep != refPointer)
		{
			Release();
            refPointer = ep; objectPointer = ep;
			AddRef();
		}
        return *this;
    }
	template <class Y>
    operator SmartPtr<Y>()				{ return dynamic_cast<Y*>((objectPointer)); }
	SmartPtr* operator&()				{ return this; }
private:
    void	AddRef() const		{ ProtectedAddRef().AddRef(refPointer); }
    void	Release() const		{ ProtectedAddRef().Release(refPointer); }
};
*/

//===================================================


class RefCountBase
{
public:
    void AddRef()        { refCounter++; }
    void ReleaseRef()
    {
        refCounter--;
        if(refCounter==0)
            delete this;
    }

protected:
    RefCountBase() : refCounter(0)    {}
    virtual ~RefCountBase()     {}

private:
    mutable long refCounter;
};


template<class T>
class SmartPtr
{
public:
    SmartPtr(T* obj=0)
        :pObject(obj)
    {
        if(pObject)
            pObject->AddRef();
    }

    SmartPtr(const SmartPtr& other)
        :pObject(other.pObject)
    {
        if(pObject)
            pObject->AddRef();
    }

    ~SmartPtr()
    {
        if(pObject)
            pObject->ReleaseRef();
    }

    T* operator->() const
    {
        return pObject;
    }

    SmartPtr& operator=(const SmartPtr& other)
    {
        if(other.pObject)
            other->AddRef();
        if(pObject)
            pObject->ReleaseRef();
        pObject = other.pObject;
        return *this;
    }

    bool operator!()        { return pObject==0; }

    bool operator!()const        { return pObject==0; }

    SmartPtr& operator=(T* other)
    {
        if(other)
            other->AddRef();
        if(pObject)
            pObject->ReleaseRef();
        pObject = other;
        return *this;
    }

    bool operator==(const SmartPtr& other)
    {
        return pObject==other.pObject;
    }

    bool operator!=(const SmartPtr& other)
    {
        return pObject!=other.pObject;
    }

    //use it only if no way to convert dirrerent THolder of the same object
    //(multiple inheritence of interfaces those are virtually derived from RefCountBase)
    //it is better to specify function for explicit convertion
#ifdef ENABLE_HOLDER_AUTO_CAST
    template<class U> operator SmartPtr<U>()
    {
        try
        {
            return dynamic_cast<U*>(pObject);
        }
        catch(...)
        {
            //very dangerous but sometimes is acceptable
            //return static_cast<U*>(pObject);
            return NULL;
        }
    }
#endif

    template <class Y>
    operator SmartPtr<Y>()				{ return dynamic_cast<Y*>((pObject)); }
    SmartPtr* operator&()				{ return this; }
private:
    T* pObject;
    //SmartPtr* operator&()    { return 0; } // only via assingnment operator to another SmartPtr

};

#endif

