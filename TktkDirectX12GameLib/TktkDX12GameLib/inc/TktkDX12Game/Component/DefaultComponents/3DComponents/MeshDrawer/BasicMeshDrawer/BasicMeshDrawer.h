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

		BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int useRtvDescriptorHeapId);

	public:

		void start();
		void draw() const;

	private:

		unsigned int				m_useRtvDescriptorHeapId;
		unsigned int				m_meshId;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !BASIC_MESH_DRAWER_H_