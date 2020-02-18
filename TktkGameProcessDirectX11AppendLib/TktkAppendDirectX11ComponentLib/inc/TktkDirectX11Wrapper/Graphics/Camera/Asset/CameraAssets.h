#ifndef CAMERA_ASSETS_H_
#define CAMERA_ASSETS_H_

#include <unordered_map>
#include "CameraData.h"

namespace tktk
{
	// 「CameraData」を管理するクラス
	class CameraAssets
	{
	public:

		CameraAssets() = default;
		~CameraAssets();

		CameraAssets(const CameraAssets& other) = delete;
		CameraAssets& operator = (const CameraAssets& other) = delete;

	public:

		// 新たなカメラを生成する
		void create(int id, const Matrix4& viewMatrix, const Matrix4& projectionMatrix);

		// 指定したカメラを削除する
		void erase(int id);

		// 全てのカメラを削除する
		void clear();

		// 指定したカメラを管理するクラスのポインタを取得する
		CameraData* getDataPtr(int id);

	private:

		// カメラを管理するクラスの連想配列
		std::unordered_map<int, CameraData> m_assets;
	};
}
#endif // !CAMERA_ASSETS_H_