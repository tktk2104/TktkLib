#ifndef SHADOW_MAP_DISABLER_H_
#define SHADOW_MAP_DISABLER_H_

#include <memory>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "ShadowMapDrawer.h"

namespace tktk
{
	class ShadowMapDisabler
		: public ComponentBase
	{
	public:

		ShadowMapDisabler(
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
#endif // !SHADOW_MAP_DISABLER_H_
