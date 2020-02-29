#ifndef BLEND_STATE_MANAGER_H_
#define BLEND_STATE_MANAGER_H_

#include <type_traits>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/BlendStateAssets.h"

namespace tktk
{
	class BlendStateManager
	{
	private:

		// �e���v���[�g�����̌^��id��\����œK�؂��𔻒肷��萔
		template <class IdType>
		static constexpr bool is_idType = (std::is_enum_v<IdType> || std::is_integral_v<IdType>);

	public:

		// �uBlendStateAssets�v���쐬
		static void setUp();

	public:

		// �V���ȃu�����h�X�e�[�g���쐬����iint�ɕϊ��ł���^��id���n���ꂽ�ꍇ�j
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc)
		{
			createImpl(static_cast<int>(id), blendDesc);
		}
		// �V���ȃu�����h�X�e�[�g���쐬����i�s���Ȍ^��id���n���ꂽ�ꍇ�j
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc) { static_assert(false, "BlendStateId Fraud Value"); }

		// �w�肵���u�����h�X�e�[�g���폜����iint�ɕϊ��ł���^��id���n���ꂽ�ꍇ�j
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		// �w�肵���u�����h�X�e�[�g���폜����i�s���Ȍ^��id���n���ꂽ�ꍇ�j
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "BlendStateId Fraud Value"); }

		// �w�肵���u�����h�X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����iint�ɕϊ��ł���^��id���n���ꂽ�ꍇ�j
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		// �w�肵���u�����h�X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����i�s���Ȍ^��id���n���ꂽ�ꍇ�j
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id) { static_assert(false, "BlendStateId Fraud Value"); return nullptr; }

		// �S�Ẵu�����h�X�e�[�g���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const D3D11_BLEND_DESC& blendDesc);
		static void eraseImpl(int id);
		static BlendStateData* getDataPtrImpl(int id);

	private:

		static CfpPtr<BlendStateAssets> m_assetsPtr;
	};
}
#endif // !BLEND_STATE_MANAGER_H_