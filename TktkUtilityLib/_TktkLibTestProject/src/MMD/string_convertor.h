#ifndef STRING_CONVERTOR_H_
#define STRING_CONVERTOR_H_

#include <string>
#include <vector>

// UTF8‚ðSJIS‚É•ÏŠ·
std::string utf8_to_sjis(const std::vector<unsigned char>& utf8);

// UTF16‚ðSJIS‚É•ÏŠ·
std::string utf16_to_sjis(const std::vector<unsigned char>& utf16);

// SJIS‚ðUTF16‚É•ÏŠ·
std::vector<unsigned char> sjis_to_utf16(const std::string& sjis);

// SJIS‚ðwchar‚É•ÏŠ·
std::string wchar_to_sjis(const std::wstring& utf16);

// SJIS‚ðwchar‚É•ÏŠ·
std::wstring sjis_to_wchar(const std::string& sjis);

// wchar‚ðSJIS‚É•ÏŠ·
std::string wchar_to_sjis(const std::wstring& utf16);

#endif

// end of file
