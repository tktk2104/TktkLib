#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/VertexShaderData.h"
#include "Asset/SystemVertexShaderId.h"

namespace tktk
{
	// �uVertexShaderManager�v�̎����̈ꕔ���B�����߂̃N���X
	class VertexShader
	{
	public:

		// �V���Ȓ��_�V�F�[�_�[�����[�h����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��ŃV�F�[�_�[�����[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class ShaderIdType, class... ConstantBufferIdTypes, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdTypes...>>* = nullptr>
		static void load(ShaderIdType id, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout, ConstantBufferIdTypes... useConstantBufferIds)
		{
			loadImpl(static_cast<int>(id), { static_cast<int>(useConstantBufferIds)... }, fileName, vertexLayout);
		}
		template <class ShaderIdType, class... ConstantBufferIdTypes, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdTypes...>>* = nullptr>
		static void load(ShaderIdType id, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout, ConstantBufferIdTypes... useConstantBufferIds)
		{ static_assert(false, "Id Fraud Type"); }

		// �w�肵�����_�V�F�[�_�[���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��ŃV�F�[�_�[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

		// �w�肵�����_�V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const VertexShaderData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const VertexShaderData& getData(IdType id) { static_assert(false, "VertexShaderId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void loadImpl(int id, const std::vector<int>& useConstantBufferIdArray, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout);
		static void eraseImpl(int id);
		static const VertexShaderData& getDataImpl(int id);
	};
}
#endif // !VERTEX_SHADER_H_