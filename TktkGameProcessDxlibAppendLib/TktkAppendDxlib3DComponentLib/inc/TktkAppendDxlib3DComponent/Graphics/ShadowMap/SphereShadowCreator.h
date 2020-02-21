#ifndef SPHERE_SHADOW_CREATOR_H_
#define SPHERE_SHADOW_CREATOR_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../Figure/SphereDrawer.h"

namespace tktk
{
	class SphereShadowCreator
		: public ComponentBase
	{
	public:

		SphereShadowCreator(
			float drawPriority,							// �`��D��x
			CfpPtr<SphereDrawer> sphereDrawer	// ���̕`��R���|�[�l���g
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		CfpPtr<SphereDrawer> m_sphereDrawer;
	};
}
#endif // !SPHERE_SHADOW_CREATOR_H_