#include "ElementShape.h"

#include <TktkDX12BaseComponents/2D/Transform2D/Transform2DMaker.h>

#include "Script/ElementShapeScript.h"
#include "Script/VertexColor2DPolygonDrawer.h"

tktk::GameObjectPtr ElementShape::create(const std::vector<VertexColor2DPolygonVertexData>& lineVertexArray)
{
	tktk::GameObjectPtr gameObject = tktk::DX12GameManager::createGameObject();

	tktk::Transform2DMaker::makeStart(gameObject)
		.create();

	/*gameObject->createComponent<VertexColor2DPolygonDrawer>(
		100.0f,
		static_cast<int>(tktk::SystemBlendStateId::Alpha),
		static_cast<int>(tktk::SystemDepthStencilStateId::NotUseDepth),
		static_cast<int>(tktk::SystemRasterizerStateId::Basic),
		lineVertexArray,
		tktkMath::Color(1.0f, 1.0f, 1.0f, 0.8f)
		);*/

	gameObject->createComponent<ElementShapeScript>(lineVertexArray);

	return gameObject;
}
