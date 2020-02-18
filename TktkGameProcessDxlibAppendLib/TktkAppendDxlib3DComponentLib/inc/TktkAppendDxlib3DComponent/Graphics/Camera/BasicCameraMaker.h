#ifndef BASIC_CAMERA_MAKER_H_
#define BASIC_CAMERA_MAKER_H_

#include <memory>
#include <TktkMath/Vector3.h>
#include "BasicCamera.h"

namespace tktk
{
	// BasicCameraのインスタンスを作成する構造体
	struct BasicCameraMaker
	{
	public:

		// インスタンス作成開始
		static BasicCameraMaker& makeStart();

	public:

		// 作成する
		std::shared_ptr<BasicCamera> create();

		// 描画優先度
		BasicCameraMaker& drawPriority(float value);

		// カメラの射角？を設定する
		BasicCameraMaker& initCameraFov(float value);

		// カメラのアスペクト比を設定する
		BasicCameraMaker& initCameraAspectRate(float value);

		// カメラが描画する最も近い距離を設定する
		BasicCameraMaker& initCameraDrawingRangeNear(float value);

		// カメラが描画する最も遠い距離を設定する
		BasicCameraMaker& initCameraDrawingRangeFar(float value);

	private:

		// 自身のポインタ
		static BasicCameraMaker m_self;

	private:

		float m_drawPriority{ 0.0f };
		float m_initCameraFov{ 45.0f };
		float m_initCameraAspectRate{ 1280.0f / 720.0f };
		float m_initCameraDrawingRangeNear{ 0.1f };
		float m_initCameraDrawingRangeFar{ 1000.0f };
	};
}
#endif // !BASIC_CAMERA_MAKER_H_