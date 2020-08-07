#ifndef SPHERE_MESH_DRAWER_H_
#define SPHERE_MESH_DRAWER_H_

#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 球体メッシュ描画コンポーネント
	class SphereMeshDrawer
		: public ComponentBase
	{
	public:

		SphereMeshDrawer(float drawPriority, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapId);
	
	public:

		void start();
		void draw() const;

	private:

		unsigned int				m_useRtvDescriptorHeapId;
		unsigned int				m_cameraId;
		unsigned int				m_shadowMapCameraId;
		unsigned int				m_lightId;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !SPHERE_MESH_DRAWER_H_