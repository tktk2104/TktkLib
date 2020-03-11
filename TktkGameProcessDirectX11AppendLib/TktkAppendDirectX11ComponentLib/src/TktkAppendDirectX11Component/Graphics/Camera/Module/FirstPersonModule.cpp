#include "TktkAppendDirectX11Component/Graphics/Camera/Module/FirstPersonModule.h"

#include <TktkComponentFramework/Time/Time.h>
#include "TktkDirectX11Wrapper/Input/Keyboard/Keyboard.h"

namespace tktk
{
	FirstPersonModule::FirstPersonModule(
		float rotateDegSpeedPerSec,
		float moveSpeedPerSec,
		bool alwaysMoveForward,
		bool enableUpDownKey
	)
		: m_rotateDegSpeedPerSec(rotateDegSpeedPerSec)
		, m_moveSpeedPerSec(moveSpeedPerSec)
		, m_alwaysMoveForward(alwaysMoveForward)
		, m_enableUpDownKey(enableUpDownKey)
	{
	}

	void FirstPersonModule::start()
	{
		m_transform = getComponent<Transform3D>();

		if (m_transform.isNull())
		{
			throw std::runtime_error("FirstPersonModule Transform3D not found");
		}
	}

	void FirstPersonModule::update()
	{
		rotate();

		if (m_enableUpDownKey) moveVertical();

		moveHorizontal();
	}

	float FirstPersonModule::getRotateDegSpeedPerSec()
	{
		return m_rotateDegSpeedPerSec;
	}

	void FirstPersonModule::setRotateDegSpeedPerSec(float deg)
	{
		m_rotateDegSpeedPerSec = deg;
	}

	float FirstPersonModule::getMoveSpeedPerSec()
	{
		return m_moveSpeedPerSec;
	}

	void FirstPersonModule::setMoveSpeedPerSec(float speed)
	{
		m_moveSpeedPerSec = speed;
	}

	bool FirstPersonModule::getAlwaysMoveForward()
	{
		return m_alwaysMoveForward;
	}

	void FirstPersonModule::setAlwaysMoveForward(bool flag)
	{
		m_alwaysMoveForward = flag;
	}

	bool FirstPersonModule::getEnableUpDownKey()
	{
		return m_enableUpDownKey;
	}

	void FirstPersonModule::setEnableUpDownKey(bool flag)
	{
		m_enableUpDownKey = flag;
	}

	void FirstPersonModule::rotate()
	{
		Vector3 rotationEuler = m_transform->calculateWorldEulerAngles();

		if (Keyboard::isPush(KEYBORD_LEFT))		rotationEuler.y -= m_rotateDegSpeedPerSec * Time::deltaTime();
		if (Keyboard::isPush(KEYBORD_RIGHT))	rotationEuler.y += m_rotateDegSpeedPerSec * Time::deltaTime();
		if (Keyboard::isPush(KEYBORD_UP))		rotationEuler.x -= m_rotateDegSpeedPerSec * Time::deltaTime();
		if (Keyboard::isPush(KEYBORD_DOWN))		rotationEuler.x += m_rotateDegSpeedPerSec * Time::deltaTime();

		if (rotationEuler.x > 89.0f && rotationEuler.x < 180.0f)	rotationEuler.x = 89.0f;
		if (rotationEuler.x > 180.0f && rotationEuler.x < 271.0f)	rotationEuler.x = 271.0f;

		m_transform->setWorldEulerAngles(rotationEuler);
	}

	void FirstPersonModule::moveHorizontal()
	{
		Matrix4 worldMat = Matrix4::identity;

		if (m_alwaysMoveForward)
		{
			worldMat = m_transform->calculateWorldMatrix();
		}
		else
		{
			Vector3 cameraRote = m_transform->calculateWorldEulerAngles();

			worldMat = Matrix4::createTRS(
				m_transform->getWorldPosition(),
				Quaternion::createFromEulerAngle(Vector3(0.0f, cameraRote.y, 0.0f)),
				m_transform->getWorldScaleRate()
			);
		}
		Vector3 moveVel = Vector3::zero;

		if (Keyboard::isPush(KEYBORD_W))	moveVel = worldMat.calculateForwardLH();
		if (Keyboard::isPush(KEYBORD_S))	moveVel = -worldMat.calculateForwardLH();
		if (Keyboard::isPush(KEYBORD_A))	moveVel = -worldMat.calculateRight();
		if (Keyboard::isPush(KEYBORD_D))	moveVel = worldMat.calculateRight();

		moveVel *= m_moveSpeedPerSec * Time::deltaTime();
		m_transform->addWorldPosition(moveVel);
	}

	void FirstPersonModule::moveVertical()
	{
		float verticalMoveVel = 0.0f;

		if (Keyboard::isPush(KEYBORD_SPACE)) verticalMoveVel = 1.0f;
		if (Keyboard::isPush(KEYBORD_LSHIFT) || Keyboard::isPush(KEYBORD_RSHIFT)) verticalMoveVel = -1.0f;

		verticalMoveVel *= m_moveSpeedPerSec * Time::deltaTime();
		m_transform->addWorldPosition(Vector3(0.0f, verticalMoveVel, 0.0f));
	}
}