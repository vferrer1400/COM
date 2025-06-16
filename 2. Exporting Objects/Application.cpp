#include "Precompiled.h"

#pragma comment(lib, "rpcrt4.lib")

// Taming the GUID
//
// GUID's weren't invented by COM designers; they in fact borrowed it from RPC
// 
// * 128 bit value
//
// * Globally unique identifier
//  - typedef GUID UUID
//  - typedef GUID IID
//  - typedef GUID CLSID
//


int main()
{
    
    /*ASSERT(RPC_S_OK == UuidCreate(&guid));
     *
     * This could theoretically fail if you happen to be running on a PC
     * without a network adaptor of some kind. 
     *
     * Now that RPC funtion is not using HRESULTs; that RPC_S_OK might
     * look similar to the HRESULTs, but they are not.
     * 
     * A convinient solution is to use COM's co-create GUID function.which
     * simply wraps the RPC function, but turns that RPC status code into
     * an HRESULT
     */
    GUID guid;
    HR(CoCreateGuid(&guid));

    //unsigned short* rpc_string;
    unsigned char* rpc_string;
    // This function uses a custom RPC allocator. It possibly fail if it ran out of memory.
    ASSERT(RPC_S_OK == UuidToString(&guid, &rpc_string));
    TRACE("%s\n", rpc_string);

    // Produce a GUID given a string using an RPC function
    // This function expects the string GUID to be formatted in the RPC way.
    GUID guid2;
    ASSERT(RPC_S_OK == UuidFromString(rpc_string, &guid2));

    // This is the RPC function to free the memory
    ASSERT(RPC_S_OK == RpcStringFree(&rpc_string));

    wchar_t ole_string[39];
    // The line between what is OLE and what is COM is fuzzy. So lets refer to this
    // as COM functions

    // OLE/COM function for turning a GUID into a string
    // Only drawback with this is that this doesn't use an allocator.
    ASSERT(StringFromGUID2(guid, ole_string, _countof(ole_string)));
    TRACE(L"%s\n", ole_string);

    std::wstring std_string(ole_string + 1, _countof(ole_string) - 3);
    TRACE(L"%s\n", std_string.c_str());

    // COM function to generate a GUID from a string usinf COM GUID style
    HR(CLSIDFromString(ole_string, &guid2));

    // We can also parsed an standard string using the RPC function
    //auto wchar_string = const_cast<wchar_t*>(std_string.c_str());
    //unsigned char* unsafeCast = reinterpret_cast<unsigned char*>(wchar_string);
    std::vector<unsigned char> buffer;
    if (WCharToUnsignedChar(std_string.c_str(), buffer))
    {
        ASSERT(RPC_S_OK == UuidFromString(buffer.data(), &guid2));
    }


    return 0;
}