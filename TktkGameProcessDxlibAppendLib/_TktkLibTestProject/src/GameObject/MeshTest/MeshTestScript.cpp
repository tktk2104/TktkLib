#include "MeshTestScript.h"

#include <iostream>
#include <algorithm>
#include "MeshTestState/MeshTestState.h"

void MeshTestScript::start()
{
	Vector3 pos = Vector3(1, 10, 100);
	Vector3 rote = Vector3(1, 10, 100);
	Vector3 scale = Vector3(1, 10, 100);

	/*Matrix4 mat4
		= Matrix4::createScale(scale)
		* Matrix4::createFromQuaternion(Quaternion::euler(rote))
		* Matrix4::createTranslation(pos);*/

	Matrix4 mat4 = Matrix4::identity;
	mat4 *= Matrix4::createScale(scale);
	mat4 *= Matrix4::createFromQuaternion(Quaternion::createFromEulerAngle(rote));
	mat4 *= Matrix4::createTranslation(pos);

	auto afterPos = mat4.calculateTranslation();
	auto afterRote = mat4.calculateRotation().calculateEulerAngle();
	auto afterScale = mat4.calculateScale();


	auto curStateTypeList = getComponent<tktk::CurStateTypeList>();

	if (curStateTypeList.expired())
	{
		throw std::runtime_error("MeshTestScript not found CurStateTypeList");
	}
	m_curStateTypeList = curStateTypeList;
	m_curStateTypeList.lock()->addState(MeshTestState::MESH_TEST_MOVE_STATE);

	auto childList = getGameObject().lock()->getChildren();
	
	if (std::begin(childList) == std::end(childList))
	{
		throw std::runtime_error("MeshTestScript not found Child");
	}
	m_child = *std::begin(childList);
}

void MeshTestScript::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_1))
	{
		m_curStateTypeList.lock()->clearState();
		m_curStateTypeList.lock()->addState(MeshTestState::MESH_TEST_MOVE_STATE);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_2))
	{
		m_curStateTypeList.lock()->clearState();
		m_curStateTypeList.lock()->addState(MeshTestState::MESH_TEST_ROTATE_STATE);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_3))
	{
		m_curStateTypeList.lock()->clearState();
		m_curStateTypeList.lock()->addState(MeshTestState::MESH_TEST_SCALE_STATE);
	}

	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_SPACE))
	{
		auto childList = getGameObject().lock()->getChildren();

		if (std::begin(childList) == std::end(childList))
		{
			//m_child.lock()->setParent(getGameObject());

			getGameObject().lock()->addChild(m_child);
		}
		else
		{
			//m_child.lock()->setParent(tktk::NULL_GAME_OBJECT);

			getGameObject().lock()->removeChild(m_child);
		}
	}

	/*if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_P))
	{
		getGameObject().lock()->destroy();
	}*/

	//m_child.lock()->

	//std::cout << m_child.lock()->getComponent<tktk::Transform3D>().lock()->calculateWorldMatrix() << std::endl;

	//std::cout 
	//	//<< m_child.lock()->getComponent<tktk::Transform3D>().lock()->getWorldPosition() << std::endl
	//	//<< m_child.lock()->getComponent<tktk::Transform3D>().lock()->calculateWorldEulerAngles() << std::endl
	//	<< m_child.lock()->getComponent<tktk::Transform3D>().lock()->getWorldScaleRate() << std::endl
	//<< std::endl;
}

void MeshTestScript::onCollisionEnter(tktk::GameObjectPtr other)
{
	std::cout << "enter" << std::endl;
}

void MeshTestScript::onCollisionStay(tktk::GameObjectPtr other)
{
	std::cout << "stay" << std::endl;
}

void MeshTestScript::onCollisionExit(tktk::GameObjectPtr other)
{
	std::cout << "exit" << std::endl;
}
