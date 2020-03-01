#ifndef DEPTH_STENCIL_VIEW_H_
#define DEPTH_STENCIL_VIEW_H_

#include <type_traits>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/DepthStencilViewData.h"
#include "Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	// �uDepthStencilViewManager�v�̎����̈ꕔ���B�����߂̃N���X
	class DepthStencilView
	{
	public:

		// �V���Ȑ[�x�r���[���쐬����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ńr���[�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize)
		{
			createImpl(static_cast<int>(id), useTextureSize);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize) { static_assert(false, "DepthStencilViewId Fraud Type"); }

		// �w�肵���[�x�r���[���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �����̊֐��Ńr���[���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "DepthStencilViewId Fraud Type"); }

		// �w�肵���[�x�r���[���Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const DepthStencilViewData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const DepthStencilViewData& getData(IdType id) { static_assert(false, "DepthStencilViewId Fraud Type"); return nullptr; }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Vector2& useTextureSize);
		static void eraseImpl(int id);
		static const DepthStencilViewData& getDataImpl(int id);
	};
}
#endif // !DEPTH_STENCIL_VIEW_H_
