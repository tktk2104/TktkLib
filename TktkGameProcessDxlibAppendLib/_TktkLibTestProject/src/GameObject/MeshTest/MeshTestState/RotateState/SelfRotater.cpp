#include "SelfRotater.h"

#include <stdexcept>

void SelfRotater::start()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (transform.isNull())
	{
		throw std::runtime_error("SelfMover not found Transform3D");
	}
	m_transform = transform;
}

void SelfRotater::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_LEFT))
	{
		m_transform->addLocalEulerAngles(Vector3::up);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_RIGHT))
	{
		m_transform->addLocalEulerAngles(Vector3::down);
	}
}
