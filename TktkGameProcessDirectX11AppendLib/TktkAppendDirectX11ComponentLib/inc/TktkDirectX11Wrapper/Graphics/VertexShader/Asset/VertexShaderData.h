#ifndef VERTEX_SHADER_DATA_H_
#define VERTEX_SHADER_DATA_H_

#include <string>
#include <vector>
#include <d3d11.h>

namespace tktk
{
	// ���_�V�F�[�_�[���Ǘ�����N���X
	class VertexShaderData
	{
	public:

		VertexShaderData(
			const std::vector<int>& useConstantBufferIdArray,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);
		~VertexShaderData();

		VertexShaderData(const VertexShaderData& other) = delete;
		VertexShaderData& operator = (const VertexShaderData& other) = delete;

	public:

		// ���_�V�F�[�_�[�ɒ萔�o�b�t�@��ݒ肵�ăf�o�C�X�R���e�L�X�g�ɐݒ肷��
		void beginVertexShader() const;

		// ���̒��_�V�F�[�_�[���g�p����萔�o�b�t�@��Id�̔z����擾
		const std::vector<int>& getUseConstantBufferIdArray() const;

		// ���_�V�F�[�_�[�̃|�C���^���擾����
		ID3D11VertexShader* getShaderPtr() const;

		// ���̓��C�A�E�g�̃|�C���^���擾����
		ID3D11InputLayout* getVertexLayoutPtr() const;

	private:

		// ���̒��_�V�F�[�_�[���g�p����萔�o�b�t�@��Id�̔z��
		std::vector<int> m_useConstantBufferIdArray;

		// ���_�V�F�[�_�[�̃|�C���^
		ID3D11VertexShader* m_vertexShaderPtr{ nullptr };

		// ���̓��C�A�E�g�̃|�C���^
		ID3D11InputLayout*	m_vertexLayoutPtr{ nullptr };
	};
}
#endif // !VERTEX_SHADER_DATA_H_