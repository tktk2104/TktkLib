#ifndef VIEW_PORT_H_
#define VIEW_PORT_H_

#include <TktkMetaFunc/TypeCheck/isIdType.h>
#include "Asset/ViewPortData.h"
#include "Asset/SystemViewPortId.h"

namespace tktk
{
	class ViewPort
	{
	public:

		// �V���ȃr���[�|�[�g�𐶐�����
		// �����̊֐��Ńr���[�|�[�g�����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size)
		{
			createImpl(static_cast<int>(id), position, size);
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void create(IdType id, const Vector2& position, const Vector2& size) { static_assert(false, "ViewPortId Fraud Type"); }

		// �w�肵���r���[�|�[�g���폜����
		// �����̊֐��Ńr���[�|�[�g���폜����ꍇ�Aid��1�ȏ�łȂ���΂Ȃ�Ȃ�
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id)
		{
			eraseImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static void erase(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

		// �w�肵���r���[�|�[�g���Ǘ�����N���X�̎Q�Ƃ��擾����
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id)
		{
			return getDataImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		static const ViewPortData& getData(IdType id) { static_assert(false, "ViewPortId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		static void createImpl(int id, const Vector2& position, const Vector2& size);
		static void eraseImpl(int id);
		static const ViewPortData& getDataImpl(int id);
	};
}
#endif // !VIEW_PORT_H_