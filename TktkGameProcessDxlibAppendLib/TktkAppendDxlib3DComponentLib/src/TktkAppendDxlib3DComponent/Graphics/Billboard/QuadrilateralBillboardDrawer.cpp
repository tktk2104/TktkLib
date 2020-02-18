#include "TktkAppendDxlib3DComponent/Graphics/Billboard/QuadrilateralBillboardDrawer.h"

#include <stdexcept>
#include <DxLib.h>
#include <TktkMath/MathHelper.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>

namespace tktk
{
	QuadrilateralBillboardDrawer::QuadrilateralBillboardDrawer(
		const DxLibDraw3DParam& dxLibDraw3DParam,
		int textureID,
		int splitTextureIndex,
		const Vector2 & leftTopPos,
		const Vector2 & rightTopPos,
		const Vector2 & leftBottomPos,
		const Vector2 & rightBottomPos
	)
		: ComponentBase(dxLibDraw3DParam.drawPriority)
		, m_dxLibDraw3DParam(dxLibDraw3DParam)
		, m_textureID(textureID)
		, m_splitTextureIndex(splitTextureIndex)
		, m_leftTopPos(leftTopPos)
		, m_rightTopPos(rightTopPos)
		, m_leftBottomPos(leftBottomPos)
		, m_rightBottomPos(rightBottomPos)
	{
	}

	void QuadrilateralBillboardDrawer::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("QuadrilateralBillboardDrawer not found Transform3D");
		}
		m_transform3D = transform3D;
	}

	void QuadrilateralBillboardDrawer::draw() const
	{
		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(m_dxLibDraw3DParam.renderTargetId);

		int textureHandle = -1;

		if (m_splitTextureIndex == -1)
		{
			textureHandle = Assets2DManager::getTextureAssets().lock()->getTextureHandles(m_textureID).textureHandle;
		}
		else
		{
			textureHandle = Assets2DManager::getTextureAssets().lock()->getTextureHandles(m_textureID).splitTextureHandles.at(m_splitTextureIndex);
		}

		DxLib::SetDrawBlendMode(m_dxLibDraw3DParam.blendMode, static_cast<int>(m_dxLibDraw3DParam.blendParam));
		DxLib::SetUseLighting((m_dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		DxLib::SetWriteZBuffer3D((m_dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		DrawModiBillboard3D(
			DXConverter::toVECTOR(m_transform3D.lock()->getWorldPosition() + m_dxLibDraw3DParam.localMat.calculateTranslation()),
			m_leftTopPos.x,
			m_leftTopPos.y,
			m_rightTopPos.x,
			m_rightTopPos.y,
			m_rightBottomPos.x,
			m_rightBottomPos.y,
			m_leftBottomPos.x,
			m_leftBottomPos.y,
			textureHandle,
			TRUE
		);

		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}

	int QuadrilateralBillboardDrawer::getTextureID() const
	{
		return m_textureID;
	}

	void QuadrilateralBillboardDrawer::setTextureID(int textureID)
	{
		m_textureID = textureID;
	}

	int QuadrilateralBillboardDrawer::getSplitTextureIndex() const
	{
		return m_splitTextureIndex;
	}

	void QuadrilateralBillboardDrawer::setSplitTextureIndex(int splitTextureIndex)
	{
		m_splitTextureIndex = splitTextureIndex;
	}

	Vector2 QuadrilateralBillboardDrawer::getLeftTopPos() const
	{
		return m_leftTopPos;
	}

	Vector2 QuadrilateralBillboardDrawer::getRightTopPos() const
	{
		return m_rightTopPos;
	}

	Vector2 QuadrilateralBillboardDrawer::getLeftBottomPos() const
	{
		return m_leftBottomPos;
	}

	Vector2 QuadrilateralBillboardDrawer::getRightBottomPos() const
	{
		return m_rightBottomPos;
	}

	void QuadrilateralBillboardDrawer::setLeftTopPos(const Vector2 & leftTopPos)
	{
		m_leftTopPos = leftTopPos;
	}

	void QuadrilateralBillboardDrawer::setRightTopPos(const Vector2 & rightTopPos)
	{
		m_rightTopPos = rightTopPos;
	}

	void QuadrilateralBillboardDrawer::setLeftBottomPos(const Vector2 & leftBottomPos)
	{
		m_leftBottomPos = leftBottomPos;
	}

	void QuadrilateralBillboardDrawer::setRightBottomPos(const Vector2 & rightBottomPos)
	{
		m_rightBottomPos = rightBottomPos;
	}

	const DxLibDraw3DParam & QuadrilateralBillboardDrawer::getDxLibDraw3DParam() const
	{
		return m_dxLibDraw3DParam;
	}

	void QuadrilateralBillboardDrawer::setMeshLocalMat(const Matrix4 & localMat)
	{
		m_dxLibDraw3DParam.localMat = localMat;
	}
	void QuadrilateralBillboardDrawer::setBlendMode(BlendMode blendMode)
	{
		m_dxLibDraw3DParam.blendMode = blendMode;
	}
	void QuadrilateralBillboardDrawer::setBlendParam(float blendParam)
	{
		m_dxLibDraw3DParam.blendParam = blendParam;
	}
	void QuadrilateralBillboardDrawer::setUseLight(bool useLight)
	{
		m_dxLibDraw3DParam.useLight = useLight;
	}
	void QuadrilateralBillboardDrawer::setWriteZBuffer(bool writeZBuffer)
	{
		m_dxLibDraw3DParam.writeZBuffer = writeZBuffer;
	}
	void QuadrilateralBillboardDrawer::useRenderTarget(int renderTargetId)
	{
		m_dxLibDraw3DParam.renderTargetId = renderTargetId;
	}
	void QuadrilateralBillboardDrawer::unUseRenderTarget()
	{
		m_dxLibDraw3DParam.renderTargetId = -1;
	}
}