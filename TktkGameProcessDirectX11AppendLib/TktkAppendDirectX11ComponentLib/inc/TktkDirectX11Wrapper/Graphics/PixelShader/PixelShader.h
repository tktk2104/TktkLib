#ifndef PIXEL_SHADER_H_
#define PIXEL_SHADER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/PixelShaderData.h"
#include "Asset/SystemPixelShaderId.h"

namespace tktk
{
	// �uPixelShaderManager�v�̎����̈ꕔ���B�����߂̃N���X
	class PixelShader
	{
	public:

		// �V���ȃs�N�Z���V�F�[�_�[�����[�h����
		// �����̊֐��ŃV�F�[�_�[�����[�h����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class ShaderIdType, class... ConstantBufferIdTypes, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdTypes...>>* = nullptr>
		static void load(const std::string& fileName, ShaderIdType id, ConstantBufferIdTypes... useConstantBufferIds)
		{
			loadImpl(static_cast<int>(id), { static_cast<int>(useConstantBufferIds)... }, fileName);
		}
		template <class ShaderIdType, class... ConstantBufferIdTypes, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdTypes...>>* = nullptr>
		static void load(const std::string& fileName, ShaderIdType id, ConstantBufferIdTypes... useConstantBufferIds) { static_assert(false, "Id Fraud Type"); }

		// �w�肵���s�N�Z���V�F�[�_�[���폜����
		// �����̊֐��ŃV�F�[�_�[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

		// �w�肵���s�N�Z���V�F�[�_�[���Ǘ�����N���X�̎Q�Ƃ��擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const PixelShaderData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const PixelShaderData& getData(IdType id) { static_assert(false, "PixelShaderId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void loadImpl(int id, const std::vector<int>& useConstantBufferIdArray, const std::string& fileName);
		static void eraseImpl(int id);
		static const PixelShaderData& getDataImpl(int id);
	};
}
#endif // !PIXEL_SHADER_H_
