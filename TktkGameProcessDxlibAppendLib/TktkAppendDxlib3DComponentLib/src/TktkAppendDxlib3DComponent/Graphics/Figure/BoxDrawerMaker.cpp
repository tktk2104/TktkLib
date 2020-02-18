#include "TktkAppendDxlib3DComponent/Graphics/Figure/BoxDrawerMaker.h"

namespace tktk
{
	BoxDrawerMaker BoxDrawerMaker::m_self;

	BoxDrawerMaker & BoxDrawerMaker::makeStart()
	{
		m_self = BoxDrawerMaker();
		return m_self;
	}

	std::shared_ptr<BoxDrawer> BoxDrawerMaker::create()
	{
		DxLibDraw3DParam dxLibDraw3DParam = DxLibDraw3DParam(m_drawPriority);
		dxLibDraw3DParam.localMat = Matrix4::createTranslation(m_localPosition);
		dxLibDraw3DParam.blendMode = m_blendMode;
		dxLibDraw3DParam.blendParam = m_blendParam;
		dxLibDraw3DParam.useLight = m_useLight;
		dxLibDraw3DParam.writeZBuffer = m_writeZBuffer;
		dxLibDraw3DParam.renderTargetId = m_renderTargetId;
		dxLibDraw3DParam.createShadow = m_createShadow;
		dxLibDraw3DParam.shadowCreatorPriority = m_shadowCreatorPriority;

		return std::make_shared<BoxDrawer>(
			dxLibDraw3DParam,
			m_boxSize,
			m_isFill,
			m_boxColor
			);
	}

	BoxDrawerMaker & BoxDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::boxSize(const Vector3 & value)
	{
		m_boxSize = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::localPosition(const Vector3 & value)
	{
		m_localPosition = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::boxColor(const Color & value)
	{
		m_boxColor = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::blendMode(const BlendMode & value)
	{
		m_blendMode = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::useLight(bool value)
	{
		m_useLight = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::writeZBuffer(bool value)
	{
		m_writeZBuffer = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::renderTargetId(int value)
	{
		m_renderTargetId = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::createShadow(bool value)
	{
		m_createShadow = value;
		return *this;
	}

	BoxDrawerMaker & BoxDrawerMaker::shadowCreatorPriority(float value)
	{
		m_shadowCreatorPriority = value;
		return *this;
	}
}