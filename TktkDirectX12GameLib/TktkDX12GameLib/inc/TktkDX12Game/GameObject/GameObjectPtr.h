#ifndef GAME_OBJECT_PTR_H_
#define GAME_OBJECT_PTR_H_

#include <memory>

namespace tktk
{
	class GameObject;

	class GameObjectPtr
	{
	public:

		GameObjectPtr() = default;

		explicit GameObjectPtr(const std::weak_ptr<GameObject>& weakPtr);

	public:

		bool expired() const;

		bool isSame(const GameObjectPtr& other) const;

		std::shared_ptr<GameObject> operator ->() const;

	private:

		std::weak_ptr<GameObject> m_gameObjectPtr;
	};
}
#endif // !GAME_OBJECT_PTR_H_