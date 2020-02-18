#ifndef RECT_COLLIDER_EXTRUSION_H_
#define RECT_COLLIDER_EXTRUSION_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "RectCollider.h"

namespace tktk
{
	class RectColliderExtrusion
		: public ComponentBase
	{
	public:

		RectColliderExtrusion() = default;

	public:

		// <PolymorphismFunc>
		void onCollisionStay(CfpPtr<GameObject> other);

	private:

		// TODO : Utilty‚ÉˆÚ“®‚·‚é
		bool lineCrossCheck(
			const Vector2& firstLinePosOne,
			const Vector2& firstLinePosTwo,
			const Vector2& secondLinePosOne,
			const Vector2& secondLinePosTwo,
			float* dR,
			float* dS,
			Vector2* crossPos
		);
	};
}
#endif // !RECT_COLLIDER_EXTRUSION_H_