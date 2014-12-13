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

HRESULT CHello::GetTypeInfoCount(UINT* infoCount) {
    *infoCount = 1;
    return S_OK;
}
HRESULT CHello::GetTypeInfo(UINT id, LCID lcid, ITypeInfo** typeInfo) {
    if (id != 0) {
        return DISP_E_BADINDEX;
    }
    return E_NOTIMPL;
}
HRESULT CHello::GetIDsOfNames(
    REFIID riid,
    LPOLESTR* names,
    UINT nameCount,
    LCID lcid,
    DISPID* dispid
) {
    return E_NOTIMPL;
}
HRESULT CHello::Invoke(
    DISPID member,
    REFIID riid,
    LCID lid,
    WORD flags,
    DISPPARAMS* dispParams,
    VARIANT* result,
    EXCEPINFO* excepInfo,
    UINT* argErr
) {
    return E_NOTIMPL;
}

void CHello::Hello() {
    printf("Hello world\n");
}
