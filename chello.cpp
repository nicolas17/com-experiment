#include <initguid.h>

#include "chello.h"

#include <cstdio>

HRESULT CHello::QueryInterface(REFIID iid, void **object)
{
    HRESULT ret = S_OK;
    if (IsEqualIID(iid, IID_IUnknown)) {
        *object = (IUnknown*) this;
    } else if (IsEqualIID(iid, IID_IDispatch)) {
        *object = (IDispatch*) this;
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

HRESULT CHello::loadTypeInfo() {
    HRESULT hr;

    ITypeLib* typelib;
    hr = LoadTypeLib(L"hello.tlb", &typelib);
    if (FAILED(hr)) {
        wprintf(L"Can't load typelib: 0x%x", hr);
        return hr;
    }

    hr = typelib->GetTypeInfoOfGuid(IID_IHello, &m_typeInfo);
    if (FAILED(hr)) {
        wprintf(L"Can't get typeinfo: 0x%x", hr);
        return hr;
    }
    //m_typeInfo->AddRef(); // is this needed?
    typelib->Release();
    return S_OK;
}

HRESULT CHello::GetTypeInfoCount(UINT* infoCount) {
    *infoCount = 1;
    return S_OK;
}
HRESULT CHello::GetTypeInfo(UINT id, LCID lcid, ITypeInfo** typeInfo) {
    HRESULT hr;

    if (id != 0) {
        return DISP_E_BADINDEX;
    }

    if (!m_typeInfo) {
        hr = this->loadTypeInfo();
        if (FAILED(hr)) return hr;
    }
    m_typeInfo->AddRef();
    *typeInfo = m_typeInfo;
    return S_OK;
}
HRESULT CHello::GetIDsOfNames(
    REFIID riid,
    LPOLESTR* names,
    UINT nameCount,
    LCID lcid,
    DISPID* dispid
) {
    if (!m_typeInfo) {
        loadTypeInfo(); // TODO error checking
    }
    return DispGetIDsOfNames(m_typeInfo, names, nameCount, dispid);
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
    return DispInvoke(this, m_typeInfo, member, flags, dispParams, result, excepInfo, argErr);
}

void CHello::Hello() {
    printf("Hello world\n");
}
