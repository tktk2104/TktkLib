#ifndef STRING_CONVERTOR_H_
#define STRING_CONVERTOR_H_

#include <string>
#include <vector>

// UTF8��SJIS�ɕϊ�
std::string utf8_to_sjis(const std::vector<unsigned char>& utf8);

// UTF16��SJIS�ɕϊ�
std::string utf16_to_sjis(const std::vector<unsigned char>& utf16);

// SJIS��UTF16�ɕϊ�
std::vector<unsigned char> sjis_to_utf16(const std::string& sjis);

// SJIS��wchar�ɕϊ�
std::string wchar_to_sjis(const std::wstring& utf16);

// SJIS��wchar�ɕϊ�
std::wstring sjis_to_wchar(const std::string& sjis);

// wchar��SJIS�ɕϊ�
std::string wchar_to_sjis(const std::wstring& utf16);

#endif

// end of file
