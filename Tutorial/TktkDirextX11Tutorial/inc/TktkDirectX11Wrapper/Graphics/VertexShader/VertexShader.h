#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include "Asset/VertexShaderData.h"
#include "Asset/SystemVertexShaderId.h"

namespace tktk
{
	// �uVertexShaderManager�v�̎����̈ꕔ���B�����߂̃N���X
	class VertexShader
	{
	public:

		// �V���Ȓ��_�V�F�[�_�[�����[�h����
		// �����̊֐��ŃV�F�[�_�[�����[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void load(
			int id,
			int useConstantBufferId,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);

		// �w�肵�����_�V�F�[�_�[���폜����
		// �����̊֐��ŃV�F�[�_�[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		static void erase(int id);

		// �w�肵�����_�V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const VertexShaderData& getData(int id);
	};
}
#endif // !VERTEX_SHADER_H_