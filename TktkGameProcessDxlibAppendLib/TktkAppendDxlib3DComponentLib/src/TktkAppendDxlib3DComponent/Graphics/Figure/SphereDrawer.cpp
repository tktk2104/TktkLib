#include "TktkAppendDxlib3DComponent/Graphics/Figure/SphereDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <DxLib.h>

#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/SphereShadowCreator.h"

namespace tktk
{
	SphereDrawer::SphereDrawer(
		const DxLibDraw3DParam& dxLibDraw3DParam,
		float radius,
		int divNum,
		bool isFill,
		const Color & sphereColor
	)
		: ComponentBase(dxLibDraw3DParam.drawPriority)
		, m_dxLibDraw3DParam(dxLibDraw3DParam)
		, m_radius(radius)
		, m_divNum(divNum)
		, m_isFill(isFill)
		, m_sphereColor(sphereColor)
	{
	}

	void SphereDrawer::start()
	{
		if (m_dxLibDraw3DParam.createShadow)
		{
			getGameObject().lock()->addComponent(std::make_shared<SphereShadowCreator>(
				m_dxLibDraw3DParam.shadowCreatorPriority,
				std::dynamic_pointer_cast<SphereDrawer>(shared_from_this())
				));
		}

		auto transform3D = getComponent<Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("SphereDrawer not found Transform3D");
		}
		m_transform3D = transform3D;
	}

	void SphereDrawer::draw() const
	{
		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(m_dxLibDraw3DParam.renderTargetId);

		Matrix4 selfPose = m_transform3D.lock()->calculateWorldMatrix();

		Vector3 centerPos = m_dxLibDraw3DParam.localMat.calculateTranslation() * selfPose;

		float radius = m_radius * m_transform3D.lock()->getWorldScaleRate().x;

		DxLib::SetDrawBlendMode(m_dxLibDraw3DParam.blendMode, static_cast<int>(m_dxLibDraw3DParam.blendParam));
		DxLib::SetUseLighting((m_dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		DxLib::SetWriteZBuffer3D((m_dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		DxLib::DrawSphere3D(
			DXConverter::toVECTOR(centerPos),
			radius,
			m_divNum,
			DXConverter::toUintColor(m_sphereColor),
			DXConverter::toUintColor(m_sphereColor),
			(m_isFill) ? TRUE : FALSE
		);

		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}

	float SphereDrawer::getRadius() const
	{
		return m_radius;
	}

	void SphereDrawer::setRadius(float radius)
	{
		m_radius = radius;
	}

	int SphereDrawer::getDivNum() const
	{
		return m_divNum;
	}

	void SphereDrawer::setDivNum(int divNum)
	{
		m_divNum = divNum;
	}

	bool SphereDrawer::getIsFill() const
	{
		return m_isFill;
	}

	void SphereDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & SphereDrawer::getSphereColor() const
	{
		return m_sphereColor;
	}

	void SphereDrawer::setSphereColor(const Color & sphereColor)
	{
		m_sphereColor = sphereColor;
	}

	const DxLibDraw3DParam & SphereDrawer::getDxLibDraw3DParam() const
	{
		return m_dxLibDraw3DParam;
	}

	void SphereDrawer::setMeshLocalMat(const Matrix4 & localMat)
	{
		m_dxLibDraw3DParam.localMat = localMat;
	}
	void SphereDrawer::setBlendMode(BlendMode blendMode)
	{
		m_dxLibDraw3DParam.blendMode = blendMode;
	}
	void SphereDrawer::setBlendParam(float blendParam)
	{
		m_dxLibDraw3DParam.blendParam = blendParam;
	}
	void SphereDrawer::setUseLight(bool useLight)
	{
		m_dxLibDraw3DParam.useLight = useLight;
	}
	void SphereDrawer::setWriteZBuffer(bool writeZBuffer)
	{
		m_dxLibDraw3DParam.writeZBuffer = writeZBuffer;
	}
	void SphereDrawer::useRenderTarget(int renderTargetId)
	{
		m_dxLibDraw3DParam.renderTargetId = renderTargetId;
	}
	void SphereDrawer::unUseRenderTarget()
	{
		m_dxLibDraw3DParam.renderTargetId = -1;
	}
}