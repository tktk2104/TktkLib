#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapDrawer.h"

#include <TktkDxlib2DWrapper/Utility/DXConverter.h>
#include <TktkDxlib3DWrapper/Assets/Assets3DManager.h>
#include <DxLib.h>
#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapCreateStarter.h"
#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapCreateFinisher.h"
#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapEnabler.h"
#include "TktkAppendDxlib3DComponent/Graphics/ShadowMap/ShadowMapDrawer/ShadowMapDisabler.h"

namespace tktk
{
	ShadowMapDrawer::ShadowMapDrawer(
		float shadowMapCreateStarterDrawPriority,
		float shadowMapCreateFinisherDrawPriority,
		float shadowMapEnablerDrawPriority,
		float shadowMapDisablerDrawPriority,
		int shadowMapId,
		const Vector3 & drawAreaMinPos,
		const Vector3 & drawAreaMaxPos
	)
		: m_shadowMapCreateStarterDrawPriority(shadowMapCreateStarterDrawPriority)
		, m_shadowMapCreateFinisherDrawPriority(shadowMapCreateFinisherDrawPriority)
		, m_shadowMapEnablerDrawPriority(shadowMapEnablerDrawPriority)
		, m_shadowMapDisablerDrawPriority(shadowMapDisablerDrawPriority)
		, m_shadowMapId(shadowMapId)
		, m_drawAreaMinPos(drawAreaMinPos)
		, m_drawAreaMaxPos(drawAreaMaxPos)
	{
		DxLib::SetShadowMapDrawArea(
			Assets3DManager::getShadowMapAssets().lock()->getShadowMapHandle(m_shadowMapId),
			DXConverter::toVECTOR(m_drawAreaMinPos),
			DXConverter::toVECTOR(m_drawAreaMaxPos)
		);
	}

	void ShadowMapDrawer::awake()
	{
		
	}

	void ShadowMapDrawer::start()
	{
		auto transform3D = getComponent<Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("ShadowMapDrawer not found Transform3D");
		}
		m_transform3D = transform3D;

		getGameObject().lock()->addComponent(
			std::make_shared<ShadowMapCreateStarter>(
				m_shadowMapCreateStarterDrawPriority,
				std::dynamic_pointer_cast<ShadowMapDrawer>(shared_from_this())
				));

		getGameObject().lock()->addComponent(
			std::make_shared<ShadowMapCreateFinisher>(
				m_shadowMapCreateFinisherDrawPriority,
				std::dynamic_pointer_cast<ShadowMapDrawer>(shared_from_this())
				));

		getGameObject().lock()->addComponent(
			std::make_shared<ShadowMapEnabler>(
				m_shadowMapEnablerDrawPriority,
				std::dynamic_pointer_cast<ShadowMapDrawer>(shared_from_this())
				));

		getGameObject().lock()->addComponent(
			std::make_shared<ShadowMapDisabler>(
				m_shadowMapDisablerDrawPriority,
				std::dynamic_pointer_cast<ShadowMapDrawer>(shared_from_this())
				));

		// シャドウマップが想定するライトの方向もセット
		DxLib::SetShadowMapLightDirection(
			Assets3DManager::getShadowMapAssets().lock()->getShadowMapHandle(m_shadowMapId),
			DXConverter::toVECTOR(m_transform3D.lock()->calculateLocalForwardLH())
		);
	}

	void ShadowMapDrawer::update()
	{
		
	}

	int ShadowMapDrawer::getShadowMapId() const
	{
		return m_shadowMapId;
	}

	void ShadowMapDrawer::setShadowMapId(int shadowMapId)
	{
		m_shadowMapId = shadowMapId;
	}

	const Vector3 & ShadowMapDrawer::getDrawAreaMinPos() const
	{
		return m_drawAreaMinPos;
	}

	const Vector3 & ShadowMapDrawer::getDrawAreaMaxPos() const
	{
		return m_drawAreaMaxPos;
	}

	void ShadowMapDrawer::setDrawArea(const Vector3 & minPos, const Vector3 & maxPos)
	{
		m_drawAreaMinPos = minPos;
		m_drawAreaMaxPos = maxPos;

		DxLib::SetShadowMapDrawArea(
			Assets3DManager::getShadowMapAssets().lock()->getShadowMapHandle(m_shadowMapId),
			DXConverter::toVECTOR(m_drawAreaMinPos),
			DXConverter::toVECTOR(m_drawAreaMaxPos)
		);
	}
}