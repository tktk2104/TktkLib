#ifndef BLEND_STATE_H_
#define BLEND_STATE_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/BlendStateData.h"
#include "Asset/SystemBlendStateId.h"

namespace tktk
{
	// �uBlendStateManager�v�̎����̈ꕔ���B�����߂̃N���X
	class BlendState
	{
	public:

		// �V���ȃu�����h�X�e�[�g���쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ńu�����h�X�e�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc)
		{
			createImpl(static_cast<int>(id), blendDesc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_BLEND_DESC& blendDesc) { static_assert(false, "BlendStateId Fraud Type"); }

		// �w�肵���u�����h�X�e�[�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ńu�����h�X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "BlendStateId Fraud Type"); }

		// �w�肵���u�����h�X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static BlendStateData* getDataPtr(IdType id) { static_assert(false, "BlendStateId Fraud Type"); return nullptr; }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const D3D11_BLEND_DESC& blendDesc);
		static void eraseImpl(int id);
		static BlendStateData* getDataPtrImpl(int id);
	};
}
#endif // !BLEND_STATE_H_