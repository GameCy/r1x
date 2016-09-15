#pragma once

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
	void	AddRef(RefCountBase *const ep_) const	{ if (ep_) ep_->AddRef(); }
	void	Release(RefCountBase *const ep_) const	{ if (ep_) ep_->Release(); }
};


template<class T>
class SmartPtr
{
    RefCountBase* ep_;
	T* ept_;
public:
	SmartPtr()
		: ep_(0), ept_(0)
	{}
    SmartPtr(const SmartPtr& eph)
		: ep_(eph.ep_), ept_(eph.ept_)		{ AddRef(); }
    SmartPtr(T* ep) : ep_(ep), ept_(ep)		{ AddRef(); }
    virtual ~SmartPtr()						{ 
		Release(); 
	}

    T* operator->() const			        { return ept_; }
    bool operator!()						{ return ep_==0; }
    bool operator!()const					{ return ep_==0; }
    bool operator==(const SmartPtr& in)		{ return ep_==in.ep_; }
    bool operator!=(const SmartPtr& in)		{ return ep_!=in.ep_; }
    SmartPtr& operator=(const SmartPtr& eph)
    {
		eph.AddRef();
		Release();
        ep_ = eph.ep_; ept_=eph.ept_;
        return *this;
    }
    SmartPtr& operator=(T* ep)
    {
		if (ep != ep_)
		{
			Release();
			ep_ = ep; ept_ = ep;
			AddRef();
		}
        return *this;
    }
	template <class Y>
	operator SmartPtr<Y>()				{ return static_cast<Y*>((ept_)); }
	SmartPtr* operator&()				{ return this; }
private:
	void	AddRef() const		{ ProtectedAddRef().AddRef(ep_); }
	void	Release() const		{ ProtectedAddRef().Release(ep_); }
};

