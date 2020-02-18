#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "../ComponentFrameworkProcessor.h"

namespace tktk
{
	class GameObject;

	// 全てのゲームオブジェクトのマネージャー
	class GameObjectManager
	{
	public:

		// GameObjectを作成する
		static CfpPtr<GameObject> createGameObject(bool isStatic);

		// 引数のタグを持つGameObjectを取得する
		static CfpPtr<GameObject> findGameObjectWithTag(int tag);

		// 指定したコンテナで引数のタグを持つGameObjectを取得する
		static std::forward_list<CfpPtr<GameObject>> findGameObjectsWithTag(int tag);

		// 全てのGameObjectにメッセージを送信する
		static void sendMessage(int eventMessageType, const SafetyVoidPtr& param = SafetyVoidPtr());
	};
}
#endif // !GAME_OBJECT_MANAGER_H_