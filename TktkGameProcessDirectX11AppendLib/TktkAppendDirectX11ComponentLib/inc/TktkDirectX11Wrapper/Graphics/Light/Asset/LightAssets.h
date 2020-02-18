#ifndef LIGHT_ASSETS_H_
#define LIGHT_ASSETS_H_

#include <unordered_map>
#include "LightData.h"

namespace tktk
{
	// 「LightData」を管理するクラス
	class LightAssets
	{
	public:

		LightAssets() = default;
		~LightAssets();

		LightAssets(const LightAssets& other) = delete;
		LightAssets& operator = (const LightAssets& other) = delete;

	public:

		// 新たなライトを生成する
		void create(
			int id,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);

		// 指定したライトを削除する
		void erase(int id);

		// 全てのライトを削除する
		void clear();

		// ライトを管理するクラスのポインタを取得する
		LightData* getLightDataPtr(int id);

	private:

		// ライトを管理するクラスの連想配列
		std::unordered_map<int, LightData> m_lightAssets;
	};
}
#endif // !LIGHT_ASSETS_H_