#include "TktkAppendDxlib3DComponent/Graphics/Figure/BoxDrawer.h"

#include <stdexcept>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib2DWrapper/Graphics/RenderTarget/RenderTargetManager.h>
#include <DxLib.h>

#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/BoxShadowCreator.h"

namespace tktk
{
	BoxDrawer::BoxDrawer(
		const DxLibDraw3DParam& dxLibDraw3DParam,
		const Vector3 & boxSize,
		bool isFill,
		const Color & boxColor
	)
		: ComponentBase(dxLibDraw3DParam.drawPriority)
		, m_dxLibDraw3DParam(dxLibDraw3DParam)
		, m_boxSize(boxSize)
		, m_isFill(isFill)
		, m_boxColor(boxColor)
	{
	}

	void BoxDrawer::start()
	{
		if (m_dxLibDraw3DParam.createShadow)
		{
			getGameObject().lock()->addComponent(std::make_shared<BoxShadowCreator>(
				m_dxLibDraw3DParam.shadowCreatorPriority,
				std::dynamic_pointer_cast<BoxDrawer>(shared_from_this())
				));
		}

		auto transform3D = getComponent<Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("BoxDrawer not found Transform3D");
		}
		m_transform3D = transform3D;
	}

	void BoxDrawer::draw() const
	{
		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::setRenderTarget(m_dxLibDraw3DParam.renderTargetId);

		Matrix4 selfNotRotatePose
			= Matrix4::createScale(m_transform3D.lock()->getWorldScaleRate())
			* Matrix4::createTranslation(m_transform3D.lock()->getWorldPosition());

		Vector3 localPos = m_dxLibDraw3DParam.localMat.calculateTranslation();

		Vector3 pos1 = (-m_boxSize * 0.5f + localPos) * selfNotRotatePose;
		Vector3 pos2 = ( m_boxSize * 0.5f + localPos) * selfNotRotatePose;

		DxLib::SetDrawBlendMode(m_dxLibDraw3DParam.blendMode, static_cast<int>(m_dxLibDraw3DParam.blendParam));
		DxLib::SetUseLighting((m_dxLibDraw3DParam.useLight) ? TRUE : FALSE);
		DxLib::SetWriteZBuffer3D((m_dxLibDraw3DParam.writeZBuffer) ? TRUE : FALSE);
		DxLib::DrawCube3D(
			DXConverter::toVECTOR(pos1),
			DXConverter::toVECTOR(pos2),
			DXConverter::toUintColor(m_boxColor),
			DXConverter::toUintColor(m_boxColor),
			(m_isFill) ? TRUE : FALSE
		);

		if (m_dxLibDraw3DParam.renderTargetId != -1) RenderTargetManager::unSetRenderTarget();
	}

	const Vector3 & BoxDrawer::getBoxSize() const
	{
		return m_boxSize;
	}
	void BoxDrawer::setBoxSize(const Vector3 & boxSize)
	{
		m_boxSize = boxSize;
	}

	bool BoxDrawer::getIsFill() const
	{
		return m_isFill;
	}
	void BoxDrawer::setIsFill(bool isFill)
	{
		m_isFill = isFill;
	}

	const Color & BoxDrawer::getBoxColor() const
	{
		return m_boxColor;
	}
	void BoxDrawer::setBoxColor(const Color & boxColor)
	{
		m_boxColor = boxColor;
	}

	const DxLibDraw3DParam & BoxDrawer::getDxLibDraw3DParam() const
	{
		return m_dxLibDraw3DParam;
	}

	void BoxDrawer::setMeshLocalMat(const Matrix4 & localMat)
	{
		m_dxLibDraw3DParam.localMat = localMat;
	}
	void BoxDrawer::setBlendMode(BlendMode blendMode)
	{
		m_dxLibDraw3DParam.blendMode = blendMode;
	}
	void BoxDrawer::setBlendParam(float blendParam)
	{
		m_dxLibDraw3DParam.blendParam = blendParam;
	}
	void BoxDrawer::setUseLight(bool useLight)
	{
		m_dxLibDraw3DParam.useLight = useLight;
	}
	void BoxDrawer::setWriteZBuffer(bool writeZBuffer)
	{
		m_dxLibDraw3DParam.writeZBuffer = writeZBuffer;
	}
	void BoxDrawer::useRenderTarget(int renderTargetId)
	{
		m_dxLibDraw3DParam.renderTargetId = renderTargetId;
	}
	void BoxDrawer::unUseRenderTarget()
	{
		m_dxLibDraw3DParam.renderTargetId = -1;
	}
}