#ifndef BASIC_MESH_DRAWER_H_
#define BASIC_MESH_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"
#include "../MeshAnimator/MeshAnimator.h"

namespace tktk
{
	// �ʏ탁�b�V���`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�z
	class BasicMeshDrawer
		: public ComponentBase
	{
	public:

		BasicMeshDrawer(float drawPriority, unsigned int meshId, unsigned int skeletonId, unsigned int cameraId, unsigned int useRtvDescriptorHeapId);

	public:

		void start();
		void draw() const;

	private:

		unsigned int				m_useRtvDescriptorHeapId;
		unsigned int				m_meshId;
		unsigned int				m_skeletonId;
		unsigned int				m_cameraId;
		ComponentPtr<Transform3D>	m_transform{ };
		ComponentPtr<MeshAnimator>	m_animator{ };
	};
}
#endif // !BASIC_MESH_DRAWER_H_