#include "string_convertor.h"
#include <Windows.h>

// UTF8をSJISに変換
std::string utf8_to_sjis(const std::vector<unsigned char>& utf8) {
	if (utf8.empty()) return std::string();
	// Unicodeへ変換後の文字列長を得る
	const int length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)&utf8[0], utf8.size(), NULL, 0);
	// 必要な分だけUnicode文字列のバッファを確保
	std::vector<wchar_t> unicode(length);
	// UTF8からUnicodeへ変換
	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)&utf8[0], utf8.size(), &unicode[0], unicode.size());
	// ShiftJISへ変換後の文字列長を得る
	const int lengthSJis = WideCharToMultiByte(CP_ACP, 0, &unicode[0], unicode.size(), NULL, 0, NULL, NULL);
	// 必要な分だけShiftJIS文字列のバッファを確保
	std::vector<char> sjis(lengthSJis);
	// UnicodeからShiftJISへ変換
	WideCharToMultiByte(CP_ACP, 0, &unicode[0], unicode.size(), &sjis[0], sjis.size(), NULL, NULL);
	return std::string(sjis.begin(), sjis.end());
}

// UTF16をSJISに変換
std::string utf16_to_sjis(const std::vector<unsigned char>& utf16) {
	if (utf16.empty()) return std::string();
	// ShiftJISへ変換後の文字列長を得る
	const int lengthSJis = WideCharToMultiByte(CP_ACP, 0, (LPWCH)&utf16[0], utf16.size() / 2, NULL, 0, NULL, NULL);
	// 必要な分だけShiftJIS文字列のバッファを確保
	std::vector<char> sjis(lengthSJis);
	// UnicodeからShiftJISへ変換
	WideCharToMultiByte(CP_ACP, 0, (LPWCH)&utf16[0], utf16.size(), &sjis[0], sjis.size(), NULL, NULL);
	return std::string(sjis.begin(), sjis.end());
}

// SJISをUTF16に変換
std::vector<unsigned char> sjis_to_utf16(const std::string& sjis) {
	std::vector<unsigned char> result;
	if (sjis.empty()) return result;
	// Shift-JIS文字列からUTF-16に変換したときの文字列長を求める
	const int length = MultiByteToWideChar(CP_ACP, 0, sjis.c_str(), sjis.size(), NULL, 0);
	// UTF-16文字列の領域を確保する。
	result.resize(length * 2);
	// Shift-JIS文字列からUTF-16に変換する。
	MultiByteToWideChar(CP_ACP, 0, sjis.c_str(), sjis.size(), (LPWCH)&result[0], result.size() / 2);
	return result;
}

// SJISをwcharに変換
std::wstring sjis_to_wchar(const std::string& sjis) {
	std::vector<unsigned char> result = sjis_to_utf16(sjis);
	result.push_back(0); result.push_back(0); // wcharの\0
	return std::wstring((wchar_t*)result.data());
}

// wcharをSJISに変換
std::string wchar_to_sjis(const std::wstring& utf16) {
	std::vector<unsigned char> wchar(utf16.size() * 2);
	memcpy((char*)wchar.data(), (char*)utf16.c_str(), utf16.size() * 2);
	return utf16_to_sjis(wchar);
}


// end of file
