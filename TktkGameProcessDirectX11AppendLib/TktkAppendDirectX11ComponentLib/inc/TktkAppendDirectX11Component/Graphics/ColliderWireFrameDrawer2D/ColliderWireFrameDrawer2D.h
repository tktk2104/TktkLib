#ifndef COLLIDER_WIRE_FRAME_DRAWER_2D_H_
#define COLLIDER_WIRE_FRAME_DRAWER_2D_H_

#include <vector>
#include <TktkMath/Color.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "TktkAppendDirectX11Component/Graphics/Line2D/Line2DDrawer.h"

namespace tktk
{
	class ColliderWireFrameDrawer2D
		: public ComponentBase
	{
	public:

		ColliderWireFrameDrawer2D(
			float drawPriority,
			const Color& lineColor
		);

	public:

		void start();
		void onEnable();
		void onDisable();

	private:

		float m_drawPriority;
		Color m_lineColor;

		std::vector<CfpPtr<Line2DDrawer>> m_wireFrameDrawerArray;
	};
}
#endif // !COLLIDER_WIRE_FRAME_DRAWER_2D_H_