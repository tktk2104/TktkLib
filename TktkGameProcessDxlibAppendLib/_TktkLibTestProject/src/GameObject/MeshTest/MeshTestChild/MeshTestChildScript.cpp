#include "MeshTestChildScript.h"

#include <iostream>

void MeshTestChildScript::start()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (transform.expired())
	{
		throw std::runtime_error("MeshTestChildScript not found Transform3D");
	}
	m_transform = transform;

	m_parent = getGameObject().lock()->getParent();
}

void MeshTestChildScript::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_P))
	{
		m_curBone++;
	}

	if (m_curBone >= 30) m_curBone = 2;

	auto meshDrawer = m_parent.lock()->getComponent<tktk::MeshDrawer>();

	auto tempMat
		= meshDrawer.lock()->getLocalBoneMatrix(7)
		* meshDrawer.lock()->getLocalBoneMatrix(6)
		* meshDrawer.lock()->getLocalBoneMatrix(5)
		* meshDrawer.lock()->getLocalBoneMatrix(4)
		* meshDrawer.lock()->getLocalBoneMatrix(3)
		* meshDrawer.lock()->getLocalBoneMatrix(2)
		* meshDrawer.lock()->getLocalBoneMatrix(1)
		* meshDrawer.lock()->getDxLibDraw3DParam().localMat
		;

	m_transform.lock()->setLocalPosition(tempMat.calculateTranslation());
	m_transform.lock()->setLocalRotation(tempMat.calculateRotation());

	///*if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_W))
	//{
	//	m_transform.lock()->addLocalPosition(Vector3::forwardLH);
	//}

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_S))
	//{
	//	m_transform.lock()->addLocalPosition(Vector3::backwardLH);
	//}

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_A))
	//{
	//	m_transform.lock()->addLocalPosition(Vector3::left);
	//}

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_D))
	//{
	//	m_transform.lock()->addLocalPosition(Vector3::right);
	//}*/

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_RETURN))
	//{
	//	auto pt = m_parent.lock()->getComponent<tktk::Transform3D>();

	//	m_transform.lock()->()

	//	//m_transform.lock()->setWorldPosition(Vector3::right);
	//}
}

void MeshTestChildScript::afterChangeParent(tktk::GameObjectPtr beforParent)
{
	std::cout << "change!" << std::endl;
}
