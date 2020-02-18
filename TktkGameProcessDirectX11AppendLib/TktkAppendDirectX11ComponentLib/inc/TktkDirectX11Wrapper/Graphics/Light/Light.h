#ifndef LIGHT_H_
#define LIGHT_H_

#include <unordered_set>
#include <forward_list>
#include "Asset/LightData.h"

namespace tktk
{
	// 「LightManager」の実装の一部を隠すためのクラス
	class Light
	{
	public:

		// 新たなライトを生成する
		// ※この関数でライトを作る場合、idは1以上でなければならない
		static void create(
			int id,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);

		// 指定したライトを削除する
		// ※この関数でライトを削除する場合、idは1以上でなければならない
		static void erase(int id);

		// ライトを管理するクラスのポインタを取得する
		static LightData* getLightDataPtr(int id);

		// 指定したライトを有効にする
		static void enableLight(int id);

		// 指定したライトを無効にする
		static void disableLight(int id);

		// 全てのライトを無効にする
		static void disableLightAll();

		// 今有効になっているライトのIdの一覧を取得する
		static const std::unordered_set<int>& getEnableLightIdList();

		// 今有効になっているライトを管理するクラスのリストを作成する
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// 今有効になっているライトを管理するクラスのリストを作成する
		static std::forward_list<LightData*> createEnableLightList();
	};
}
#endif // !LIGHT_H_
