#ifndef RECT_COLLIDER_EXTRUSION_MAKER_H_
#define RECT_COLLIDER_EXTRUSION_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RectColliderExtrusion.h"

namespace tktk
{
	class RectColliderExtrusionMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RectColliderExtrusionMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<RectColliderExtrusion> create();

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static RectColliderExtrusionMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_MAKER_H_