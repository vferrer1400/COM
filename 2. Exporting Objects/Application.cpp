#include "Precompiled.h"
#include "Library.h"

#pragma comment(lib, "rpcrt4.lib")

template <typename T>
class RemoveAddRefRelease : public T
{
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
};

template <typename T>
struct ComPtr
{
    T* m_ptr;

public:
    ComPtr() : m_ptr(0){}
    ~ComPtr()
    {
        if (m_ptr)
        {
            m_ptr->Release();
        }
    }

    RemoveAddRefRelease<T>* operator ->() const
    {
        ASSERT(m_ptr);
        return static_cast<RemoveAddRefRelease<T>*>(m_ptr);
    }

    T** GetAddressOf()
    {
        return &m_ptr;
    }
};

int main()
{
    //IHen* hen;
    ComPtr<IHen> hen;
    if(S_OK != CreateHen(&hen.m_ptr))
        return 0;

    hen->Cluck();

    //IHen2* hen2;
    ComPtr<IHen2> hen2;

    //if (S_OK == hen->QueryInterface(__uuidof(IHen2), reinterpret_cast<void**>(&hen2)))
    if(S_OK == hen->QueryInterface(hen2.GetAddressOf()))
    {
        hen2->Forage();
        //hen2->Release();
    }

    //IOfflineChicken* offline;

    ComPtr<IOfflineChicken> offline;
    if (S_OK == hen->QueryInterface(offline.GetAddressOf()))
    {
        offline->Save("filename");
        //offline->Release();
    }

    //hen->Release();

    return 0;
}