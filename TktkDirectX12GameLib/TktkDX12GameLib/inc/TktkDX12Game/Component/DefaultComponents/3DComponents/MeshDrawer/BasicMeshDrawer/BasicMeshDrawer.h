#ifndef BASIC_MESH_DRAWER_H_
#define BASIC_MESH_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../../ComponentBase.h"
#include "../../Transform3D/Transform3D.h"

namespace tktk
{
	class BasicMeshDrawer
		: public ComponentBase
	{
	public:

		BasicMeshDrawer(
			float drawPriority,
			int meshId
		);

	public:

		void start();
		void draw() const;

	private:

		int							m_meshId{ -1 };
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BASIC_MESH_DRAWER_H_