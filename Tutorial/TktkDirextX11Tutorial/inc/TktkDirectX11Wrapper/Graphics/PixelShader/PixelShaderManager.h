#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/PixelShaderAssets.h"

namespace tktk
{
	// �uPixelShaderAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class PixelShaderManager
	{
	public:

		// �uPixelShaderAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃs�N�Z���V�F�[�_�[�����[�h����
		static void load(int id, int useConstantBufferId, const std::string& fileName);

		// �w�肵���s�N�Z���V�F�[�_�[���폜����
		static void erase(int id);

		// �S�Ẵs�N�Z���V�F�[�_�[���폜����
		static void clear();

		// �w�肵���s�N�Z���V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const PixelShaderData& getData(int id);

	private:

		static CfpPtr<PixelShaderAssets> m_assetsPtr;
	};
}
#endif // !PIXEL_SHADER_MANAGER_H_