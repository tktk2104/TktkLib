#ifndef CAMERA_DATA_H_
#define CAMERA_DATA_H_

#include <TktkMath/Matrix4.h>

namespace tktk
{
	// カメラを管理するクラス
	class CameraData
	{
	public:

		CameraData(const Matrix4& viewMatrix, const Matrix4& projectionMatrix);
		~CameraData();

		CameraData(const CameraData& other) = delete;
		CameraData& operator = (const CameraData& other) = delete;

	public:

		// カメラのビュー行列のポインタを取得する
		Matrix4* getViewMatrixPtr();

		// カメラのプロジェクション行列を取得する
		Matrix4* getProjectionMatrixPtr();

	private:

		// カメラのビュー行列
		Matrix4 m_viewMatrix;

		// カメラのプロジェクション行列
		Matrix4 m_projectionMatrix;
	};
}
#endif // !CAMERA_DATA_H_