#include "ElementSphereManager.h"

#include <TktkDX12Game/GameObject/GameObject.h>
#include "Script/ElementSphereManagerScript.h"

tktk::GameObjectPtr ElementSphereManager::create()
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	gameObject->addGameObjectTag(1);

	gameObject->createComponent<ElementSphereManagerScript>();

	return gameObject;
}
