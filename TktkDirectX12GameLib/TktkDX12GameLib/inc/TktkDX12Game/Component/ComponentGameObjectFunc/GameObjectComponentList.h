#ifndef GAME_OBJECT_COMPONENT_LIST_H_
#define GAME_OBJECT_COMPONENT_LIST_H_

#include <forward_list>
#include "ComponentGameObjectFuncRunner.h"

namespace tktk
{
	class ComponentBase;

	// ゲームオブジェクトが持っているコンポーネントのリスト
	class GameObjectComponentList
	{
	public:

		GameObjectComponentList() = default;

	public:

		// 新たなコンポーネントを追加する
		template <class ComponentType>
		ComponentPtr<ComponentType> add(const std::weak_ptr<ComponentType>& weakPtr);

		// テンプレート引数の型のコンポーネントを取得する
		// ※取得できなかったらnullptrを返す
		// ※複数該当するコンポーネントがあったら最初に見つけた１つを返す
		template <class ComponentType>
		ComponentPtr<ComponentType> find() const;

		// テンプレート引数の型のコンポーネントを全て取得する
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> findAll() const;

		// 全てのメッセージ取得関数を呼ぶ
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

		// 全ての「子供の全てのコンポーネントの親要素が変わった時関数」を呼ぶ
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// 全てのコンポーネントの衝突開始関数を呼ぶ
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突中関数を呼ぶ
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突終了関数を呼ぶ
		void runOnCollisionExitAll(const GameObjectPtr& other);

		// 全てのコンポーネントを殺す
		void destroyAll();

		void removeDeadComponent();

	private:

		std::forward_list<ComponentGameObjectFuncRunner> m_componentList;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// 新たなコンポーネントを追加する
	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObjectComponentList::add(const std::weak_ptr<ComponentType>& weakPtr)
	{
		m_componentList.emplace_front(weakPtr);
		return ComponentPtr<ComponentType>(weakPtr);
	}

	// テンプレート引数の型のコンポーネントを取得する
	// ※取得できなかったらnullptrを返す
	// ※複数該当するコンポーネントがあったら最初に見つけた１つを返す
	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObjectComponentList::find() const
	{
		for (const auto& node : m_componentList)
		{
			const auto& gameObjectPtr = node.getComponentBasePtr();

			if (gameObjectPtr.canCast<ComponentType>())
			{
				return gameObjectPtr.castPtr<ComponentType>();
			}
		}
		return ComponentPtr<ComponentType>();
	}

	// テンプレート引数の型のコンポーネントを全て取得する
	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObjectComponentList::findAll() const
	{
		std::forward_list<ComponentPtr<ComponentType>> result;

		for (const auto& node : m_componentList)
		{
			const auto& gameObjectPtr = node.getComponentBasePtr();

			if (gameObjectPtr.canCast<ComponentType>())
			{
				result.push_front(gameObjectPtr.castPtr<ComponentType>());
			}
		}
		return result;
	}
}
#endif // !GAME_OBJECT_COMPONENT_LIST_H_
