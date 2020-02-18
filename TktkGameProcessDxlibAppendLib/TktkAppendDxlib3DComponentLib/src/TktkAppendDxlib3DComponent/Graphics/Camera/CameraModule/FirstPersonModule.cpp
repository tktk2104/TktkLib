#include "TktkAppendDxlib3DComponent/Graphics/Camera/CameraModule/FirstPersonModule.h"

#include <stdexcept>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>
#include <TktkMath/Quaternion.h>
#include <TktkDxlib2DWrapper/Input/Mouse/Mouse.h>
#include <TktkDxlib2DWrapper/Input/Keyboard/Keyboard.h>
#include <TktkComponentFramework/Time/Time.h>
#include <TktkDxlib2DWrapper/Graphics/Screen/Screen.h>

namespace tktk
{
	FirstPersonModule::FirstPersonModule(
		float rotationDegPerPixelOnMouseMove,
		float moveSpeedPerSec,
		bool alwaysMoveForward,
		bool enableUpDownKey
	)
		: m_rotationDegPerPixelOnMouseMove(rotationDegPerPixelOnMouseMove)
		, m_moveSpeedPerSec(moveSpeedPerSec)
		, m_alwaysMoveForward(alwaysMoveForward)
		, m_enableUpDownKey(enableUpDownKey)
	{
	}

	void FirstPersonModule::start()
	{
		auto transform3D = getComponent<tktk::Transform3D>();

		if (transform3D.expired())
		{
			throw std::runtime_error("CameraTestScript not found Transform3D");
		}
		m_selfTransform = transform3D;

		m_preMousePos = Mouse::getCursorPoint();
	}

	void FirstPersonModule::update()
	{
		rotateWithMouse();

		if (m_enableUpDownKey) moveVertical();

		inputToMove();
	}

	void FirstPersonModule::rotateWithMouse()
	{
		Vector2 curMousePos = Mouse::getCursorPoint();
		Vector2 mousePosDist = curMousePos - m_preMousePos;

		if (curMousePos.x < 0.0f)									curMousePos.x += tktk::Screen::getGameScreenSize().x;
		if (curMousePos.x > tktk::Screen::getGameScreenSize().x)	curMousePos.x -= tktk::Screen::getGameScreenSize().x;
		if (curMousePos.y < 0.0f)									curMousePos.y += tktk::Screen::getGameScreenSize().y;
		if (curMousePos.y > tktk::Screen::getGameScreenSize().y)	curMousePos.y -= tktk::Screen::getGameScreenSize().y;

		Mouse::setCursorPoint(curMousePos);

		Vector3 rotationEuler = m_selfTransform.lock()->calculateWorldEulerAngles();

		rotationEuler += Vector3(
			 (mousePosDist.y * m_rotationDegPerPixelOnMouseMove),
			 (mousePosDist.x * m_rotationDegPerPixelOnMouseMove),
			0.0f
		);

		if (rotationEuler.x > 89.0f && rotationEuler.x < 180.0f)	rotationEuler.x = 89.0f;
		if (rotationEuler.x > 180.0f && rotationEuler.x < 271.0f)	rotationEuler.x = 271.0f;

		m_selfTransform.lock()->setLocalEulerAngles(rotationEuler);

		m_preMousePos = curMousePos;
	}

	void FirstPersonModule::moveVertical()
	{
		float verticalMoveVel = 0.0f;

		if (Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_SPACE))
		{
			verticalMoveVel = 1.0f;
		}

		if (Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_LSHIFT)
			|| Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_RSHIFT))
		{
			verticalMoveVel = -1.0f;
		}

		verticalMoveVel *= tktk::Time::deltaTime() * m_moveSpeedPerSec;
		m_selfTransform.lock()->addLocalPosition(Vector3(0.0f, verticalMoveVel, 0.0f));
	}

	void FirstPersonModule::inputToMove()
	{
		Matrix4 pose = Matrix4::identity;

		if (m_alwaysMoveForward)
		{
			pose = m_selfTransform.lock()->calculateWorldMatrix();
		}
		else
		{
			Vector3 cameraRote = m_selfTransform.lock()->calculateWorldEulerAngles();

			pose = Matrix4::createScale(m_selfTransform.lock()->getWorldScaleRate())
				 * Matrix4::createFromYawPitchRoll(cameraRote.y, 0.0f, 0.0f)
				 * Matrix4::createTranslation(m_selfTransform.lock()->getWorldPosition());
		}

		Vector3 moveVel = Vector3::zero;

		if (Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_W))	moveVel = pose.calculateForwardLH();
		if (Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_S))	moveVel = -pose.calculateForwardLH();
		if (Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_A))	moveVel = -pose.calculateRight();
		if (Keyboard::getState(InputType::INPUT_PUSHING, KeyboardKeyType::KEYBOARD_D))	moveVel = pose.calculateRight();


		moveVel *= tktk::Time::deltaTime() * m_moveSpeedPerSec;
		m_selfTransform.lock()->addLocalPosition(moveVel);
	}
}