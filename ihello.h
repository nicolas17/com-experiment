#ifndef COMEXPERIMENT_IHELLO_H
#define COMEXPERIMENT_IHELLO_H

#include <ole2.h>

// {DA193271-5E58-41AC-9ECE-0865757DFAD4}
DEFINE_GUID(IID_IHello,
	0xda193271, 0x5e58, 0x41ac, 0x9e, 0xce, 0x8, 0x65, 0x75, 0x7d, 0xfa, 0xd4);


interface IHello: public IUnknown
{
	virtual void STDMETHODCALLTYPE Hello() = 0;
};

#endif
