#ifndef TEXT_SPLITER_H_
#define TEXT_SPLITER_H_

#include <string>
#include <vector>

class TextSpliter
{
public:

	// �����̕�����������̕����ŋ�؂����f�[�^��string�^��vector�ɓ����
	// �P�x�ł���؂ꂽ��true�A��؂�Ȃ�������false���Ԃ�
	static bool textSplit(const std::string& beforSplitText, char spritChar, std::vector<std::string>* out);
};
#endif // !TEXT_SPLITER_H_