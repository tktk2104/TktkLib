#ifndef SCREEN_H_
#define SCREEN_H_

#include <vector>
#include <TktkMath/Color.h>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <d3d11.h>

namespace tktk
{
	// �uScreenManager�v�̎����̈ꕔ���B�����߂̃N���X
	class Screen
	{
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

	private:

		// setDepthStencilViewAndRenderTargets()�̎���
		static void setDepthStencilViewAndRenderTargetsImpl(int depthStencilViewId, const std::vector<int>& renderTargetIdArray);
	};
}
#endif // !SCREEN_H_
