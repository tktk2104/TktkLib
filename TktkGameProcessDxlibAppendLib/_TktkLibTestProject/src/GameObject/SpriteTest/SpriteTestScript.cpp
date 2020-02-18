#include "SpriteTestScript.h"

#include <stdexcept>
#include "SpriteTestState.h"

void SpriteTestScript::start()
{
	auto curStateTypeList = getComponent<tktk::CurStateTypeList>();

	if (curStateTypeList.expired())
	{
		throw std::runtime_error("SpriteTestScript not found CurStateTypeList");
	}

	m_curStateTypeList = curStateTypeList;

	m_curStateTypeList.lock()->addState(SpriteTestState::STOP_STATE);
}

void SpriteTestScript::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_ESCAPE))
	{
		tktk::ComponentFrameworkProcessor::exitGame();
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_1))
	{
		m_curStateTypeList.lock()->clearState();
		m_curStateTypeList.lock()->addState(SpriteTestState::STOP_STATE);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_2))
	{
		m_curStateTypeList.lock()->clearState();
		m_curStateTypeList.lock()->addState(SpriteTestState::WALK_STATE);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_3))
	{
		m_curStateTypeList.lock()->clearState();
		m_curStateTypeList.lock()->addState(SpriteTestState::RUN_STATE);
	}
}