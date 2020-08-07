#include "ElementShapeGuide.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h>
#include <TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawerMaker.h>

tktk::GameObjectPtr ElementShapeGuide::create()
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform2DMaker::makeStart(gameObject)
		.create();

	tktk::Line2DDrawerMaker::makeStart(gameObject)
		.drawPriority(100.0f)
		.lineColor(tktkMath::colorWhite)
		.create();

	return gameObject;
}
