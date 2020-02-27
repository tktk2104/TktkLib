#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "ScreenUpdater.h"

namespace tktk
{
	// �uScreenUpdater�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class ScreenManager
	{
	public:

		// �uScreenUpdater�v�𐶐�
		static void setUp(bool fullScreen);

	public:

		// �X���b�v�`�F�C���̃|�C���^���擾����
		static IDXGISwapChain* getSwapChainPtr();

		// �f�o�C�X�̃|�C���^���擾����
		static ID3D11Device* getDevicePtr();

		// �f�o�C�X�R���e�L�X�g�̃|�C���^���擾����
		static ID3D11DeviceContext* getDeviceContextPtr();

		// ��ʂ̔w�i�F��ݒ肷��
		static void setBackgroundColor(const Color& color);

		// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[��ݒ肷��
		static void setRenderTargetsAndDepthStencilView(const std::vector<int>& renderTargetIdArray, int depthStencilViewId);

	private:

		static CfpPtr<ScreenUpdater> m_updaterPtr;
	};
}
#endif // !SCREEN_MANAGER_H_
