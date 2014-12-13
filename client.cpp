#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ole2.h>
#include <initguid.h>

#include <stdio.h>

#include "chello.h"

void greetByDispatch(IUnknown* hello) {
    HRESULT hr;

    IDispatch* dispatch;
    hr = hello->QueryInterface(IID_IDispatch, (void**)&dispatch);
    if (FAILED(hr)) {
        wprintf(L"QueryInterface(IDispatch) failed: 0x%x\n", hr);
        return;
    }

    OLECHAR* methodName = L"Hello";
    DISPID methodId;
    hr = dispatch->GetIDsOfNames(IID_NULL, &methodName, 1, 0, &methodId);
    if (FAILED(hr)) {
        wprintf(L"Error finding Hello method: 0x%x\n", hr);
        return;
    }

    DISPPARAMS params = {nullptr, nullptr, 0, 0};
    hr = dispatch->Invoke(methodId, IID_NULL, 0, DISPATCH_METHOD, &params, nullptr, nullptr, nullptr);
    if (FAILED(hr)) {
        wprintf(L"Error calling Hello method: 0x%x\n", hr);
        return;
    }
    dispatch->Release();
}

int main()
{
    HRESULT hr;

    hr = CoInitialize(nullptr);

    IHello* hello;

    hr = CoCreateInstance(CLSID_Hello, nullptr, CLSCTX_INPROC_SERVER, IID_IHello, (void**)&hello);
    if (FAILED(hr)) {
        wprintf(L"CoCreateInstance failed: 0x%x\n", hr);
        return 1;
    }

    hello->Hello();

    greetByDispatch(hello);

    hello->Release();

    CoUninitialize();
}
