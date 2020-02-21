#pragma once

#include "CommonIncludePaths.h"

class LightTest
{
public:

	static void create()
	{
		GameObjectPtr gameObject = tktk::GameObjectManager::createGameObject(false);

		gameObject->addComponent(
			tktk::Transform3DMaker::makeStart()
			.rotationDeg(Vector3(30.0f, 30.0f, 0.0f))
			.create()
		);

		gameObject->addComponent(
			tktk::BasicDirectionalLightMaker::makeStart()
			.create()
		);

		gameObject->addComponent(
			tktk::ShadowMapDrawerMaker::makeStart()
			.shadowMapCreateStarterDrawPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW_BEGIN)
			.shadowMapCreateFinisherDrawPriority(DrawPriority::DRAW_PRIORITY_CREATE_SHADOW_END)
			.shadowMapEnablerDrawPriority(DrawPriority::DRAW_PRIORITY_SHADOW_ENABLE)
			.shadowMapDisablerDrawPriority(DrawPriority::DRAW_PRIORITY_SHADOW_DISABLE)
			.shadowMapId(ShadowMapId::BASE_SHADOW_MAP)
			.drawAreaMinPos(Vector3(-1000.0f, -1.0f, -1000.0f))
			.drawAreaMaxPos(Vector3(1000.0f, 1000.0f, 1000.0f))
			.create()
		);
	}
};