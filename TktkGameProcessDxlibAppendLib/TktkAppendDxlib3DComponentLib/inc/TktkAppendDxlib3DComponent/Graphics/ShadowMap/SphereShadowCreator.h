#ifndef SPHERE_SHADOW_CREATOR_H_
#define SPHERE_SHADOW_CREATOR_H_

#include <memory>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../Figure/SphereDrawer.h"

namespace tktk
{
	class SphereShadowCreator
		: public ComponentBase
	{
	public:

		SphereShadowCreator(
			float drawPriority,							// 描画優先度
			std::weak_ptr<SphereDrawer> sphereDrawer	// 球体描画コンポーネント
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		std::weak_ptr<SphereDrawer> m_sphereDrawer;
	};
}
#endif // !SPHERE_SHADOW_CREATOR_H_