#ifndef COMEXPERIMENT_CHELLOFACTORY_H
#define COMEXPERIMENT_CHELLOFACTORY_H

#include <Ole2.h>

class CHelloFactory : public IClassFactory {
public:
	//IUnknown methods
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void **object) override;
	ULONG STDMETHODCALLTYPE AddRef() override;
	ULONG STDMETHODCALLTYPE Release() override;

	//IClassFactory methods
	HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown *outer, REFIID iid, void **object) override;
	HRESULT STDMETHODCALLTYPE LockServer(BOOL lock) override;

private:
	ULONG m_refCount=0;
};

#endif
