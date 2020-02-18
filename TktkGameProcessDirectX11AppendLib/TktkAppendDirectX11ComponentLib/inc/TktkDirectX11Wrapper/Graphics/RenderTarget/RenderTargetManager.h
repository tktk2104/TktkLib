#ifndef RENDER_TARGET_MANAGER_H_
#define RENDER_TARGET_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/RenderTargetAssets.h"
#include "Asset/SystemRenderTargetId.h"

namespace tktk
{
	// �uRenderTargetAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class RenderTargetManager
	{
	public:

		// �uRenderTargetAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃ����_�[�^�[�Q�b�g�𐶐�����
		static void create(int id, ID3D11Texture2D* renderTargetTexture);

		// �w�肵�������_�[�^�[�Q�b�g���폜����
		static void erase(int id);

		// �S�Ẵ����_�[�^�[�Q�b�g���폜����
		static void clear();

		// �w�肵�������_�[�^�[�Q�b�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const RenderTargetData& getData(int id);

	private:

		static CfpPtr<RenderTargetAssets> m_assetsPtr;
	};
}
#endif // !RENDER_TARGET_MANAGER_H_