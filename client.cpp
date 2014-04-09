#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ole2.h>
#include <initguid.h>

#include <stdio.h>

#include "chello.h"

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
	hello->Release();

	CoUninitialize();
}
