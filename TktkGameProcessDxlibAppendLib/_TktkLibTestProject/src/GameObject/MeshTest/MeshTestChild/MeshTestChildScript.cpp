#include "MeshTestChildScript.h"

#include <iostream>

void MeshTestChildScript::start()
{
	auto transform = getComponent<tktk::Transform3D>();

	if (transform.isNull())
	{
		throw std::runtime_error("MeshTestChildScript not found Transform3D");
	}
	m_transform = transform;

	m_parent = getGameObject()->getParent();
}

void MeshTestChildScript::update()
{
	if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_P))
	{
		m_curBone++;
	}

	if (m_curBone >= 30) m_curBone = 2;

	auto meshDrawer = m_parent->getComponent<tktk::MeshDrawer>();

	auto tempMat
		= meshDrawer->getLocalBoneMatrix(7)
		* meshDrawer->getLocalBoneMatrix(6)
		* meshDrawer->getLocalBoneMatrix(5)
		* meshDrawer->getLocalBoneMatrix(4)
		* meshDrawer->getLocalBoneMatrix(3)
		* meshDrawer->getLocalBoneMatrix(2)
		* meshDrawer->getLocalBoneMatrix(1)
		* meshDrawer->getDxLibDraw3DParam().localMat
		;

	m_transform->setLocalPosition(tempMat.calculateTranslation());
	m_transform->setLocalRotation(tempMat.calculateRotation());

	///*if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_W))
	//{
	//	m_transform->addLocalPosition(Vector3::forwardLH);
	//}

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_S))
	//{
	//	m_transform->addLocalPosition(Vector3::backwardLH);
	//}

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_A))
	//{
	//	m_transform->addLocalPosition(Vector3::left);
	//}

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_PUSHING, tktk::KeyboardKeyType::KEYBOARD_D))
	//{
	//	m_transform->addLocalPosition(Vector3::right);
	//}*/

	//if (tktk::Keyboard::getState(tktk::InputType::INPUT_BEGIN, tktk::KeyboardKeyType::KEYBOARD_RETURN))
	//{
	//	auto pt = m_parent->getComponent<tktk::Transform3D>();

	//	m_transform->()

	//	//m_transform->setWorldPosition(Vector3::right);
	//}
}

void MeshTestChildScript::afterChangeParent(GameObjectPtr beforParent)
{
	std::cout << "change!" << std::endl;
}
