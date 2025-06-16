#pragma once

#include <atlbase.h>
#include <string>
#include <vector>

#define TRACE ATLTRACE
#define ASSERT ATLASSERT

struct ComException
{
    HRESULT error;

    ComException(HRESULT hr) : error(hr) {}
};

inline void HR(HRESULT hr)
{
    if (S_OK != hr)
    {
        throw ComException(hr);
    }
}


// Converts a wide-character GUID string to an unsigned char buffer
// Returns true on success, false on failure
bool WCharToUnsignedChar(const wchar_t* wideStr, std::vector<unsigned char>& outBuffer) {
    if (!wideStr) return false;

    // Get required buffer size
    int size = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    if (size <= 0) return false;

    // Resize output buffer and convert
    outBuffer.resize(size);
    int result = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, reinterpret_cast<LPSTR>(outBuffer.data()), size, nullptr, nullptr);
    return result > 0;
}
