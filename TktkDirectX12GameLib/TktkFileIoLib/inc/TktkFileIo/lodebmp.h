#ifndef LODE_BMP_H_
#define LODE_BMP_H_

#include <string>
#include <vector>

namespace tktk
{
	// ���uOS/2�v�t�H�[�}�b�g�ɂ͖��Ή�
	class lodebmp
	{
	public:

		struct loadData
		{
			unsigned int width;
			unsigned int height;
			std::vector<unsigned char> data;
		};

	public:

		static void load(loadData* out, const std::string& fileName);
	};
}
#endif // !LODE_BMP_H_