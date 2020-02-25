#ifndef CAMERA_H_
#define CAMERA_H_

#include "Asset/CameraData.h"

namespace tktk
{
	// 「CameraManager」の実装の一部を隠すためのクラス
	class Camera
	{
	public:

		// 新たなカメラを生成する
		static void create(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		// 指定したカメラを削除する
		static void erase(int id);

		// 指定したカメラを管理するクラスのポインタを取得する
		static CameraData* getDataPtr(int id);
	};
}
#endif // !CAMERA_H_