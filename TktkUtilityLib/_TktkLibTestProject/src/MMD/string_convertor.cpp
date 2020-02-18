#include "string_convertor.h"
#include <Windows.h>

// UTF8��SJIS�ɕϊ�
std::string utf8_to_sjis(const std::vector<unsigned char>& utf8) {
	if (utf8.empty()) return std::string();
	// Unicode�֕ϊ���̕����񒷂𓾂�
	const int length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)&utf8[0], utf8.size(), NULL, 0);
	// �K�v�ȕ�����Unicode������̃o�b�t�@���m��
	std::vector<wchar_t> unicode(length);
	// UTF8����Unicode�֕ϊ�
	MultiByteToWideChar(CP_UTF8, 0, (LPCCH)&utf8[0], utf8.size(), &unicode[0], unicode.size());
	// ShiftJIS�֕ϊ���̕����񒷂𓾂�
	const int lengthSJis = WideCharToMultiByte(CP_ACP, 0, &unicode[0], unicode.size(), NULL, 0, NULL, NULL);
	// �K�v�ȕ�����ShiftJIS������̃o�b�t�@���m��
	std::vector<char> sjis(lengthSJis);
	// Unicode����ShiftJIS�֕ϊ�
	WideCharToMultiByte(CP_ACP, 0, &unicode[0], unicode.size(), &sjis[0], sjis.size(), NULL, NULL);
	return std::string(sjis.begin(), sjis.end());
}

// UTF16��SJIS�ɕϊ�
std::string utf16_to_sjis(const std::vector<unsigned char>& utf16) {
	if (utf16.empty()) return std::string();
	// ShiftJIS�֕ϊ���̕����񒷂𓾂�
	const int lengthSJis = WideCharToMultiByte(CP_ACP, 0, (LPWCH)&utf16[0], utf16.size() / 2, NULL, 0, NULL, NULL);
	// �K�v�ȕ�����ShiftJIS������̃o�b�t�@���m��
	std::vector<char> sjis(lengthSJis);
	// Unicode����ShiftJIS�֕ϊ�
	WideCharToMultiByte(CP_ACP, 0, (LPWCH)&utf16[0], utf16.size(), &sjis[0], sjis.size(), NULL, NULL);
	return std::string(sjis.begin(), sjis.end());
}

// SJIS��UTF16�ɕϊ�
std::vector<unsigned char> sjis_to_utf16(const std::string& sjis) {
	std::vector<unsigned char> result;
	if (sjis.empty()) return result;
	// Shift-JIS�����񂩂�UTF-16�ɕϊ������Ƃ��̕����񒷂����߂�
	const int length = MultiByteToWideChar(CP_ACP, 0, sjis.c_str(), sjis.size(), NULL, 0);
	// UTF-16������̗̈���m�ۂ���B
	result.resize(length * 2);
	// Shift-JIS�����񂩂�UTF-16�ɕϊ�����B
	MultiByteToWideChar(CP_ACP, 0, sjis.c_str(), sjis.size(), (LPWCH)&result[0], result.size() / 2);
	return result;
}

// SJIS��wchar�ɕϊ�
std::wstring sjis_to_wchar(const std::string& sjis) {
	std::vector<unsigned char> result = sjis_to_utf16(sjis);
	result.push_back(0); result.push_back(0); // wchar��\0
	return std::wstring((wchar_t*)result.data());
}

// wchar��SJIS�ɕϊ�
std::string wchar_to_sjis(const std::wstring& utf16) {
	std::vector<unsigned char> wchar(utf16.size() * 2);
	memcpy((char*)wchar.data(), (char*)utf16.c_str(), utf16.size() * 2);
	return utf16_to_sjis(wchar);
}


// end of file
