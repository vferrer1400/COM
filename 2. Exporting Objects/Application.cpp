#include "windows.h"
#define TRACE OutputDebugString

struct ComException
{
    HRESULT error;
    ComException(HRESULT const hr) : error(hr){}
};

inline void HR(HRESULT const hr)
{
    if (S_OK != hr)
    {
        throw ComException(hr);
    }
}

int main()
{
    HRESULT hr = S_OK;
    //HRESULT hr = S_FALSE;

    // Strong advice to not use this macros and check the real errors

    //if (SUCCEEDED(hr))
    //{
    //    TRACE("succeeded\n");
    //}

    //if (FAILED(hr))
    //{
    //    TRACE("failed\n");
    //}

    if (hr == S_OK)
    {
        TRACE("succeeded\n");
    }
    else
    {
        TRACE("failed\n");
        HR(hr);
    }
    return 0;
}