#include "TktkDX12BaseComponents/3D/Camera/OrthographicCameraControllerMaker.h"

namespace tktk
{
	OrthographicCameraControllerMaker OrthographicCameraControllerMaker::m_self;

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = OrthographicCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
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
		// 値を設定して自身の参照を返す
		m_initCameraWidth = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraHeight(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraHeight = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraNear(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraNear = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraFar(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraFar = value;
		return *this;
	}

	OrthographicCameraControllerMaker& OrthographicCameraControllerMaker::initCameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraId = value;
		return *this;
	}
}