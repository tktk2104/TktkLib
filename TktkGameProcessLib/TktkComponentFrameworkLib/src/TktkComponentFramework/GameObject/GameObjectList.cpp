#include "TktkComponentFramework/GameObject/GameObjectList.h"

#include <algorithm>
#include "TktkComponentFramework/GameObject/GameObject.h"

namespace tktk
{
	// 新たなGameObjectを追加する
	void GameObjectList::add(CfpPtr<GameObject> addGameObject)
	{
		m_gameObjectList.push_front(addGameObject);
	}
	
	// 削除フラグの立ったGameObjectを削除する
	void GameObjectList::removeExpandPtr()
	{
		m_gameObjectList.remove_if(
			[](CfpPtr<GameObject> node) { return node.isNull(); }
		);
	}
	
	// 引数のタグを持つGameObjectを取得する
	CfpPtr<GameObject> GameObjectList::findWithTag(int tag)
	{
		for (CfpPtr<GameObject> gameObject : m_gameObjectList)
		{
			if (!gameObject.isNull() && gameObject->containTag(tag)) return gameObject;
		}
		return CfpPtr<GameObject>();
	}
	
	std::forward_list<CfpPtr<GameObject>> GameObjectList::findWithTagAll(int tag)
	{
		std::forward_list<CfpPtr<GameObject>> resultList;
	
		for (CfpPtr<GameObject> gameObject : m_gameObjectList)
		{
			if (!gameObject.isNull() && gameObject->containTag(tag)) resultList.push_front(gameObject);
		}
		return resultList;
	}

	void GameObjectList::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		std::for_each(
			std::begin(m_gameObjectList),
			std::end(m_gameObjectList),
			[&eventMessageType, &param](CfpPtr<GameObject> node) { node->handleMessage(eventMessageType, param); }
		);
	}

	void GameObjectList::removeAll()
	{
		std::for_each(
			std::begin(m_gameObjectList),
			std::end(m_gameObjectList),
			[](CfpPtr<GameObject> node) { node.processingClassPtr().deletePtr(); }
		);
		removeExpandPtr();
	}
}