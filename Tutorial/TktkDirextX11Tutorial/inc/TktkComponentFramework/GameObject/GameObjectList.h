#ifndef GAME_OBJECT_LIST_H_
#define GAME_OBJECT_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

namespace tktk
{
	class GameObject;

	// 全てのゲームオブジェクトのリスト
	class GameObjectList
	{
	public:

		GameObjectList() = default;

		// 新たなGameObjectを追加する
		void add(CfpPtr<GameObject> addGameObject);
		
		// 削除フラグの立ったGameObjectを削除する
		void removeExpandPtr();
		
		// 引数のタグを持つGameObjectを取得する
		CfpPtr<GameObject> findWithTag(int tag);
		
		// 引数のタグを持つGameObjectを全て取得する
		std::forward_list<CfpPtr<GameObject>> findWithTagAll(int tag);

		// 全てのGameObjectにメッセージを送信する
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

		// 全てのGameObjectを削除する
		void removeAll();

	private:

		std::forward_list<CfpPtr<GameObject>> m_gameObjectList;
	};
}
#endif // !GAME_OBJECT_LIST_H_