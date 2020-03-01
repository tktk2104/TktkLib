#ifndef DEPTH_STENCIL_STATE_H_
#define DEPTH_STENCIL_STATE_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/DepthStencilStateData.h"
#include "Asset/SystemDepthStencilStateId.h"

namespace tktk
{
	class DepthStencilState
	{
	public:

		// �V���Ȑ[�x�X�e���V���X�e�[�g���쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ő[�x�X�e���V���X�e�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc)
		{
			createImpl(static_cast<int>(id), depthStencilDesc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// �w�肵���[�x�X�e���V���X�e�[�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ő[�x�X�e���V���X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

		// �w�肵���[�x�X�e���V���X�e�[�g���Ǘ�����N���X�̃|�C���^���擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static DepthStencilStateData* getDataPtr(IdType id)
		{
			return getDataPtrImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static DepthStencilStateData* getDataPtr(IdType id) { static_assert(false, "DepthStencilStateId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const D3D11_DEPTH_STENCIL_DESC& depthStencilDesc);
		static void eraseImpl(int id);
		static DepthStencilStateData* getDataPtrImpl(int id);
	};
}
#endif // !DEPTH_STENCIL_STATE_H_