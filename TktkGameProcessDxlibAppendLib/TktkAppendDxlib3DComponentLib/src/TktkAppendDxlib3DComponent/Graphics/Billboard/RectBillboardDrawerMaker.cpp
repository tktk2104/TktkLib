#include "TktkAppendDxlib3DComponent/Graphics/Billboard/RectBillboardDrawerMaker.h"

namespace tktk
{
	RectBillboardDrawerMaker RectBillboardDrawerMaker::m_self;

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::makeStart()
	{
		m_self = RectBillboardDrawerMaker();
		return m_self;
	}

	RectBillboardDrawer* RectBillboardDrawerMaker::create()
	{
		DxLibDraw3DParam dxLibDraw3DParam = DxLibDraw3DParam(m_drawPriority);
		dxLibDraw3DParam.localMat = Matrix4::createTranslation(m_localPos);
		dxLibDraw3DParam.blendMode = m_blendMode;
		dxLibDraw3DParam.blendParam = m_blendParam;
		dxLibDraw3DParam.useLight = m_useLight;
		dxLibDraw3DParam.writeZBuffer = m_writeZBuffer;
		dxLibDraw3DParam.renderTargetId = m_renderTargetId;

		return new RectBillboardDrawer(
			dxLibDraw3DParam,
			m_textureId,
			m_splitTextureIndex,
			m_rotateCenterRate,
			m_billboardScaleRate
			);
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::textureId(int value)
	{
		m_textureId = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::splitTextureIndex(int value)
	{
		m_splitTextureIndex = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::localPos(const Vector3 & value)
	{
		m_localPos = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::rotateCenterRate(const Vector2 & value)
	{
		m_rotateCenterRate = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::billboardScaleRate(float value)
	{
		m_billboardScaleRate = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::blendMode(const BlendMode & value)
	{
		m_blendMode = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::useLight(bool value)
	{
		m_useLight = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::writeZBuffer(bool value)
	{
		m_writeZBuffer = value;
		return *this;
	}

	RectBillboardDrawerMaker & RectBillboardDrawerMaker::renderTargetId(int value)
	{
		m_renderTargetId = value;
		return *this;
	}
}