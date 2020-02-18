#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/SphereShadowCreator.h"

#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <DxLib.h>

namespace tktk
{
	SphereShadowCreator::SphereShadowCreator(
		float drawPriority,
		std::weak_ptr<SphereDrawer> sphereDrawer
	)
		: ComponentBase(drawPriority)
		, m_sphereDrawer(sphereDrawer)
	{
	}

	void SphereShadowCreator::draw() const
	{
		if (m_sphereDrawer.expired() || !m_sphereDrawer.lock()->isActive()) return;

		auto baseRadius = m_sphereDrawer.lock()->getRadius();
		auto divNum = m_sphereDrawer.lock()->getDivNum();
		auto sphereColor = m_sphereDrawer.lock()->getSphereColor();
		auto isFill = m_sphereDrawer.lock()->getIsFill();
		auto dxLibDraw3DParam = m_sphereDrawer.lock()->getDxLibDraw3DParam();
		auto transform3D = m_sphereDrawer.lock()->getComponent<Transform3D>();

		if (dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(dxLibDraw3DParam.renderTargetId);

		Matrix4 selfPose = transform3D.lock()->calculateWorldMatrix();

		Vector3 centerPos = dxLibDraw3DParam.localMat.calculateTranslation() * selfPose;

		float radius = baseRadius * transform3D.lock()->getWorldScaleRate().x;

		DxLib::SetDrawBlendMode(dxLibDraw3DParam.blendMode, static_cast<int>(dxLibDraw3DParam.blendParam));
		DxLib::SetUseLighting((dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		DxLib::SetWriteZBuffer3D((dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		DxLib::DrawSphere3D(
			DXConverter::toVECTOR(centerPos),
			radius,
			divNum,
			DXConverter::toUintColor(sphereColor),
			DXConverter::toUintColor(sphereColor),
			(isFill) ? TRUE : FALSE
		);

		if (dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}
}