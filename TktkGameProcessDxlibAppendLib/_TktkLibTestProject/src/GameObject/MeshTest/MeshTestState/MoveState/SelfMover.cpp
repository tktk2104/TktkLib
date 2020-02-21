#include "SelfMover.h"

#include <stdexcept>

void SelfMover::start()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (transform.isNull())
	{
		throw std::runtime_error("SelfMover not found Transform3D");
	}
	m_transform = transform;
}

void SelfMover::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_UP))
	{
		m_transform->addWorldPosition(Vector3::forwardLH);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_DOWN))
	{
		m_transform->addWorldPosition(Vector3::backwardLH);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_LEFT))
	{
		m_transform->addWorldPosition(Vector3::left);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_RIGHT))
	{
		m_transform->addWorldPosition(Vector3::right);
	}
}
