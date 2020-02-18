#ifndef TEXTURE_2D_H_
#define TEXTURE_2D_H_

#include <string>
#include "Asset/Texture2DData.h"

namespace tktk
{
	// �uTexture2DManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Texture2D
	{
	public:

		// �V����2D�e�N�X�`�������[�h����
		// �����̊֐���2D�e�N�X�`�������[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void load(int id, const std::string& fileName);

		// �w�肵��2D�e�N�X�`�����폜����
		// �����̊֐���2D�e�N�X�`�����폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵��2D�e�N�X�`�����Ǘ�����N���X�̎Q�Ƃ��擾����
		static const Texture2DData& getData(int id);
	};
}
#endif // !TEXTURE_2D_H_