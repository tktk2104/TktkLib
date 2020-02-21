#include "SelfScaler.h"

#include <stdexcept>

void SelfScaler::start()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (transform.isNull())
	{
		throw std::runtime_error("SelfMover not found Transform3D");
	}
	m_transform = transform;
}

void SelfScaler::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_UP))
	{
		m_transform->addLocalScaleRate(Vector3::forwardLH * 0.1f);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_DOWN))
	{
		m_transform->addLocalScaleRate(Vector3::backwardLH * 0.1f);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_LEFT))
	{
		m_transform->addLocalScaleRate(Vector3::left * 0.1f);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_RIGHT))
	{
		m_transform->addLocalScaleRate(Vector3::right * 0.1f);
	}
}
