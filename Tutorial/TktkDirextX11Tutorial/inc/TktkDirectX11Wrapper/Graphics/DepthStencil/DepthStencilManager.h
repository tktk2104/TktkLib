#ifndef DEPTH_STENCIL_MANAGER_H_
#define DEPTH_STENCIL_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilAssets.h"
#include "Asset/SystemDepthStencilId.h"

namespace tktk
{
	// �uDepthStencilAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class DepthStencilManager
	{
	public:

		// �uDepthStencilAssets�v�𐶐�
		static void setUp();

	public:

		// �V���Ȑ[�x�r���[���쐬����
		static void create(int id, const Vector2& useTextureSize);

		// �w�肵���[�x�r���[���폜����
		static void erase(int id);

		// �S�Ă̐[�x�r���[���폜����
		static void clear();

		// �w�肵���[�x�r���[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const DepthStencilData& getData(int id);

	private:

		static CfpPtr<DepthStencilAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_MANAGER_H_
