#ifndef PIXEL_SHADER_DATA_H_
#define PIXEL_SHADER_DATA_H_

#include <string>
#include <d3d11.h>

namespace tktk
{
	// �s�N�Z���V�F�[�_�[���Ǘ�����N���X
	class PixelShaderData
	{
	public:

		PixelShaderData(int useConstantBufferId, const std::string& fileName);
		~PixelShaderData();

		PixelShaderData(const PixelShaderData& other) = delete;
		PixelShaderData& operator = (const PixelShaderData& other) = delete;

	public:

		// �s�N�Z���V�F�[�_�[�ɒ萔�o�b�t�@��ݒ肵�ăf�o�C�X�R���e�L�X�g�ɐݒ肷��
		void beginShader() const;

		// ���̃s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@��Id���擾
		int getUseConstantBufferId() const;

		// �s�N�Z���V�F�[�_�[�̃|�C���^���擾����
		ID3D11PixelShader* getShaderPtr() const;

	private:

		// ���̃s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@��Id
		int m_useConstantBufferId;

		// �s�N�Z���V�F�[�_�[�̃|�C���^
		ID3D11PixelShader* m_shaderPtr{ nullptr };
	};
}
#endif // !PIXEL_SHADER_DATA_H_