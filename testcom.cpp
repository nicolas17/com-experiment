#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ole2.h>

#include <stdio.h>

int main()
{
	HRESULT hr;

	hr = CoInitialize(nullptr);

	CLSID clsid;
	hr = CLSIDFromProgID(L"WScript.Shell", &clsid);
	if (FAILED(hr)) {
		wprintf(L"CLSIDFromProgID failed: 0x%x\n", hr);
		return 1;
	}
	IUnknown* punk;

	hr = CoCreateInstance(clsid, nullptr, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&punk);
	if (FAILED(hr)) {
		wprintf(L"CoCreateInstance failed: 0x%x\n", hr);
		return 1;
	}

	IDispatch* pdisp;
	hr = punk->QueryInterface(IID_IDispatch, (void**)&pdisp);
	if (FAILED(hr)) {
		wprintf(L"Can't get IDispatch interface: 0x%x\n", hr);
	}

	OLECHAR* methodName = L"Run";
	DISPID dispID;
	hr = pdisp->GetIDsOfNames(IID_NULL, &methodName, 1, 0, &dispID);
	if (FAILED(hr)) {
		wprintf(L"Can't get Run method: 0x%x\n", hr);
	}

	BSTR command = SysAllocString(L"calc.exe");
	VARIANTARG args[1];
	args[0].vt = VT_BSTR;
	args[0].bstrVal = command;
	DISPPARAMS paramstruct = { args, nullptr, 1, 0 };
	
	EXCEPINFO exc;

	hr = pdisp->Invoke(dispID, IID_NULL, 0, DISPATCH_METHOD, &paramstruct, nullptr, &exc, nullptr);
	if (hr == DISP_E_EXCEPTION) {
		wprintf(L"Run method threw an exception: 0x%x\n", exc.scode);
	} else if (FAILED(hr)) {
		wprintf(L"Can't invoke Run method: 0x%x\n", hr);
	}

	pdisp->Release();
	punk->Release();

	CoUninitialize();
}
