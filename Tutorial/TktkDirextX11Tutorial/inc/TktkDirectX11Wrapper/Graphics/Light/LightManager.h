#ifndef LIGHT_MANAGER_H_
#define LIGHT_MANAGER_H_

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "LightUpdater.h"

namespace tktk
{
	// 「LightUpdater」に簡単にアクセスするためのクラス
	class LightManager
	{
	public:

		// 「LightUpdater」を生成
		static void setUp();

	public:

		// 新たなライトを生成する
		static void create(
			int id,
			const Color& ambientColor,
			const Color& diffuseColor,
			const Color& specularColor,
			const Vector3& position
		);

		// 指定したライトを削除する
		static void erase(int id);

		// 全てのライトを削除する
		void clear();

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

		// 今有効になっているライトを管理するクラスのリストを作成する（引数で取得型）
		static void createEnableLightList(std::forward_list<LightData*>* result);

		// 今有効になっているライトを管理するクラスのリストを作成する（戻り値で取得型）
		static std::forward_list<LightData*> createEnableLightList();

	private:

		static CfpPtr<LightUpdater> m_updaterPtr;
	};
}
#endif // !LIGHT_MANAGER_H_