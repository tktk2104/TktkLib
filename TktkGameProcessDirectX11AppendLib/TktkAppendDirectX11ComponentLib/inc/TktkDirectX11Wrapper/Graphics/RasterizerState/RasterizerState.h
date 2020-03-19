#ifndef RASTERIZER_STATE_H_
#define RASTERIZER_STATE_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/RasterizerStateData.h"
#include "Asset/SystemRasterizerStateId.h"

namespace tktk
{
	// �uRasterizerStateManager�v�̎����̈ꕔ���B�����߂̃N���X
	class RasterizerState
	{
	public:

		// �V���ȃ��X�^���C�U�X�e�[�g���쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ń��X�^���C�U�X�e�[�g���쐬����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_RASTERIZER_DESC& desc)
		{
			createImpl(static_cast<int>(id), desc);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const D3D11_RASTERIZER_DESC& desc) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// �w�肵�����X�^���C�U�X�e�[�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ń��X�^���C�U�X�e�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }

		// �w�肵�����X�^���C�U�X�e�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const RasterizerStateData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const RasterizerStateData& getData(IdType id) { static_assert(false, "RasterizerStateId Fraud Type"); }
	
	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const D3D11_RASTERIZER_DESC& desc);
		static void eraseImpl(int id);
		static const RasterizerStateData& getDataImpl(int id);
	};
}
#endif // !RASTERIZER_STATE_H_
