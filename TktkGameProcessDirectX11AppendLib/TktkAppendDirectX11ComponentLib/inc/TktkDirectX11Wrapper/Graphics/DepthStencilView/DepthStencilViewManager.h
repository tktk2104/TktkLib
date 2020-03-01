#ifndef DEPTH_STENCIL_VIEW_MANAGER_H_
#define DEPTH_STENCIL_VIEW_MANAGER_H_

#include <type_traits>
#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/DepthStencilViewAssets.h"
#include "Asset/SystemDepthStencilViewId.h"

namespace tktk
{
	// �uDepthStencilViewAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class DepthStencilViewManager
	{
	public:

		// �uDepthStencilViewAssets�v�𐶐�
		static void setUp();

	public:

		// �V���Ȑ[�x�r���[���쐬���� �e��id�w��n�̊֐��̎����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize)
		{
			createImpl(static_cast<int>(id), useTextureSize);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& useTextureSize) { static_assert(false, "DepthStencilViewId Fraud Type"); }

		// �w�肵���[�x�r���[���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
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

		// �S�Ă̐[�x�r���[���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Vector2& useTextureSize);
		static void eraseImpl(int id);
		static const DepthStencilViewData& getDataImpl(int id);

	private:

		static CfpPtr<DepthStencilViewAssets> m_assetsPtr;
	};
}
#endif // !DEPTH_STENCIL_VIEW_MANAGER_H_
