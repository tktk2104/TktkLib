#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		// �[�x�X�e���V���r���[�ƃ����_�[�^�[�Q�b�g��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class DepthStencilViewIdType, class... RenderTargetIdType, std::enable_if_t<is_idType_v<DepthStencilViewIdType> && is_idType_all_v<RenderTargetIdType...>>* = nullptr>
		static void setDepthStencilViewAndRenderTargets(DepthStencilViewIdType depthStencilViewId, RenderTargetIdType... renderTargetIds)
		{
			setDepthStencilViewAndRenderTargetsImpl(static_cast<int>(depthStencilViewId), { static_cast<int>(renderTargetIds)... });
		}
		template <class DepthStencilViewIdType, class... RenderTargetIdType, std::enable_if_t<!(is_idType_v<DepthStencilViewIdType> && is_idType_all_v<RenderTargetIdType...>)>* = nullptr>
		static void setDepthStencilViewAndRenderTargets(DepthStencilViewIdType depthStencilViewId, RenderTargetIdType... renderTargetIds)
		{
			static_assert(false, "Id Fraud Type");
		}

		// �r���[�|�[�g��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void setViewport(IdType viewPortId)
		{
			setViewportImpl(static_cast<int>(viewPortId));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void setViewport(IdType viewPortId) { static_assert(false, "ViewportId Fraud Type"); }

		// setDepthStencilViewAndRenderTargets()�̎���
		static void setDepthStencilViewAndRenderTargetsImpl(int depthStencilViewId, const std::vector<int>& renderTargetIdArray);
	private:

		// setViewport()�̎���
		static void setViewportImpl(int viewPortId);

	private:

		static CfpPtr<ScreenUpdater> m_updaterPtr;
	};
}
#endif // !SCREEN_MANAGER_H_
