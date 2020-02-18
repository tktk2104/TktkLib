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
			float drawPriority,						// 描画優先度
			std::weak_ptr<MeshDrawer> meshDrawer	// メッシュ描画コンポーネント
		);

	public:

		// <PolymorphismFunc>
		void draw() const;

	private:

		std::weak_ptr<MeshDrawer> m_meshDrawer;
	};
}

#endif // !MESH_SHADOW_CREATOR_H_
