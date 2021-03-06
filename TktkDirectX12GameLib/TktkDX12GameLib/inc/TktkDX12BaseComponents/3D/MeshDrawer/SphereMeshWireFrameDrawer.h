#ifndef SPHERE_MESH_WIRE_FRAME_DRAWER_H_
#define SPHERE_MESH_WIRE_FRAME_DRAWER_H_

#include <TktkMath/Structs/Color.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// 球体メッシュワイヤーフレーム描画コンポーネント
	class SphereMeshWireFrameDrawer
		: public ComponentBase
	{
	public:

		SphereMeshWireFrameDrawer(float drawPriority, float radius, const tktkMath::Color& albedoColor, unsigned int cameraId, unsigned int shadowMapCameraId, unsigned int lightId, unsigned int useRtvDescriptorHeapId);

	public:

		void start();
		void draw() const;

	public:

		const tktkMath::Color& getAlbedoColor() const;

	private:

		float						m_radius;
		tktkMath::Color				m_albedoColor;
		unsigned int				m_useRtvDescriptorHeapId;
		unsigned int				m_cameraId;
		unsigned int				m_shadowMapCameraId;
		unsigned int				m_lightId;
		ComponentPtr<Transform3D>	m_transform{ };
	};
}
#endif // !SPHERE_MESH_WIRE_FRAME_DRAWER_H_