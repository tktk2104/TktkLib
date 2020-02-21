#ifndef MESH_SHADOW_CREATOR_H_
#define MESH_SHADOW_CREATOR_H_

#include <memory>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../MeshDrawer/MeshDrawer.h"

namespace tktk
{
	class MeshShadowCreator
		: public ComponentBase
	{
	public:

		MeshShadowCreator(
			float drawPriority,						// �`��D��x
			CfpPtr<MeshDrawer> meshDrawer	// ���b�V���`��R���|�[�l���g
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		CfpPtr<MeshDrawer> m_meshDrawer;
	};
}

#endif // !MESH_SHADOW_CREATOR_H_
