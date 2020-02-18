#ifndef SHADOW_MAP_CREATE_STARTER_H_
#define SHADOW_MAP_CREATE_STARTER_H_

#include <memory>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "ShadowMapDrawer.h"

namespace tktk
{
	class ShadowMapCreateStarter
		: public ComponentBase
	{
	public:

		ShadowMapCreateStarter(
			float drawPriority,
			std::weak_ptr<ShadowMapDrawer> shadowMapDrawer
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		std::weak_ptr<ShadowMapDrawer> m_shadowMapDrawer;
	};
}
#endif // !SHADOW_MAP_CREATE_STARTER_H_