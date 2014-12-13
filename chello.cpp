#include <initguid.h>

#include "chello.h"

#include <cstdio>

HRESULT CHello::QueryInterface(REFIID iid, void **object)
{
    HRESULT ret = S_OK;
    if (IsEqualIID(iid, IID_IUnknown)) {
        *object = (IUnknown*) this;
    } else if (IsEqualIID(iid, IID_IHello)) {
        *object = (IHello*) this;
    } else {
        ret = E_NOINTERFACE;
    }

    if (ret == S_OK) {
        ((IUnknown*) *object)->AddRef();
    }
    return ret;
}
ULONG CHello::AddRef()
{
    return ++m_refCount;
}
ULONG CHello::Release()
{
    ULONG newRefCount = --m_refCount;
    if (newRefCount == 0) {
        delete this;
    }
    return newRefCount;
}

void CHello::Hello() {
    printf("Hello world\n");
}
