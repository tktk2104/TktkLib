#ifndef MESH_ANIMATOR_H_
#define MESH_ANIMATOR_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshAnimator
		: public ComponentBase
	{
	public:

		MeshAnimator(
			CfpPtr<MeshDrawer> meshDrawer,
			int animationId,
			float animFrameIntervalPerSec,
			float animSpeedRate
		);
		~MeshAnimator();

	public:

		void start();
		void update();

	private:

		CfpPtr<MeshDrawer> m_meshDrawer;

		int m_animationId{ 0 };

		float m_animSecTimer{ 0.0f };

		float m_animFrameIntervalPerSec{ 60.0f };

		float m_animSpeedRate{ 1.0f };
	};
}
#endif // !MESH_ANIMATOR_H_