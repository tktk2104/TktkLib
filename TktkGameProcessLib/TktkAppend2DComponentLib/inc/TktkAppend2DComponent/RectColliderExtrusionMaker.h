#ifndef RECT_COLLIDER_EXTRUSION_MAKER_H_
#define RECT_COLLIDER_EXTRUSION_MAKER_H_

#include "RectColliderExtrusion.h"

namespace tktk
{
	class RectColliderExtrusionMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RectColliderExtrusionMaker& makeStart();

	public:

		// �쐬����
		RectColliderExtrusion* create();

	private:

		// ���g�̃|�C���^
		static RectColliderExtrusionMaker m_self;
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_MAKER_H_