#ifndef TEXTURE_2D_MANAGER_H_
#define TEXTURE_2D_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/Texture2DAssets.h"

namespace tktk
{
	// �uTexture2DAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class Texture2DManager
	{
	public:

		// �uTexture2DAssets�v�𐶐�
		static void setUp();

	public:

		// �V����2D�e�N�X�`�������[�h����
		static void load(int id, const std::string& fileName);

		// �w�肵��2D�e�N�X�`�����폜����
		static void erase(int id);

		// �S�Ă�2D�e�N�X�`�����폜����
		static void clear();

		// �w�肵��2D�e�N�X�`�����Ǘ�����N���X�̎Q�Ƃ��擾����
		static const Texture2DData& getData(int id);

	private:

		static CfpPtr<Texture2DAssets> m_assetsPtr;
	};
}
#endif // !TEXTURE_2D_MANAGER_H_