#ifndef COMPONENT_MANAGER_H_
#define COMPONENT_MANAGER_H_

#include <memory>
#include <map>
#include <unordered_map>
#include "ComponentUpdatePriorityList.h"
#include "ComponentMainList.h"
#include "ComponentStartFunc/ComponentSatrtList.h"
#include "ComponentCollisionFunc/ComponentCollisionList.h"
#include "ComponentDrawFunc/ComponentDrawList.h"

namespace tktk
{
	class ComponentMainList;

	// 全てのコンポーネントを管理するマネージャークラス
	class ComponentManager
	{
	public:

		ComponentManager() = default;

	public:

		// コンポーネントの更新処理
		void update();

		// コンポーネントの描画処理
		void draw();

	public:

		// コンポーネントの型ごとの更新優先度を設定する
		// ※デフォルト（0.0f）で値が小さい程、早く実行される
		template <class ComponentType>
		void addUpdatePriority(float priority);

		// 衝突判定の組み合わせを追加する
		void addCollisionGroup(int firstGroup, int secondGroup);

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		std::weak_ptr<ComponentType> createComponent(Args... args);

	private:

		// １種類のコンポーネントを管理するリストを新たに作る
		template<class ComponentType>
		void createList();

	private:

		ComponentUpdatePriorityList									m_priorityList;
		std::multimap<float, std::shared_ptr<ComponentMainList>>	m_mainMap;
		std::unordered_map<int, std::weak_ptr<ComponentMainList>>	m_addComponentMap;
		ComponentSatrtList											m_startList;
		ComponentCollisionList										m_collisionList;
		ComponentDrawList											m_drawList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// コンポーネントの型ごとの更新優先度を設定する
	// ※デフォルト（0.0f）で値が小さい程、早く実行される
	template<class ComponentType>
	inline void ComponentManager::addUpdatePriority(float priority)
	{
		m_priorityList.addPriority<ComponentType>(priority);
	}

	// テンプレート引数の型のコンポーネントを引数の値を使って作る
	template<class ComponentType, class ...Args>
	inline std::weak_ptr<ComponentType> ComponentManager::createComponent(Args ...args)
	{
		auto findNode = m_addComponentMap.find(ClassTypeChecker::getClassId<ComponentType>());
		
		if (findNode == std::end(m_addComponentMap))
		{
			createList<ComponentType>();
			findNode = m_addComponentMap.find(ClassTypeChecker::getClassId<ComponentType>());
		}
		auto createdComponent = (*findNode).second.lock()->createComponent<ComponentType>(args...);
		
		m_startList.addComponent(createdComponent);
		m_collisionList.addComponent(createdComponent);
		m_drawList.addComponent(createdComponent);

		return createdComponent;
	}

	// コンポーネントの更新処理
	template<class ComponentType>
	inline void ComponentManager::createList()
	{
		ComponentType* tempPtr = nullptr;
		auto createList = std::make_shared<ComponentMainList>(tempPtr);
		
		m_mainMap.emplace(m_priorityList.getPriority<ComponentType>(), createList);
		m_addComponentMap.emplace(ClassTypeChecker::getClassId<ComponentType>(), createList);
	}
}
#endif // !COMPONENT_MANAGER_H_