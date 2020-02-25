#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/VertexShaderAssets.h"
#include "Asset/SystemVertexShaderId.h"

namespace tktk
{
	// �uVertexShaderAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class VertexShaderManager
	{
	public:

		// �uVertexShaderAssets�v�𐶐�
		static void setUp();

	public:

		// �V���Ȓ��_�V�F�[�_�[�����[�h����
		static void load(
			int id,
			int useConstantBufferId,
			const std::string& fileName,
			const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout
		);

		// �w�肵�����_�V�F�[�_�[���폜����
		static void erase(int id);

		// �S�Ă̒��_�V�F�[�_�[���폜����
		static void clear();

		// �w�肵�����_�V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		static const VertexShaderData& getData(int id);

	private:

		static CfpPtr<VertexShaderAssets> m_assetsPtr;
	};
}
#endif // !VERTEX_SHADER_MANAGER_H_
