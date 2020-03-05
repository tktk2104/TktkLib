#ifndef VERTEX_SHADER_ASSETS_H_
#define VERTEX_SHADER_ASSETS_H_

#include <unordered_map>
#include "VertexShaderData.h"

namespace tktk
{
	// �uVertexShaderData�v���Ǘ�����N���X
	class VertexShaderAssets
	{
	public:

		VertexShaderAssets() = default;
		~VertexShaderAssets();

		VertexShaderAssets(const VertexShaderAssets& other) = delete;
		VertexShaderAssets& operator = (const VertexShaderAssets& other) = delete;

	public:

		// �V���Ȓ��_�V�F�[�_�[�����[�h����
		void load(
			int id,
			const std::vector<int>& useConstantBufferIdArray,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);

		// �w�肵�����_�V�F�[�_�[���폜����
		void erase(int id);

		// �S�Ă̒��_�V�F�[�_�[���폜����
		void clear();

		// �w�肵�����_�V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		const VertexShaderData& getData(int id) const;

	private:

		// ���_�V�F�[�_�[���Ǘ�����N���X�̘A�z�z��
		std::unordered_map<int, VertexShaderData> m_assets;
	};
}
#endif // !VERTEX_SHADER_ASSETS_H_