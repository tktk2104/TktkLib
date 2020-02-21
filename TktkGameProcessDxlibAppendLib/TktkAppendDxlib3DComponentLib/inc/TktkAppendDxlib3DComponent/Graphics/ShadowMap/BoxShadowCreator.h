#ifndef BOX_SHADOW_CREATOR_H_
#define BOX_SHADOW_CREATOR_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../Figure/BoxDrawer.h"

namespace tktk
{
	class BoxShadowCreator
		: public ComponentBase
	{
	public:

		BoxShadowCreator(
			float drawPriority,						// 描画優先度
			CfpPtr<BoxDrawer> boxDrawer		// 立方体描画コンポーネント
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		CfpPtr<BoxDrawer> m_boxDrawer;
	};
}
#endif // !BOX_SHADOW_CREATOR_H_
