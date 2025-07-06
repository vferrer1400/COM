#include "Library.h"
//#include <stdio.h>
#include <windows.h>
#include <crtdbg.h>
#include <iostream>

#define ASSERT _ASSERTE
#define TRACE OutputDebugString

struct Hen : IHen2, IOfflineChicken
{
    long m_count;
    Hen() : m_count(0)
    {
        static char* cheep("cheep\n");
        TRACE(cheep);
        std::cout << cheep;
    }

    ~Hen()
    {
        TRACE("Chicken soup!\n");
    }

    //
    // IUnknown
    //

    ULONG __stdcall AddRef()
    {
        return _InterlockedIncrement(&m_count);
    }

    ULONG __stdcall Release()
    {
        ULONG const result = _InterlockedDecrement(&m_count);
        if (0 == result)
        {
            delete this;
        }
        return result;
    }

    // IID is just a GUID. It's just customary to use IID when referring to
    // an interface ID GUID.
    // 
    // We need to turn off the C++ type system momentarily to allow COM's
    // runtime type discovery to be implemented portably and correctly.
    //
    HRESULT __stdcall QueryInterface(IID const& id, void** result)
    {
        ASSERT(result);

        if (id == __uuidof(IHen2) ||
            id == __uuidof(IHen) ||
            id == __uuidof(IUnknown))
        {
            *result = static_cast<IHen2*>(this);
        }
        else if (id == __uuidof(IOfflineChicken))
        {
            *result = static_cast<IOfflineChicken*>(this);
        }
        else
        {
            *result = 0;
            return E_NOINTERFACE;
        }

        // One of the rules of COM is that the Release function must
        // be called on the same interface that the AddRef function was
        // originally called on. This goes back to COM's object identity
        // laws, which we'll cover in due course.
        static_cast<IUnknown*>(*result)->AddRef();
        return S_OK;
    }

    //
    // IHen
    //

    void __stdcall Cluck()
    {
        static const char* cluck("Cluck\n");
        TRACE(cluck);
        std::cout << cluck;
    }

    void __stdcall Roost()
    {
        TRACE("Zzzzzz!\n");
    }

    //
    // IHen2
    //

    void __stdcall Forage()
    {
        TRACE("Forage!\n");
    }

    //
    // IOfflineChicken
    //

    void __stdcall Load(char const* /*file*/)
    {

    }

    void __stdcall Save(char const* /*file*/)
    {

    }
};

// This version will return a null pointer if the allocation fails.

HRESULT __stdcall CreateHen(IHen** result)
{
    ASSERT(result);
    *result = new (std::nothrow) Hen;
    if (*result == 0)
    {
        return E_OUTOFMEMORY;
    }

    (*result)->AddRef();
    return S_OK;
}