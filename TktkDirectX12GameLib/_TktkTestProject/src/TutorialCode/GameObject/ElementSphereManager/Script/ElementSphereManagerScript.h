#pragma once

#include <array>
#include <forward_list>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include <TktkDX12Game/Component/ComponentBase.h>
#include "../../ElementShape/VertexColor2DPolygonVertexData.h"

constexpr int countId(MaterialId first, MaterialId last)
{
	return static_cast<int>(last) - static_cast<int>(first) + 1;
}

class ElementSphereManagerScript
	: public tktk::ComponentBase
{
public:

	ElementSphereManagerScript() = default;

public:

	void start();

	void update();

public:

	void createElementSphere(const tktkMath::Vector3& position, const tktkMath::Color& color);

private:

	void addElementShapeVertexArray(
		std::vector<tktkMath::Vector2>* elementShapeGuideVertexArrayPtr,
		std::vector<VertexColor2DPolygonVertexData>* elementShapeVertexArrayPtr,
		std::forward_list<unsigned int>* notMaxOrMinIndexListPtr,
		const tktkMath::Vector2& previousPos,
		const tktkMath::Vector2& nextPos,
		const std::vector<VertexColor2DPolygonVertexData>& elementSpherePointArray
	);

private:

	static constexpr unsigned int m_firstElementMaterialId{ static_cast<unsigned int>(MaterialId::Sphere_1) };

	static constexpr unsigned int m_lastElementMaterialId{ static_cast<unsigned int>(MaterialId::Sphere_10) };

	static constexpr unsigned int m_useMatArraySize{ m_lastElementMaterialId - m_firstElementMaterialId + 1U };

private:

	std::array<bool, m_useMatArraySize> m_useMatArray;

	std::forward_list<tktk::GameObjectPtr> m_elementSphereObjectList;

	tktk::GameObjectPtr m_elementShapeGuide;
};