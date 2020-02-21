#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/BoxShadowCreator.h"

#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Assets/Assets2DManager.h>
#include "TktkDxlib3DWrapper/Assets/Assets3DManager.h"
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <DxLib.h>

namespace tktk
{
	BoxShadowCreator::BoxShadowCreator(
		float drawPriority,
		CfpPtr<BoxDrawer> boxDrawer
	)
		: ComponentBase(drawPriority)
		, m_boxDrawer(boxDrawer)
	{
	}

	void BoxShadowCreator::draw() const
	{
		if (m_boxDrawer.isNull() || !m_boxDrawer->isActive()) return;

		auto boxSize = m_boxDrawer->getBoxSize();
		auto boxColor = m_boxDrawer->getBoxColor();
		auto isFill = m_boxDrawer->getIsFill();
		auto dxLibDraw3DParam = m_boxDrawer->getDxLibDraw3DParam();
		auto transform3D = m_boxDrawer->getComponent<Transform3D>();

		if (dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(dxLibDraw3DParam.renderTargetId);

		Matrix4 selfNotRotatePose
			= Matrix4::createScale(transform3D->getWorldScaleRate())
			* Matrix4::createTranslation(transform3D->getWorldPosition());

		Vector3 localPos = dxLibDraw3DParam.localMat.calculateTranslation();

		Vector3 pos1 = (-boxSize * 0.5f + localPos) * selfNotRotatePose;
		Vector3 pos2 = (boxSize * 0.5f + localPos) * selfNotRotatePose;

		DxLib::SetDrawBlendMode(dxLibDraw3DParam.blendMode, static_cast<int>(dxLibDraw3DParam.blendParam));
		DxLib::SetUseLighting((dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		DxLib::SetWriteZBuffer3D((dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		DxLib::DrawCube3D(
			DXConverter::toVECTOR(pos1),
			DXConverter::toVECTOR(pos2),
			DXConverter::toUintColor(boxColor),
			DXConverter::toUintColor(boxColor),
			(isFill) ? TRUE : FALSE
		);

		if (dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}
}