#ifndef SCREEN_H_
#define SCREEN_H_

#include <d3d11.h>
#include <TktkMath/Color.h>

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
	};
}
#endif // !SCREEN_H_
