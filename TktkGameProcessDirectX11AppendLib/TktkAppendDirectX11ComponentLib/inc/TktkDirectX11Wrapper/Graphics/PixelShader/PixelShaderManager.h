#ifndef PIXEL_SHADER_MANAGER_H_
#define PIXEL_SHADER_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/PixelShaderAssets.h"
#include "Asset/SystemPixelShaderId.h"

namespace tktk
{
	// �uPixelShaderAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class PixelShaderManager
	{
	public:

		// �uPixelShaderAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃs�N�Z���V�F�[�_�[�����[�h����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName)
		{
			loadImpl(static_cast<int>(id), static_cast<int>(useConstantBufferId), fileName);
		}
		template <class ShaderIdType, class ConstantBufferIdType, std::enable_if_t<!is_idType_all_v<ShaderIdType, ConstantBufferIdType>>* = nullptr>
		static void load(ShaderIdType id, ConstantBufferIdType useConstantBufferId, const std::string& fileName) { static_assert(false, "Id Fraud Type"); }

		// �w�肵���s�N�Z���V�F�[�_�[���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
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

		// �S�Ẵs�N�Z���V�F�[�_�[���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void loadImpl(int id, int useConstantBufferId, const std::string& fileName);
		static void eraseImpl(int id);
		static const PixelShaderData& getDataImpl(int id);

	private:

		static CfpPtr<PixelShaderAssets> m_assetsPtr;
	};
}
#endif // !PIXEL_SHADER_MANAGER_H_