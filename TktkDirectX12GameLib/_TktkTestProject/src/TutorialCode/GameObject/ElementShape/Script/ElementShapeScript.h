#pragma once

#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../VertexColor2DPolygonVertexData.h"

class ElementShapeScript
	: public tktk::ComponentBase
{
public:

	ElementShapeScript(
		const std::vector<VertexColor2DPolygonVertexData>& lineVertexArray
	);

public:

	void start();
	void update();

private:

	std::vector<VertexColor2DPolygonVertexData> m_lineVertexArray;
};