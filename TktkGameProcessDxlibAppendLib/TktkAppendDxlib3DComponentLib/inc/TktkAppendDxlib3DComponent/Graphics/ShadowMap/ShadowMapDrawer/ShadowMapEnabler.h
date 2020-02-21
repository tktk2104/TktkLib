#ifndef SHADOW_MAP_ENABLER_H_
#define SHADOW_MAP_ENABLER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "ShadowMapDrawer.h"

namespace tktk
{
	class ShadowMapEnabler
		: public ComponentBase
	{
	public:

		ShadowMapEnabler(
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
#endif // !SHADOW_MAP_ENABLER_H_