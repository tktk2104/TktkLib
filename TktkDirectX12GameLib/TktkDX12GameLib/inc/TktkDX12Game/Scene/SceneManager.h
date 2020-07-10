#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "SceneInstanceCarrier.h"

namespace tktk
{
	// シーン管理クラス
	class SceneManager
	{
	public:

		SceneManager(unsigned int sceneNum);
		~SceneManager() = default;

	public:

		// シーンを作成して追加する
		template<class SceneType, class... Args>
		void createScene(unsigned int id, Args... constructorArgs);

		// シーンを有効にする
		void enableScene(unsigned int id);

		// シーンを無効にする
		void disableScene(unsigned int id);

		// シーンの更新処理
		void update();

	private:

		HeapArray<SceneInstanceCarrier> m_sceneArray;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// シーンを追加する
	template<class SceneType, class ...Args>
	inline void SceneManager::createScene(unsigned int id, Args ...constructorArgs)
	{
		m_sceneArray.emplaceAt(id, new SceneType(constructorArgs...));
	}
}
#endif // !SCENE_MANAGER_H_