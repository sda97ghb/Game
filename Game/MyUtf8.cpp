#include "MyUtf8.h"

#include <algorithm>
#include <codecvt>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <cstdint>

void my_utf8::setConsoleToUtf8()
{
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
    _setmode(_fileno(stderr), _O_U8TEXT);
}

void changeEndianness(std::wstring& string)
{
    for (wchar_t& c : string)
    {
        uint8_t* d = reinterpret_cast<uint8_t*>(&c);
        std::swap(d[0], d[1]);
    }
}

std::wstring my_utf8::convertToWString(const char* bytes,
                                       bool needChangeEndianness)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring wstr = convert.from_bytes(bytes);

    /*if (needChangeEndianness)
        changeEndianness(wstr);*/

    return wstr;
}

std::wstring my_utf8::convertToWString(const std::string& bytes,
                                       bool needChangeEndianness)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
    std::wstring wstr = convert.from_bytes(bytes);

    /*if (needChangeEndianness)
        changeEndianness(wstr);*/

    return wstr;
}

std::string my_utf8::convertToBytes(std::wstring string,
                                    bool needChangeEndianness)
{
    if (needChangeEndianness)
        changeEndianness(string);

    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

    return convert.to_bytes(string);
}
