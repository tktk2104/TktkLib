#ifndef DEPTH_STENCIL_DATA_H_
#define DEPTH_STENCIL_DATA_H_

#include <d3d11.h>
#include <TktkMath/Vector2.h>

namespace tktk
{
	// �[�x�o�b�t�@���Ǘ�����N���X
	class DepthStencilData
	{
	public:

		explicit DepthStencilData(const Vector2& useTextureSize);
		~DepthStencilData();

		DepthStencilData(const DepthStencilData& other) = delete;
		DepthStencilData& operator = (const DepthStencilData& other) = delete;

	public:

		// �[�x�r���[�̃|�C���^���擾����
		ID3D11DepthStencilView* getViewPtr() const;

	private:

		// �[�x�r���[�Ŏg�p����e�N�X�`���̃|�C���^
		ID3D11Texture2D*		m_useTexturePtr{ nullptr };

		// �[�x�r���[�̃|�C���^
		ID3D11DepthStencilView* m_viewPtr{ nullptr };
	};
}
#endif // !DEPTH_STENCIL_DATA_H_