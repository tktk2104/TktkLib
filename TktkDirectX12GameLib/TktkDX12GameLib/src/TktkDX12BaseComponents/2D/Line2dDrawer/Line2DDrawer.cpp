#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawer.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include <stdexcept>
#include <array>

namespace tktk
{
	Line2DDrawer::Line2DDrawer(
		float drawPriority,
		unsigned int useLine2DMaterialId,
		const std::vector<tktkMath::Vector2>& lineVertexArray,
		const tktkMath::Color& lineColor,
		const tktkMath::Color& blendRate,
		unsigned int useRtvDescriptorHeapId
	)
		: ComponentBase(drawPriority)
		, m_useLine2DMaterialId(useLine2DMaterialId)
		, m_useRtvDescriptorHeapId(useRtvDescriptorHeapId)
		, m_lineVertexArray(lineVertexArray)
		, m_lineColor(lineColor)
		, m_blendRate(blendRate)
	{
	}

	void Line2DDrawer::start()
	{
		m_transform = getComponent<Transform2D>();

		if (m_transform.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
	}

	void Line2DDrawer::draw() const
	{
		Line2DMaterialDrawFuncArgs drawFuncArgs;
		drawFuncArgs.viewportId				= DX12GameManager::getSystemId(SystemViewportType::Basic);
		drawFuncArgs.scissorRectId			= DX12GameManager::getSystemId(SystemScissorRectType::Basic);
		drawFuncArgs.rtvDescriptorHeapId = m_useRtvDescriptorHeapId;
		drawFuncArgs.worldMatrix			= m_transform->calculateWorldMatrix();
		drawFuncArgs.lineColor				= m_lineColor;
		drawFuncArgs.lineVertexArray		= m_lineVertexArray;

		DX12GameManager::drawLine(m_useLine2DMaterialId, drawFuncArgs);
	}

	const std::vector<tktkMath::Vector2>& Line2DDrawer::getLineVertexArray() const
	{
		return m_lineVertexArray;
	}

	void Line2DDrawer::setLineVertexArray(const std::vector<tktkMath::Vector2>& vertexArray)
	{
		m_lineVertexArray = vertexArray;
	}

	const tktkMath::Color & Line2DDrawer::getLineColor() const
	{
		return m_lineColor;
	}

	void Line2DDrawer::setLineColor(const tktkMath::Color & color)
	{
		m_lineColor = color;
	}

	void Line2DDrawer::setBlendRate(const tktkMath::Color & blendRate)
	{
		m_blendRate = blendRate;
	}
}