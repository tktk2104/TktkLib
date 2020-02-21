#include "TktkAppendDxlib3DComponent/Graphics/MeshDrawer/MeshDrawerMaker.h"

namespace tktk
{
	MeshDrawerMaker MeshDrawerMaker::m_self;

	MeshDrawerMaker & MeshDrawerMaker::makeStart()
	{
		m_self = MeshDrawerMaker();
		return m_self;
	}

	MeshDrawer* MeshDrawerMaker::create()
	{
		DxLibDraw3DParam dxLibDraw3DParam = DxLibDraw3DParam(m_drawPriority);
		dxLibDraw3DParam.localMat = Matrix4::createTRS(m_meshLocalPos, m_meshLocalRotation, m_meshLocalScale);
		dxLibDraw3DParam.blendMode = m_blendMode;
		dxLibDraw3DParam.blendParam = m_blendParam;
		dxLibDraw3DParam.useLight = m_useLight;
		dxLibDraw3DParam.writeZBuffer = m_writeZBuffer;
		dxLibDraw3DParam.renderTargetId = m_renderTargetId;
		dxLibDraw3DParam.createShadow = m_createShadow;
		dxLibDraw3DParam.shadowCreatorPriority = m_shadowCreatorPriority;

		return new MeshDrawer(
			dxLibDraw3DParam,
			m_meshID
			);
	}

	MeshDrawerMaker & MeshDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::meshID(int value)
	{
		m_meshID = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::meshLocalPos(const Vector3 & value)
	{
		m_meshLocalPos = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::meshLocalRotation(const Quaternion & value)
	{
		m_meshLocalRotation = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::meshLocalScale(const Vector3 & value)
	{
		m_meshLocalScale = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::blendMode(BlendMode value)
	{
		m_blendMode = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::blendParam(float value)
	{
		m_blendParam = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::useLight(bool value)
	{
		m_useLight = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::writeZBuffer(bool value)
	{
		m_writeZBuffer = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::renderTargetId(int value)
	{
		m_renderTargetId = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::createShadow(bool value)
	{
		m_createShadow = value;
		return *this;
	}

	MeshDrawerMaker & MeshDrawerMaker::shadowCreatorPriority(float value)
	{
		m_shadowCreatorPriority = value;
		return *this;
	}
}