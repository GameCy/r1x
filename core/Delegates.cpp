#include "Delegates.h"


NonTypeDelegate::NonTypeDelegate(void (*pfn)(QVariantMap&))
		: mpFunc(pfn)
{
}

void NonTypeDelegate::Invoke(QVariantMap& args)
{
   mpFunc(args);
}

class Boo
{
public:
	Boo()
    : proxy( this, &Boo::ProxyHandler)
	{}

	void example()
	{
        QVariantMap args;
        args["ClickEventArgs"] = 0;
		proxy.Invoke(args);
	}

	TypeDelegate<Boo> proxy;

    void ProxyHandler(QVariantMap& args) {}
};

