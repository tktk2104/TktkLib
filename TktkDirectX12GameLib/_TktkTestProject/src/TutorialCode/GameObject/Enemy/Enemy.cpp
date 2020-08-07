#include "Enemy.h"

#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h>

#include "../../../Enum/_ResourceIds/ResourceIds.h"

tktk::GameObjectPtr Enemy::create(const tktkMath::Vector3 & position)
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.create();

	tktk::SphereMeshDrawerMaker::makeStart(gameObject)
		.drawPriority(0.0f)
		.cameraId(CameraId::Basic)
		.shadowMapCameraId(CameraId::ShadowMap)
		.lightId(LightId::Basic)
		.create();

	return gameObject;
}
