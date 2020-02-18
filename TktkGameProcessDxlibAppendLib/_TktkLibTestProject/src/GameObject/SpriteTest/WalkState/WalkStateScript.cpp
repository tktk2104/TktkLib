#include "WalkStateScript.h"

void WalkStateScript::start()
{
}

void WalkStateScript::update()
{
	auto transform = getComponent<tktk::Transform2D>();

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_UP))
	{
		transform.lock()->addLocalPosition(Vector2(0.0f, -2.0f));
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_DOWN))
	{
		transform.lock()->addLocalPosition(Vector2(0.0f, 2.0f));
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_LEFT))
	{
		transform.lock()->addLocalPosition(Vector2(-2.0f, 0.0f));
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_RIGHT))
	{
		transform.lock()->addLocalPosition(Vector2(2.0f, 0.0f));
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_W))
	{
		transform.lock()->addLocalScaleRate(Vector2(0.0f, 0.1f));
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_S))
	{
		transform.lock()->addLocalScaleRate(Vector2(0.0f, -0.1f));
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_A))
	{
		transform.lock()->addLocalScaleRate(Vector2(0.1f, 0.0f));
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_D))
	{
		transform.lock()->addLocalScaleRate(Vector2(-0.1f, 0.0f));
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_Z))
	{
		transform.lock()->addLocalRotationDeg(-1.0f);
	}
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_X))
	{
		transform.lock()->addLocalRotationDeg(1.0f);
	}
}
