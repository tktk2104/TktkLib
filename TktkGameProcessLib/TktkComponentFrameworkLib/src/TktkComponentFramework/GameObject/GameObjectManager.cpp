#include "TktkComponentFramework/GameObject/GameObjectManager.h"

#include "TktkComponentFramework/ComponentFrameworkProcessor.h"
#include "TktkComponentFramework/GameObject/GameObject.h"

namespace tktk
{
	// GameObjectを作成する
	CfpPtr<GameObject> GameObjectManager::createGameObject(bool isStatic)
	{
		return ComponentFrameworkProcessor::createGameObject(isStatic);
	}

	// 引数のタグを持つGameObjectを取得する
	CfpPtr<GameObject> GameObjectManager::findGameObjectWithTag(int tag)
	{
		return ComponentFrameworkProcessor::findGameObjectWithTag(tag);
	}

	std::forward_list<CfpPtr<GameObject>> GameObjectManager::findGameObjectsWithTag(int tag)
	{
		return ComponentFrameworkProcessor::findGameObjectsWithTag(tag);
	}

	// 全てのGameObjectにメッセージを送信する
	void GameObjectManager::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		ComponentFrameworkProcessor::sendMessage(eventMessageType, param);
	}
}