#ifndef BOX_SHADOW_CREATOR_H_
#define BOX_SHADOW_CREATOR_H_

#include <memory>
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
			std::weak_ptr<BoxDrawer> boxDrawer		// �����̕`��R���|�[�l���g
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		std::weak_ptr<BoxDrawer> m_boxDrawer;
	};
}
#endif // !BOX_SHADOW_CREATOR_H_
