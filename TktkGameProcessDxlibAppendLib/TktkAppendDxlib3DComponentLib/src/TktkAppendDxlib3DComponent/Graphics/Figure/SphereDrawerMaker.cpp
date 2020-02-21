#include "TktkAppendDxlib3DComponent/Graphics/Figure/SphereDrawerMaker.h"

namespace tktk
{
	SphereDrawerMaker SphereDrawerMaker::m_self;

	SphereDrawerMaker & SphereDrawerMaker::makeStart()
	{
		m_self = SphereDrawerMaker();
		return m_self;
	}

	SphereDrawer* SphereDrawerMaker::create()
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

		return new SphereDrawer(
			dxLibDraw3DParam,
			m_radius,
			m_divNum,
			m_isFill,
			m_sphereColor
			);
	}

	SphereDrawerMaker & SphereDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::radius(float value)
	{
		m_radius = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::divNum(int value)
	{
		m_divNum = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::localPosition(const Vector3 & value)
	{
		m_localPosition = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::isFill(bool value)
	{
		m_isFill = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::sphereColor(const Color & value)
	{
		m_sphereColor = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::blendMode(const BlendMode & value)
	{
		m_blendMode = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::useLight(bool value)
	{
		m_useLight = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::writeZBuffer(bool value)
	{
		m_writeZBuffer = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::renderTargetId(int value)
	{
		m_renderTargetId = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::createShadow(bool value)
	{
		m_createShadow = value;
		return *this;
	}

	SphereDrawerMaker & SphereDrawerMaker::shadowCreatorPriority(float value)
	{
		m_shadowCreatorPriority = value;
		return *this;
	}
}