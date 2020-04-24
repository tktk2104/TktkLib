#ifndef GAME_OBJECT_MANAGER_H_
#define GAME_OBJECT_MANAGER_H_

#include <memory>
#include <forward_list>
#include "GameObjectPtr.h"

namespace tktk
{
	class GameObject;

	class GameObjectManager
	{
	public:

		GameObjectManager() = default;

	public:

		void update();

	public:

		GameObjectPtr createGameObject();

		GameObjectPtr findGameObjectWithTag(int tag) const;

		std::forward_list<GameObjectPtr> findGameObjectsWithTag(int tag) const;

	private:

		std::forward_list<std::shared_ptr<GameObject>> m_gameObjectList;
	};
}
#endif // !GAME_OBJECT_MANAGER_H_