#include "CameraTestScript.h"

#include <iostream>
#include <stdexcept>

#include <DxLib.h>

void CameraTestScript::start()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (transform.isNull())
	{
		throw std::runtime_error("CameraTestScript not found Transform3D");
	}
	m_transform = transform;
}

void CameraTestScript::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_ESCAPE))
	{
		tktk::ComponentFrameworkProcessor::exitGame();
	}
}