#include "RunFuncCheckTest.h"

#include <TktkComponentFramework/ComponentFrameworkProcessor.h>
#include <TktkComponentFramework/Time/Time.h>
#include <string>
#include <iostream>

RunFuncCheckTest::RunFuncCheckTest(bool printRunFuncLog)
	: m_printRunFuncLog(printRunFuncLog)
{
	if (m_printRunFuncLog) std::cout << "[programStart]------------------------------" << std::endl;
}

RunFuncCheckTest::~RunFuncCheckTest()
{
	if (m_printRunFuncLog) std::cout << "[programEnd]------------------------------" << std::endl;
}

void RunFuncCheckTest::frameBegin()
{
	if (m_printRunFuncLog)
	{
		std::cout << "[frameBegin]------------------------------" << std::endl;

		std::cout << " input to [exit] to exit program" << std::endl;

		std::string input;

		std::cin >> input;

		if (input == "exit")
		{
			tktk::ComponentFrameworkProcessor::exitGame();
		}
		std::cout << std::endl;
	}
}

void RunFuncCheckTest::awake()
{
	if (m_printRunFuncLog) std::cout << "[awake]------------------------------" << std::endl;
}

void RunFuncCheckTest::start()
{
	if (m_printRunFuncLog) std::cout << "[start]------------------------------" << std::endl;
}

bool RunFuncCheckTest::isActive()
{
	return m_isActive;
}

void RunFuncCheckTest::onEnable()
{
	if (m_printRunFuncLog) std::cout << "[onEnable]------------------------------" << std::endl;
}

void RunFuncCheckTest::onDisable()
{
	if (m_printRunFuncLog) std::cout << "[onDisable]------------------------------" << std::endl;
}

void RunFuncCheckTest::update()
{
	if (m_printRunFuncLog) std::cout << "[update]------------------------------" << std::endl;

	std::cout << tktk::Time::deltaTime() << std::endl;
}

//bool RunFuncCheckTest::isCollide(const SafetyVoidSmartPtr<std::weak_ptr> other)
//{
//	if (m_printRunFuncLog) std::cout << "[isCollide]------------------------------" << std::endl;
//	return true;
//}
//
//void RunFuncCheckTest::onCollide(const SafetyVoidSmartPtr<std::weak_ptr> other)
//{
//	if (m_printRunFuncLog) std::cout << "[onCollide]------------------------------" << std::endl;
//}

void RunFuncCheckTest::afterCollide()
{
	if (m_printRunFuncLog) std::cout << "[afterCollide]------------------------------" << std::endl;
}

void RunFuncCheckTest::draw() const
{
	if (m_printRunFuncLog) std::cout << "[draw]------------------------------" << std::endl;
}

void RunFuncCheckTest::frameEnd()
{
	if (m_printRunFuncLog) std::cout << "[frameEnd]------------------------------" << std::endl;
}

bool RunFuncCheckTest::isDestroy()
{
	return m_isDestroy;
}

void RunFuncCheckTest::onDestroy()
{
	if (m_printRunFuncLog) std::cout << "[onDestroy]------------------------------" << std::endl;
}
