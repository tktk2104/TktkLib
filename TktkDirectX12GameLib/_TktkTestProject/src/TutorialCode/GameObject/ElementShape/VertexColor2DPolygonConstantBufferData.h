#pragma once

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

struct VertexColor2DPolygonConstantBufferData
{
	float worldMatrix[12];
	tktkMath::Vector2 screenSize;
	float pad2[2];
	tktkMath::Color blendRate;
};