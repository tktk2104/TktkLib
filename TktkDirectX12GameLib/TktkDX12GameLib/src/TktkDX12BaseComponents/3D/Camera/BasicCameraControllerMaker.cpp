#include "TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h"

namespace tktk
{
	BasicCameraControllerMaker BasicCameraControllerMaker::m_self;

	BasicCameraControllerMaker& BasicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = BasicCameraControllerMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// �J�����A�X�y�N�g��̃f�t�H���g�l�̓Q�[���X�N���[���̔䗦
		m_self.m_initCameraAspect = DX12GameManager::getWindowSize().x / DX12GameManager::getWindowSize().y;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<BasicCameraController> BasicCameraControllerMaker::create()
	{
		return m_user->createComponent<BasicCameraController>(
			m_initCameraId,
			m_initCameraFov,
			m_initCameraAspect,
			m_initCameraNear,
			m_initCameraFar
			);
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFov(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFov = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraAspect(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraAspect = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraNear(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraNear = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFar(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraFar = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraIdImpl(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_initCameraId = value;
		return *this;
	}
}