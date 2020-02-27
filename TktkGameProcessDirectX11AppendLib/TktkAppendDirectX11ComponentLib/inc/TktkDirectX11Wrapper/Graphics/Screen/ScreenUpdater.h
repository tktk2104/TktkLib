#ifndef SCREEN_UPDATER_H_
#define SCREEN_UPDATER_H_

#include <string>
#include <vector>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <d3d11.h>
#include "../../Utility/WindownsHeaderIncluder.h"

namespace tktk
{
	// ��ʂ̍X�V�A�`����s���N���X
	class ScreenUpdater
	{
	public:

		explicit ScreenUpdater(bool fullScreen);
		~ScreenUpdater();

		ScreenUpdater(const ScreenUpdater& other) = delete;
		ScreenUpdater& operator = (const ScreenUpdater& other) = delete;

	public:

		void start();
		void frameBegin();
		void draw();
		void frameEnd();
		float getDrawPriority();

	public:

		// �X���b�v�`�F�C���̃|�C���^���擾����
		IDXGISwapChain* getSwapChainPtr() const;

		// �f�o�C�X�̃|�C���^���擾����
		ID3D11Device* getDevicePtr() const;

		// �f�o�C�X�R���e�L�X�g�̃|�C���^���擾����
		ID3D11DeviceContext* getDeviceContextPtr() const;

		// ��ʂ̔w�i�F��ݒ肷��
		void setBackgroundColor(const Color& color);

		// �����_�[�^�[�Q�b�g�Ɛ[�x�X�e���V���r���[��ݒ肷��
		void setRenderTargetsAndDepthStencilView(const std::vector<int>& renderTargetIdArray, int depthStencilViewId);

	private:

		// �X���b�v�`�F�C���̃|�C���^
		IDXGISwapChain*			m_swapChainPtr;

		// �f�o�C�X�̃|�C���^
		ID3D11Device*			m_devicePtr;

		// �f�o�C�X�R���e�L�X�g�̃|�C���^
		ID3D11DeviceContext*	m_deviceContextPtr;

		// ���b�Z�[�W�����p�̕ϐ�
		MSG						m_msg{};

		// �t���X�N���[���t���O
		bool m_fullScreen{ false };

		// ��ʂ̔w�i�F
		Color m_backGroundColor{ Color::black };
	};
}
#endif // !SCREEN_UPDATER_H_