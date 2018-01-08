#include "Delegates.h"
#include "EventArgs.h"

NonTypeDelegate::NonTypeDelegate(void (*pfn)(EventArgs&))
		: mpFunc(pfn)
{
}

void NonTypeDelegate::Invoke(EventArgs& args)
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
		EventArgs args("ClickEventArgs", (void*) 0);
		proxy.Invoke(args);
	}

	TypeDelegate<Boo> proxy;

	void ProxyHandler(EventArgs& args) {}
};

