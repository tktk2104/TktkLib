#include "TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h"

namespace tktk
{
	OrthographicCameraControllerMaker OrthographicCameraControllerMaker::m_self;

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = OrthographicCameraControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<OrthographicCameraController> OrthographicCameraControllerMaker::create()
	{
		return m_user->createComponent<OrthographicCameraController>(
			m_initCameraId,
			m_initCameraWidth,
			m_initCameraHeight,
			m_initCameraNear,
			m_initCameraFar
			);
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraWidth(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraWidth = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraHeight(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraHeight = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraNear(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraNear = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraFar(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFar = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraId = value;
		return *this;
	}
}