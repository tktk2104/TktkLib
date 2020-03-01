#ifndef VIEW_PORT_MANAGER_H_
#define VIEW_PORT_MANAGER_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/ViewPortAssets.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	// �uViewPortAssets�v�ɊȒP�ɃA�N�Z�X���邽�߂̃N���X
	class ViewPortManager
	{
	public:

		// �uViewPortAssets�v�𐶐�
		static void setUp();

	public:

		// �V���ȃr���[�|�[�g�𐶐�����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size)
		{
			createImpl(static_cast<int>(id), position, size);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size) { static_assert(false, "ViewPortId Fraud Type"); }

		// �w�肵���r���[�|�[�g���폜����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

		// �w�肵���r���[�|�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

		// �S�Ẵr���[�|�[�g���폜����
		static void clear();

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Vector2& position, const Vector2& size);
		static void eraseImpl(int id);
		static const ViewPortData& getDataImpl(int id);

	private:

		static CfpPtr<ViewPortAssets> m_assetsPtr;
	};
}
#endif // !VIEW_PORT_MANAGER_H_