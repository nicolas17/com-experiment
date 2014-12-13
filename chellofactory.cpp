#include <initguid.h>

#include "chellofactory.h"

#include <new>

#include "chello.h"

HRESULT CHelloFactory::QueryInterface(REFIID iid, void **object)
{
    HRESULT ret = S_OK;
    if (IsEqualIID(iid, IID_IUnknown)) {
        *object = (IUnknown*) this;
    } else if (IsEqualIID(iid, IID_IClassFactory)) {
        *object = (IClassFactory*) this;
    } else {
        ret = E_NOINTERFACE;
    }

    if (ret == S_OK) {
        ((IUnknown*) *object)->AddRef();
    }
    return ret;
}
ULONG CHelloFactory::AddRef()
{
    return ++m_refCount;
}
ULONG CHelloFactory::Release()
{
    ULONG newRefCount = --m_refCount;
    if (newRefCount == 0) {
        delete this;
    }
    return newRefCount;
}

HRESULT CHelloFactory::CreateInstance(IUnknown *outer, REFIID iid, void **object) {
    if (outer) {
        return CLASS_E_NOAGGREGATION;
    }
    *object = NULL;
    try {
        IHello* hello = new CHello;
        HRESULT ret = hello->QueryInterface(iid, object);
        if (FAILED(ret)) {
            delete hello;
        }
        return ret;
    }
    catch (std::bad_alloc&) {
        return E_OUTOFMEMORY;
    }
}

HRESULT CHelloFactory::LockServer(BOOL lock) {
    return S_OK;
}
HRESULT __stdcall DllGetClassObject(REFCLSID clsid, REFIID iid, void **out) {
    if (IsEqualCLSID(clsid, CLSID_Hello)) {
        CHelloFactory* factory = new CHelloFactory;
        HRESULT ret;

        factory->AddRef();
        ret = factory->QueryInterface(iid, out);
        factory->Release();
        return ret;
    } else {
        *out = nullptr;
        return CLASS_E_CLASSNOTAVAILABLE;
    }
}
HRESULT __stdcall DllCanUnloadNow() {
    return S_FALSE;
}
