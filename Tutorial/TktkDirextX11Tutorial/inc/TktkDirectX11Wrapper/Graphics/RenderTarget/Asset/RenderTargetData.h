#ifndef RENDER_TARGET_DATA_H_
#define RENDER_TARGET_DATA_H_

#include <d3d11.h>

namespace tktk
{
	// �����_�[�^�[�Q�b�g���Ǘ�����N���X
	class RenderTargetData
	{
	public:

		explicit RenderTargetData(ID3D11Texture2D* renderTargetTexturePtr);
		~RenderTargetData();

		RenderTargetData(const RenderTargetData& other) = delete;
		RenderTargetData& operator = (const RenderTargetData& other) = delete;

	public:

		// �����_�[�^�[�Q�b�g�r���[�̃|�C���^���擾����
		ID3D11RenderTargetView* getViewPtr() const;

	private:

		// �����_�[�^�[�Q�b�g�r���[�̃|�C���^
		ID3D11RenderTargetView* m_viewPtr;
	};
}
#endif // !RENDER_TARGET_DATA_H_
