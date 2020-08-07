#include "ElementSphere.h"

#include <TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h>
#include <TktkDX12BaseComponents/3D/MeshDrawer/SphereMeshDrawerMaker.h>

#include "Script/ElementColorChanger.h"

tktk::GameObjectPtr ElementSphere::create(const tktkMath::Vector3 & position, const tktkMath::Color & color, unsigned int id)
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform3DMaker::makeStart(gameObject)
		.initPosition(position)
		.initScaleRate({ 0.1f })
		.create();

	tktk::SphereMeshDrawerMaker::makeStart(gameObject)
		.drawPriority(0.0f)
		.cameraId(0)
		.shadowMapCameraId(1)
		.lightId(0)
		.create();

	gameObject->createComponent<ElementColorChanger>(color, id);

	return gameObject;
}
