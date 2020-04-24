#include "TktkDX12Game/GameObject/GameObjectPtr.h"

#include "TktkDX12Game/GameObject/GameObject.h"

namespace tktk
{
	GameObjectPtr::GameObjectPtr(const std::weak_ptr<GameObject>& weakPtr)
		: m_gameObjectPtr(weakPtr)
	{
	}

	bool GameObjectPtr::expired() const
	{
		return m_gameObjectPtr.expired();
	}

	std::shared_ptr<GameObject> GameObjectPtr::operator->() const
	{
		if (m_gameObjectPtr.expired()) return nullptr;
		return m_gameObjectPtr.lock();
	}
}