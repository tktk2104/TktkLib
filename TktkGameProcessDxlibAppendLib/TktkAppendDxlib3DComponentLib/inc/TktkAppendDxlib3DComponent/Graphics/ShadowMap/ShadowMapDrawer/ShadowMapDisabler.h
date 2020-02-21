#ifndef SHADOW_MAP_DISABLER_H_
#define SHADOW_MAP_DISABLER_H_

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
			CfpPtr<ShadowMapDrawer> shadowMapDrawer
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		CfpPtr<ShadowMapDrawer> m_shadowMapDrawer;
	};
}
#endif // !SHADOW_MAP_DISABLER_H_
