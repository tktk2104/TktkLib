#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// �X�v���C�g�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(float drawPriority, unsigned int spriteMaterialId, unsigned int useRtvDescriptorHeapId);

	public:

		void start();
		void draw() const;

	public:

		// �e�N�X�`��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, std::enable_if_t<is_idType_v<IdType>>* = nullptr>
		void setSpriteMaterialId(IdType id)
		{
			setSpriteMaterialIdImpl(static_cast<int>(id));
		}
		template <class IdType, std::enable_if_t<!is_idType_v<IdType>>* = nullptr>
		void setSpriteMaterialId(IdType id) { static_assert(false, "SpriteMaterialId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		void setSpriteMaterialIdImpl(int id);

	private:

		unsigned int				m_useRtvDescriptorHeapId;
		unsigned int				m_spriteMaterialId;
		ComponentPtr<Transform2D>	m_transform			{ };
	};
}
#endif // !SPRITE_DRAWER_H_
