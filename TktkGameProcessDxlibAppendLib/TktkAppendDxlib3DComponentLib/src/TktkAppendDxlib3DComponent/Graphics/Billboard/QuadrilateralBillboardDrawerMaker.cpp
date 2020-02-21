#include "TktkAppendDxlib3DComponent/Graphics/Billboard/QuadrilateralBillboardDrawerMaker.h"

namespace tktk
{
	QuadrilateralBillboardDrawerMaker QuadrilateralBillboardDrawerMaker::m_self;

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::makeStart()
	{
		m_self = QuadrilateralBillboardDrawerMaker();
		return m_self;
	}

	QuadrilateralBillboardDrawer* QuadrilateralBillboardDrawerMaker::create()
	{
		DxLibDraw3DParam dxLibDraw3DParam = DxLibDraw3DParam(m_drawPriority);
		dxLibDraw3DParam.localMat = Matrix4::createTranslation(m_localPos);
		dxLibDraw3DParam.blendMode = m_blendMode;
		dxLibDraw3DParam.blendParam = m_blendParam;
		dxLibDraw3DParam.useLight = m_useLight;
		dxLibDraw3DParam.writeZBuffer = m_writeZBuffer;
		dxLibDraw3DParam.renderTargetId = m_renderTargetId;

		return new QuadrilateralBillboardDrawer(
			dxLibDraw3DParam,
			m_textureId,
			m_splitTextureIndex,
			m_leftTopPos,
			m_rightTopPos,
			m_leftBottomPos,
			m_rightBottomPos
			);
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::textureId(int value)
	{
		m_textureId = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::splitTextureIndex(int value)
	{
		m_splitTextureIndex = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::localPos(const Vector3 & value)
	{
		m_localPos = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::leftTopPos(const Vector2 & value)
	{
		m_leftTopPos = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::rightTopPos(const Vector2 & value)
	{
		m_rightTopPos = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::leftBottomPos(const Vector2 & value)
	{
		m_leftBottomPos = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::rightBottomPos(const Vector2 & value)
	{
		m_rightBottomPos = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::blendMode(const BlendMode & value)
	{
		m_blendMode = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::useLight(bool value)
	{
		m_useLight = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::writeZBuffer(bool value)
	{
		m_writeZBuffer = value;
		return *this;
	}

	QuadrilateralBillboardDrawerMaker & QuadrilateralBillboardDrawerMaker::renderTargetId(int value)
	{
		m_renderTargetId = value;
		return *this;
	}
}