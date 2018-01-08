#ifndef _SMART_PTR_H
#define _SMART_PTR_H

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

    template <class Y>
    operator SmartPtr<Y>()				{ return dynamic_cast<Y*>((pObject)); }
    SmartPtr* operator&()				{ return this; }
private:
    T* pObject;
    //SmartPtr* operator&()    { return 0; } // only via assingnment operator to another SmartPtr

};

#endif

