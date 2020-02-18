#ifndef CAMERA_MANAGER_H_
#define CAMERA_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/CameraAssets.h"

namespace tktk
{
	// 「CameraAssets」に簡単にアクセスするためのクラス
	class CameraManager
	{
	public:

		// 「CameraAssets」を生成
		static void setUp();

	public:

		// 新たなカメラを生成する
		static void create(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		// 指定したカメラを削除する
		static void erase(int id);

		// 全てのカメラを削除する
		static void clear();

		// 指定したカメラを管理するクラスのポインタを取得する
		static CameraData* getDataPtr(int id);

	private:

		static CfpPtr<CameraAssets> m_assetsPtr;
	};
}
#endif // !CAMERA_MANAGER_H_