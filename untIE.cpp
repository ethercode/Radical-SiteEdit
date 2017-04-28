//---------------------------------------------------------------------------


#pragma hdrstop

#include "untIE.h"

#include <mshtml.h>
#include <atl/atlbase.h>
#include <oleacc.h>
#include <windows.h>
#define INITGUID
#include <initguid.h>
#include <exdisp.h>
#include <memory.h>
#include <vcl.h>

HRESULT GetPostData(char* cszPostData, LPVARIANT pvPostData);

AnsiString DoURL(AnsiString strURL, AnsiString strPost)
{
    AnsiString                  pReturnValue;
    HRESULT                     hr;
    IWebBrowserApp*             pWBApp          = NULL; // Derived from IWebBrowser
    BSTR bstrURL =              NULL, bstrHeaders = NULL;
    short                       fBusy           = 1;
    VARIANT                     vFlags = {0}, vTargetFrameName = {0}, vPostData = {0}, vHeaders = {0};
    CComPtr<IDispatch>          spDisp;
    CComQIPtr<IHTMLDocument2>   spDoc;
    IHTMLElement*               pBodyElement    = NULL;
    wchar_t*                    text            = NULL;

    if (FAILED(hr = CoInitialize(NULL)))
    {
        return "";
    }

    if (FAILED(hr = CoCreateInstance(CLSID_InternetExplorer, NULL, CLSCTX_SERVER, IID_IWebBrowserApp, (LPVOID *) &pWBApp)))
    {
        goto Error;
    }

    Application->MainForm->SetFocus();
    bstrURL = SysAllocString(WideString(strURL));
    if (!bstrURL)
    {
        goto Error;
    }

    bstrHeaders = SysAllocString(L"Content-Type: application/x-www-form-urlencoded\r\n");
    if (!bstrHeaders)
    {
        goto Error;
    }

    V_VT(&vHeaders) = VT_BSTR;
    V_BSTR(&vHeaders) = bstrHeaders;

    hr = GetPostData(strPost.c_str(), &vPostData);
    hr = pWBApp->Navigate(bstrURL, &vFlags, &vTargetFrameName, &vPostData, &vHeaders);

    while (fBusy)
    {
        pWBApp->get_Busy(&fBusy);
        Sleep(100);
    }

    pWBApp->get_Document(&spDisp.p);
    spDoc = spDisp;
    spDoc.p->get_body(&pBodyElement);
    if (pBodyElement)
    {
        pBodyElement->get_innerText(&text);
        pReturnValue = text;
        pReturnValue = pReturnValue.Trim();
    }

    Error:
    if (bstrURL)
    {
        SysFreeString(bstrURL);
    }
    if (bstrHeaders)
    {
        SysFreeString(bstrHeaders);
    }
    VariantClear(&vPostData);
    if (pBodyElement)
    {
        pBodyElement->Release();
    }
    if (pWBApp)
    {
        pWBApp->Quit();
        pWBApp->Release();
    }
    CoUninitialize();

    return pReturnValue;
}

// Pack some data into a SAFEARRAY of BYTEs. Return in a VARIANT
HRESULT GetPostData(char* cszPostData, LPVARIANT pvPostData)
{
    HRESULT     hr;
    LPSAFEARRAY psa;
    UINT        cElems  = lstrlen(cszPostData);
    LPSTR       pPostData;

    if (!pvPostData)
    {
        return E_POINTER;
    }

    VariantInit(pvPostData);

    psa = SafeArrayCreateVector(VT_UI1, 0, cElems);
    if (!psa)
    {
        return E_OUTOFMEMORY;
    }

    hr = SafeArrayAccessData(psa, (LPVOID *) &pPostData);
    memcpy(pPostData, cszPostData, cElems);
    hr = SafeArrayUnaccessData(psa);

    V_VT(pvPostData) = VT_ARRAY | VT_UI1;

    V_ARRAY(pvPostData) = psa;
    return NOERROR;
}

