#include "TktkAppendDxlib3DComponent/Graphics/Billboard/RectBillboardDrawer.h"

#include <stdexcept>
#include <DxLib.h>
#include <TktkMath/MathHelper.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>

namespace tktk
{
	RectBillboardDrawer::RectBillboardDrawer(
		const DxLibDraw3DParam& dxLibDraw3DParam,
		int textureId,
		int splitTextureIndex,
		const Vector2 & rotateCenterRate,
		float billboardScaleRate
	)
		: ComponentBase(dxLibDraw3DParam.drawPriority)
		, m_dxLibDraw3DParam(dxLibDraw3DParam)
		, m_textureID(textureId)
		, m_splitTextureIndex(splitTextureIndex)
		, m_rotateCenterRate(rotateCenterRate)
		, m_billboardScaleRate(billboardScaleRate)
	{
	}

	void RectBillboardDrawer::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("RectBillboardDrawer not found Transform3D");
		}
		m_transform3D = transform3D;
	}

	void RectBillboardDrawer::draw() const
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
		DxLib::DrawBillboard3D(
			DXConverter::toVECTOR(m_transform3D.lock()->getWorldPosition() + m_dxLibDraw3DParam.localMat.calculateTranslation()),
			m_rotateCenterRate.x,
			m_rotateCenterRate.y,
			m_billboardScaleRate,
			MathHelper::toRadians(m_transform3D.lock()->calculateLocalEulerAngles().z),
			textureHandle,
			TRUE
		);

		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}

	int RectBillboardDrawer::getTextureID() const
	{
		return m_textureID;
	}

	void RectBillboardDrawer::setTextureID(int textureID)
	{
		m_textureID = textureID;
		m_splitTextureIndex = -1;
	}

	int RectBillboardDrawer::getSplitTextureIndex() const
	{
		return m_splitTextureIndex;
	}

	void RectBillboardDrawer::setSplitTextureIndex(int splitTextureIndex)
	{
		m_splitTextureIndex = splitTextureIndex;
	}

	float RectBillboardDrawer::getBillboardScaleRate() const
	{
		return m_billboardScaleRate;
	}

	void RectBillboardDrawer::setBillboardScaleRate(float billboardScaleRate)
	{
		m_billboardScaleRate = billboardScaleRate;
	}

	const Vector2 & RectBillboardDrawer::getRotateCenterRate() const
	{
		return m_rotateCenterRate;
	}

	void RectBillboardDrawer::setRotateCenterRate(const Vector2 & rotateCenterRate)
	{
		m_rotateCenterRate = rotateCenterRate;
	}

	const DxLibDraw3DParam & RectBillboardDrawer::getDxLibDraw3DParam() const
	{
		return m_dxLibDraw3DParam;
	}

	void RectBillboardDrawer::setMeshLocalMat(const Matrix4 & localMat)
	{
		m_dxLibDraw3DParam.localMat = localMat;
	}
	void RectBillboardDrawer::setBlendMode(BlendMode blendMode)
	{
		m_dxLibDraw3DParam.blendMode = blendMode;
	}
	void RectBillboardDrawer::setBlendParam(float blendParam)
	{
		m_dxLibDraw3DParam.blendParam = blendParam;
	}
	void RectBillboardDrawer::setUseLight(bool useLight)
	{
		m_dxLibDraw3DParam.useLight = useLight;
	}
	void RectBillboardDrawer::setWriteZBuffer(bool writeZBuffer)
	{
		m_dxLibDraw3DParam.writeZBuffer = writeZBuffer;
	}
	void RectBillboardDrawer::useRenderTarget(int renderTargetId)
	{
		m_dxLibDraw3DParam.renderTargetId = renderTargetId;
	}
	void RectBillboardDrawer::unUseRenderTarget()
	{
		m_dxLibDraw3DParam.renderTargetId = -1;
	}
}