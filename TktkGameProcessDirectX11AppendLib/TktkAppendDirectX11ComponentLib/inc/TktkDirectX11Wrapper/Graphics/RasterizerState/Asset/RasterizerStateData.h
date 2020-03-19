#ifndef RASTERIZER_STATE_DATA_H_
#define RASTERIZER_STATE_DATA_H_

#include <d3d11.h>

namespace tktk
{
	class RasterizerStateData
	{
	public:

		RasterizerStateData(const D3D11_RASTERIZER_DESC& desc);
		~RasterizerStateData();

		// �R�s�[�֎~
		RasterizerStateData(const RasterizerStateData& other) = delete;
		RasterizerStateData& operator = (const RasterizerStateData& other) = delete;

	public:

		// �����_�����O�p�C�v���C���Ƀ��X�^���C�U�[�X�e�[�g��ݒ肷��
		void setState() const;

	private:

		ID3D11RasterizerState* m_rasterizerStatePtr{ nullptr };
	};
}
#endif // !RASTERIZER_STATE_DATA_H_
