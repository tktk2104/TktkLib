#ifndef LIGHT_UPDATER_H_
#define LIGHT_UPDATER_H_

#include <memory>
#include <forward_list>
#include <unordered_set>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "Asset/LightAssets.h"

namespace tktk
{
	// 「LightAssets」で管理しているライト情報の有効無効を切り替えるクラス
	class LightUpdater
	{
	public:

		LightUpdater();
		~LightUpdater();

		LightUpdater(const LightUpdater& other) = delete;
		LightUpdater& operator = (const LightUpdater& other) = delete;

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

		// 指定したライトを有効にする
		void enableLight(int id);

		// 指定したライトを無効にする
		void disableLight(int id);

		// 全てのライトを無効にする
		void disableLightAll();

		// 今有効になっているライトのIdの一覧を取得する
		const std::unordered_set<int>& getEnableLightIdList() const;

		// 今有効になっているライトを管理するクラスのリストを作成する
		void createEnableLightList(std::forward_list<LightData*>* result);

	private:

		// 今有効になっているライトのIdの一覧
		std::unordered_set<int> m_enableLightIdList;

		// ライトアセットのポインタ
		CfpPtr<LightAssets> m_assets;
	};
}
#endif // !LIGHT_UPDATER_H_
