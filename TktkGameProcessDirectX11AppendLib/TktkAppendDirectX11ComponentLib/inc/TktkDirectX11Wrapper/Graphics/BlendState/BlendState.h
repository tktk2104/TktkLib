#ifndef BLEND_STATE_H_
#define BLEND_STATE_H_

#include <type_traits>
#include "Asset/BlendStateData.h"

namespace tktk
{
	// �uBlendStateManager�v�̎����̈ꕔ���B�����߂̃N���X
	class BlendState
	{
	private:

		// �e���v���[�g�����̌^��id��\����œK�؂��𔻒肷��萔
		template <class IdType>
		static constexpr bool is_idType = (std::is_enum_v<IdType> || std::is_integral_v<IdType>);

	public:

		// �V���ȃu�����h�X�e�[�g���쐬����iint�ɕϊ��ł���^��id���n���ꂽ�ꍇ�j
		// �����̊֐��Ńu�����h�X�e�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc)
		{
			createImpl(static_cast<int>(id), blendDesc);
		}
		// �V���ȃu�����h�X�e�[�g���쐬����i�s���Ȍ^��id���n���ꂽ�ꍇ�j
		// �����̊֐��Ńu�����h�X�e�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<!is_idType<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc) { static_assert(false, "BlendStateId Fraud Value"); }

		// �w�肵���u�����h�X�e�[�g���폜����iint�ɕϊ��ł���^��id���n���ꂽ�ꍇ�j
		// �����̊֐��Ńu�����h�X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		// �w�肵���u�����h�X�e�[�g���폜����i�s���Ȍ^��id���n���ꂽ�ꍇ�j
		// �����̊֐��Ńu�����h�X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
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

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const D3D11_BLEND_DESC& blendDesc);
		static void eraseImpl(int id);
		static BlendStateData* getDataPtrImpl(int id);
	};
}
#endif // !BLEND_STATE_H_