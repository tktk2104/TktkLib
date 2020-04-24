#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <memory>
#include "GameObjectTagList.h"
#include "../Component/GameObjectComponentList.h"
#include "../_MainManager/DX12GameManager.h"

namespace tktk
{
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();

	public:

		void update();

	public:

		void setActive(bool activeFlag);

		void destroy();

		bool isActive() const;

		bool isDead() const;

	public:

		void addGameObjectTag(int tag);

		void removeGameobjectTag(int tag);

		bool containGameobjectTag(int tag) const;

	public:

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		void createComponent(Args... args);

		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

	public:



	private:

		bool					m_isActive			{ true };
		bool					m_nextFrameActive	{ true };
		bool					m_isDead			{ false };
		GameObjectTagList		m_tagList			{};
		GameObjectComponentList m_componentList		{};
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType, class ...Args>
	inline void GameObject::createComponent(Args ...args)
	{
		auto createdComponent = DX12GameManager::createComponent<ComponentType>(args...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		m_componentList.add<ComponentType>(createdComponent);
	}

	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObject::getComponent() const
	{
		return m_componentList.find<ComponentType>();
	}

	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObject::getComponents() const
	{
		return m_componentList.findAll<ComponentType>();
	}
}
#endif // !GAME_OBJECT_H_