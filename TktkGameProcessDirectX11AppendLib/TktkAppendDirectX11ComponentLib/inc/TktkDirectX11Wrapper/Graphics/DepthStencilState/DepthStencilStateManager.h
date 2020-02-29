#ifndef DEPTH_STENCIL_STATE_MANAGER_H_
#define DEPTH_STENCIL_STATE_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilStateAssets.h"

namespace tktk
{
	class DepthStencilStateManager
	{
	public:

		// �uDepthStencilStateAssets�v�𐶐�
		static void setUp();

	public:

		// �V���Ȑ[�x�X�e���V���X�e�[�g���쐬����
		static void create(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);

		// �w�肵���[�x�X�e���V���X�e�[�g���폜����
		static void erase(int id);

		// �S�Ă̐[�x�X�e���V���X�e�[�g���폜����
		static void clear();

		// �w�肵���[�x�X�e���V���X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����
		static DepthStencilStateData* getData(int id);

	private:

		static CfpPtr<DepthStencilStateAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_STATE_MANAGER_H_