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
			float drawPriority,						// �`��D��x
			CfpPtr<BoxDrawer> boxDrawer		// �����̕`��R���|�[�l���g
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		CfpPtr<BoxDrawer> m_boxDrawer;
	};
}
#endif // !BOX_SHADOW_CREATOR_H_
