#ifndef BASIC_CAMERA_H_
#define BASIC_CAMERA_H_

#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>

namespace tktk
{
	class BasicCamera
		: public ComponentBase
	{
	public:

		BasicCamera(
			float drawPriority,					// 描画優先度
			float initCameraFov,				// カメラの射角？
			float initCameraAspectRate,			// カメラのアスペクト比
			float initCameraDrawingRangeNear,	// カメラが描画する最も近い距離
			float initCameraDrawingRangeFar		// カメラが描画する最も遠い距離
		);

	public:

		// <PolymorphismFunc>
		void afterCollide();
		void draw() const;

	public:

		// ビュー変換行列を計算し取得する
		Matrix4 calculateViewMatrix() const;

		// パースペクティブ射影行列を計算し取得する
		Matrix4 calculateProjectionMatrix() const;

		// カメラの射角？を取得する
		float getCameraFov() const;

		// カメラのアスペクト比を取得する
		float getCameraAspectRate() const;

		// カメラが描画する最も近い距離を取得する
		float getCameraDrawingRangeNear() const;

		// カメラが描画する最も遠い距離を取得する
		float getCameraDrawingRangeFar() const;

		// カメラの射角？を再設定する
		void setCameraFov(float cameraFov);

		// カメラのアスペクト比を再設定する
		void setCameraAspectRate(float cameraAspectRate);

		// カメラが描画する最も近い距離を再設定する
		void setCameraDrawingRangeNear(float cameraDrawingRangeNear);

		// カメラが描画する最も遠い距離を再設定する
		void setCameraDrawingRangeFar(float cameraDrawingRangeFar);

	private:

		// 自身の３次元座標コンポーネント
		CfpPtr<Transform3D> m_transform3D;

		// カメラの射角？
		float m_cameraFov;

		// カメラのアスペクト比
		float m_cameraAspectRate;

		// カメラが描画する最も近い距離
		float m_cameraDrawingRangeNear;

		// カメラが描画する最も遠い距離
		float m_cameraDrawingRangeFar;
	};
}
#endif // !BASIC_CAMERA_H_