#include "SpriteTestScript.h"

#include <TktkDirectX11Wrapper/Input/Keyboard/Keyboard.h>
#include <TktkDirectX11Wrapper/Input/Mouse/Mouse.h>

SpriteTestScript::SpriteTestScript()
{
}

void SpriteTestScript::update()
{
	auto transform = getComponent<tktk::Transform2D>();

	if (tktk::Keyboard::isPush(tktk::KEYBORD_UP))
	{
		transform->addLocalPosition(Vector2( 0.0f, -1.0f));
	}
	if (tktk::Keyboard::isPush(tktk::KEYBORD_DOWN))
	{
		transform->addLocalPosition(Vector2( 0.0f,  1.0f));
	}
	if (tktk::Keyboard::isPush(tktk::KEYBORD_LEFT))
	{
		transform->addLocalPosition(Vector2(-1.0f,  0.0f));
	}
	if (tktk::Keyboard::isPush(tktk::KEYBORD_RIGHT))
	{
		transform->addLocalPosition(Vector2( 1.0f,  0.0f));
	}

	transform->addLocalRotationDeg(0.1f);

	transform->addLocalScaleRate(Vector2(0.01f));

	if (tktk::Mouse::isTrigger(tktk::MouseButtonType::leftBtn))
	{
		transform->setLocalPosition(tktk::Mouse::mousePos());
	}
}
