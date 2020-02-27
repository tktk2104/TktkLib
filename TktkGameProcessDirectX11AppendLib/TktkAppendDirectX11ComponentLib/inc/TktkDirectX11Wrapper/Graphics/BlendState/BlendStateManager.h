#ifndef BLEND_STATE_MANAGER_H_
#define BLEND_STATE_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/BlendStateAssets.h"

namespace tktk
{
	class BlendStateManager
	{
	public:

		// �uBlendStateAssets�v���쐬
		static void setUp();

	public:

		// �V���ȃu�����h�X�e�[�g���쐬����
		static void create(int id, const D3D11_BLEND_DESC& blendDesc);

		// �w�肵���u�����h�X�e�[�g���폜����
		static void erase(int id);

		// �S�Ẵu�����h�X�e�[�g���폜����
		static void clear();

		// �w�肵���u�����h�X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����
		static BlendStateData* getDataPtr(int id);

	private:

		static CfpPtr<BlendStateAssets> m_assetsPtr;
	};
}
#endif // !BLEND_STATE_MANAGER_H_