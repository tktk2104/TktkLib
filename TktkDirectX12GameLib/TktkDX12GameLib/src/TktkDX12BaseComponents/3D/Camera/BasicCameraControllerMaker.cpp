#include "TktkDX12BaseComponents/3D/Camera/BasicCameraControllerMaker.h"

namespace tktk
{
	BasicCameraControllerMaker BasicCameraControllerMaker::m_self;

	BasicCameraControllerMaker& BasicCameraControllerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = BasicCameraControllerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// カメラアスペクト比のデフォルト値はゲームスクリーンの比率
		m_self.m_initCameraAspect = DX12GameManager::getWindowSize().x / DX12GameManager::getWindowSize().y;

		// 自身の参照を返す
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
		// 値を設定して自身の参照を返す
		m_initCameraFov = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraAspect(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraAspect = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraNear(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraNear = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraFar(float value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraFar = value;
		return *this;
	}

	BasicCameraControllerMaker& BasicCameraControllerMaker::initCameraIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_initCameraId = value;
		return *this;
	}
}