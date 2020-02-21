#ifndef SHADOW_MAP_CREATE_FINISHER_H_
#define SHADOW_MAP_CREATE_FINISHER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "ShadowMapDrawer.h"

namespace tktk
{
	class ShadowMapCreateFinisher
		: public ComponentBase
	{
	public:

		ShadowMapCreateFinisher(
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
#endif // !SHADOW_MAP_CREATE_FINISHER_H_