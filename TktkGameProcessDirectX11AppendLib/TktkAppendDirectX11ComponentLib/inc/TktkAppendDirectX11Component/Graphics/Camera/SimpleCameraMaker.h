#ifndef SIMPLE_CAMERA_MAKER_H_
#define SIMPLE_CAMERA_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SimpleCamera.h"

namespace tktk
{
	class SimpleCameraMaker
	{
	public:

		// インスタンス作成開始
		static SimpleCameraMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<SimpleCamera> create();

		SimpleCameraMaker& cameraId(int value);

		SimpleCameraMaker& cameraFov(float value);

		SimpleCameraMaker& cameraNear(float value);

		SimpleCameraMaker& cameraFar(float value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static SimpleCameraMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		int m_cameraId{ 0 };
		float m_cameraFov{ 45.0f };
		float m_cameraNear{ 0.01f };
		float m_cameraFar{ 1000.0f };
	};
}
#endif // !SIMPLE_CAMERA_MAKER_H_