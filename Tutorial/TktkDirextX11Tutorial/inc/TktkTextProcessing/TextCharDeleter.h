#ifndef TEXT_CHAR_DELETER_H_
#define TEXT_CHAR_DELETER_H_

#include <string>
#include <vector>

class TextCharDeleter
{
public:

	// �����̕����񂩂�����̕������폜����
	// �폜�ł�����true�A�폜�ł��Ȃ�������false���Ԃ�
	static bool textCharDelete(const std::string& beforDeleteText, char deleteChar, std::string* out);

	// �����̕����񂩂�����̕����̔z��̗v�f�S�Ă��폜����
	// �폜�ł�����true�A�폜�ł��Ȃ�������false���Ԃ�
	static bool textCharDelete(const std::string& beforDeleteText, std::vector<char> deleteChars, std::string* out);
};
#endif // !TEXT_CHAR_DELETER_H_