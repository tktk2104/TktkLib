#ifndef VERTEX_SHADER_MANAGER_H_
#define VERTEX_SHADER_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
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

		// �V���Ȓ��_�V�F�[�_�[�����[�h����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
		{
			loadImpl(static_cast<int>(id), static_cast<int>(useConstantBufferId), fileName, vertexLayout);
		}
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout)
		{ static_assert(false, "Id Fraud Type"); }

		// �w�肵�����_�V�F�[�_�[���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
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

		// �S�Ă̒��_�V�F�[�_�[���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void loadImpl(int id, int useConstantBufferId, const std::string& fileName, const std::vector<D3D11_INPUT_ELEMENT_DESC>& vertexLayout);
		static void eraseImpl(int id);
		static const VertexShaderData& getDataImpl(int id);

	private:

		static CfpPtr<VertexShaderAssets> m_assetsPtr;
	};
}
#endif // !VERTEX_SHADER_MANAGER_H_
