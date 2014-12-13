#ifndef COMEXPERIMENT_CHELLO_H
#define COMEXPERIMENT_CHELLO_H

#include "hello.h"

// {9957873A-4208-4AFE-ADD7-FC5BB781AFBC}
DEFINE_GUID(CLSID_Hello,
    0x9957873a, 0x4208, 0x4afe, 0xad, 0xd7, 0xfc, 0x5b, 0xb7, 0x81, 0xaf, 0xbc);

class CHello : public IHello {
public:
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppvObject) override;
    ULONG STDMETHODCALLTYPE AddRef() override;
    ULONG STDMETHODCALLTYPE Release() override;

    HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT* infoCount) override;
    HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT id, LCID lcid, ITypeInfo** typeInfo) override;
    HRESULT STDMETHODCALLTYPE GetIDsOfNames(
        REFIID riid,
        LPOLESTR* names,
        UINT nameCount,
        LCID lcid,
        DISPID* dispid
    ) override;
    HRESULT STDMETHODCALLTYPE Invoke(
        DISPID member,
        REFIID riid,
        LCID lid,
        WORD flags,
        DISPPARAMS* dispParams,
        VARIANT* result,
        EXCEPINFO* excepInfo,
        UINT* argErr
    ) override;

    void STDMETHODCALLTYPE Hello() override;

private:
    ULONG m_refCount=0;
    ITypeInfo* m_typeInfo = nullptr;
};

#endif
