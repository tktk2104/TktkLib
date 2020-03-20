#ifndef PIXEL_SHADER_DATA_H_
#define PIXEL_SHADER_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktk
{
	// �s�N�Z���V�F�[�_�[���Ǘ�����N���X
	class PixelShaderData
	{
	public:

		PixelShaderData(const std::vector<int>& useConstantBufferIdArray, const std::string& fileName);
		~PixelShaderData();

		// �R�s�[�֎~
		PixelShaderData(const PixelShaderData& other) = delete;
		PixelShaderData& operator = (const PixelShaderData& other) = delete;

	public:

		// �s�N�Z���V�F�[�_�[�ɒ萔�o�b�t�@��ݒ肵�ăf�o�C�X�R���e�L�X�g�ɐݒ肷��
		void beginShader() const;

		// ���̃s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@��Id�̔z����擾
		const std::vector<int>& getUseConstantBufferIdArray() const;

		// �s�N�Z���V�F�[�_�[�̃|�C���^���擾����
		ID3D11PixelShader* getShaderPtr() const;

	private:

		// ���̃s�N�Z���V�F�[�_�[���g�p����萔�o�b�t�@��Id�̔z��
		std::vector<int> m_useConstantBufferIdArray;

		// �s�N�Z���V�F�[�_�[�̃|�C���^
		ID3D11PixelShader* m_shaderPtr{ nullptr };
	};
}
#endif // !PIXEL_SHADER_DATA_H_