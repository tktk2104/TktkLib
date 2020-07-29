#ifndef RECT_COLLIDER_EXTRUSION_MAKER_H_
#define RECT_COLLIDER_EXTRUSION_MAKER_H_

#include "RectColliderExtrusion.h"

namespace tktk
{
	class RectColliderExtrusionMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		RectColliderExtrusionMaker() = default;
		RectColliderExtrusionMaker(const RectColliderExtrusionMaker& other) = default;
		RectColliderExtrusionMaker& operator = (const RectColliderExtrusionMaker& other) = default;

	public:

		// �C���X�^���X�쐬�J�n
		static RectColliderExtrusionMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<RectColliderExtrusion> create();

	private:

		// ���g�̃|�C���^
		static RectColliderExtrusionMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_MAKER_H_