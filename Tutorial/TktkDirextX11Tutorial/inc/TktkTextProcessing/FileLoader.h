#ifndef FILE_LOADER_H_
#define FILE_LOADER_H_

#include <string>
#include <vector>

class FileLoader
{
public:

	// �����̃t�@�C���̍s���ƃf�[�^��string�^��vector�ɓ����
	// �ǂݍ��݂Ɏ��s�����ꍇ��false���Ԃ�
	static bool fileLoad(const std::string& filePath, std::vector<std::string>* out);
};
#endif // !FILE_LOADER_H_