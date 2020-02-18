#include "TktkAppendDxlib2DComponent/Graphics/Figure/Polygon2DDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix3.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <DxLib.h>
#include "TktkDxlib2DWrapper/Utility/DXConverter.h"
#include "TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h"

namespace tktk
{
	Polygon2DDrawer::Polygon2DDrawer(
		const std::vector<Vector2>& vertexs,
		float lineThickness,
		bool isFill,
		const Color & polygonColor,
		float drawPriority,
		BlendMode blendMode,
		float blendParam
	)
		: ComponentBase(drawPriority)
		, m_vertexs(vertexs)
		, m_lineThickness(lineThickness)
		, m_isFill(isFill)
		, m_polygonColor(polygonColor)
		, m_blendMode(blendMode)
		, m_blendParam(blendParam)
	{
	}

	void Polygon2DDrawer::start()
	{
		auto transform2D = getComponent<Transform2D>();

		if (transform2D.expired())
		{
			throw std::runtime_error("SpriteDrawer not found Transform2D");
		}
		m_transform2D = transform2D;
	}

	void Polygon2DDrawer::draw() const
	{
		if (m_useRenderTarget) RenderTargetManager::setRenderTarget(m_renderTargetId);

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(m_blendMode, static_cast<int>(m_blendParam * 255));

		if (m_isFill)
			drawPolygon2D();
		else
			drawPolygon2DFlame();

		if (m_blendMode != DX_BLENDMODE_NOBLEND) DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
		if (m_useRenderTarget) RenderTargetManager::unSetRenderTarget();
	}

	void Polygon2DDrawer::drawPolygon2D() const
	{
		Matrix3 selfMat = m_transform2D.lock()->calculateWorldMatrix();

		std::vector<DxLib::VERTEX2D> dxlib2DVertexs;
		dxlib2DVertexs.resize(m_vertexs.size());
		auto dxlib2DVertexsItr = std::begin(dxlib2DVertexs);

		for (const auto& node : m_vertexs)
		{
			DxLib::VERTEX2D dxlib2DVertex;

			dxlib2DVertex.pos = DXConverter::toVECTOR(node * selfMat);
			dxlib2DVertex.rhw = 1.0f;
			dxlib2DVertex.dif = DXConverter::toCOLOR_U8(m_polygonColor);
			dxlib2DVertex.u = 0.0f;
			dxlib2DVertex.v = 0.0f;
			(*dxlib2DVertexsItr++) = dxlib2DVertex;
		}

		std::vector<unsigned short> dxlibIndices;
		dxlibIndices.resize(3U + (m_vertexs.size() - 3U) * 3U);
		auto dxlibIndicesItr = std::begin(dxlibIndices);

		for (unsigned short us = 0; us < static_cast<unsigned short>(dxlib2DVertexs.size() - 2U); us++)
		{
			(*dxlibIndicesItr++) = 0;
			(*dxlibIndicesItr++) = us + 1U;
			(*dxlibIndicesItr++) = us + 2U;
		}

		DxLib::DrawPolygonIndexed2D(
			dxlib2DVertexs.data(),
			static_cast<int>(dxlib2DVertexs.size()),
			dxlibIndices.data(),
			static_cast<int>(dxlibIndices.size() / 3U),
			DX_NONE_GRAPH,
			TRUE
		);
	}

	void Polygon2DDrawer::drawPolygon2DFlame() const
	{
		Matrix3 selfMat = m_transform2D.lock()->calculateWorldMatrix();

		for (auto itr = std::begin(m_vertexs); itr != --std::end(m_vertexs); itr++)
		{
			auto tempItr = itr;
			Vector2 firstPos = (*tempItr) * selfMat;
			Vector2 secondPos = (*++tempItr) * selfMat;

			DxLib::DrawLineAA(
				firstPos.x,
				firstPos.y,
				secondPos.x,
				secondPos.y,
				DXConverter::toUintColor(m_polygonColor),
				m_lineThickness
			);
		}

		Vector2 firstPos = (*std::begin(m_vertexs)) * selfMat;
		Vector2 secondPos = (*--std::end(m_vertexs)) * selfMat;

		DxLib::DrawLineAA(
			firstPos.x,
			firstPos.y,
			secondPos.x,
			secondPos.y,
			DXConverter::toUintColor(m_polygonColor),
			m_lineThickness
		);
	}

	const std::vector<Vector2>& Polygon2DDrawer::getVertexs() const
	{
		return m_vertexs;
	}

	void Polygon2DDrawer::setVertexs(const std::vector<Vector2>& vertexs)
	{
		m_vertexs = vertexs;
	}

	float Polygon2DDrawer::getLineThickness() const
	{
		return m_lineThickness;
	}

	void Polygon2DDrawer::setLineThickness(float lineThickness)
	{
		m_lineThickness = lineThickness;
	}

	bool Polygon2DDrawer::getIsFill() const
	{
		return m_isFill;
	}

	void Polygon2DDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & Polygon2DDrawer::getPolygonColor() const
	{
		return m_polygonColor;
	}

	void Polygon2DDrawer::setPolygonColor(const Color & polygonColor)
	{
		m_polygonColor = polygonColor;
	}

	BlendMode Polygon2DDrawer::getBlendMode() const
	{
		return m_blendMode;
	}

	void Polygon2DDrawer::setBlendMode(BlendMode blendMode)
	{
		m_blendMode = blendMode;
	}

	float Polygon2DDrawer::getBlendParam() const
	{
		return m_blendParam;
	}

	void Polygon2DDrawer::setBlendParam(float blendParam)
	{
		m_blendParam = blendParam;
	}

	void Polygon2DDrawer::useRenderTarget(int renderTargetId)
	{
		m_useRenderTarget = true;
		m_renderTargetId = renderTargetId;
	}

	void Polygon2DDrawer::unUseRenderTarget()
	{
		m_useRenderTarget = false;
		m_renderTargetId = -1;
	}
}