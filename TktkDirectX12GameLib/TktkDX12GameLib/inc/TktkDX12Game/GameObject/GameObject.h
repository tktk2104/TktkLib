#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <memory>
#include <utility>
#include <unordered_map>
#include "GameObjectTagList.h"
#include "../Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "../_MainManager/DX12GameManager.h"
#include "../Component/ComponentPtr.h"
#include "../Component/DefaultComponents/StateMachine/StateMachineList.h"

namespace tktk
{
	class ParentChildManager;
	class CurStateTypeList;

	// ゲームオブジェクトクラス
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

	public: /* フラグ管理関数 */

		// アクティブフラグを設定する
		void setActive(bool activeFlag);

		// オブジェクトを削除する
		void destroy();

		// アクティブフラグを取得する
		bool isActive() const;

		// 死亡フラグを取得する
		bool isDead() const;

	public: /* タグ管理関数 */

		// 自身のタグを追加する
		void addGameObjectTag(int tag);

		// 引数のタグを削除する
		void removeGameobjectTag(int tag);

		// 引数のタグを持っているかの判定を行う
		bool containGameobjectTag(int tag) const;

	public: /* コンポーネント取得処理 */

		// テンプレート引数の型のコンポーネントを引数の値を使って作る
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args);

		// テンプレート引数の型のコンポーネントを持っていたら取得し、持っていなかったらnullptrを返す
		// ※複数同じ型のコンポーネントを所持していた場合、最初に見つけた１つを取得する
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		// テンプレート引数の型のコンポーネントを全て取得する
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

	public: /* コンポーネント関数呼び出し処理 */

		// 全てのメッセージ取得関数を呼ぶ
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

		// 全ての子供の全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// 全てのコンポーネントの衝突開始関数を呼ぶ
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突中関数を呼ぶ
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// 全てのコンポーネントの衝突終了関数を呼ぶ
		void runOnCollisionExitAll(const GameObjectPtr& other);

	public: /* 親子関係処理 */

		// 親要素を取得
		const GameObjectPtr& getParent() const;

		// 親要素を設定
		void setParent(const GameObjectPtr& parent);

		// 子要素のリストを取得
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// 子要素をリストに追加する
		void addChild(const GameObjectPtr& child);

		// 指定した子要素をリストから削除する
		void removeChild(const GameObjectPtr& child);

		// 全ての子要素にメッセージを送信する
		void sendMessage(unsigned int messageId, const MessageAttachment& value = {});

	public: /* ステートマシン関係処理 */

		// ステートの種類を引数として渡し、ステートマシンの操作に必要なコンポーネントを準備する
		void setupStateMachine(const StateMachineListInitParam& initParam);

		/**************************************************
		【setupStateMachine()の引数の作成例】

		StateMachineListInitParam stateList = 
		{
			{
				MOVE_STATE, 
				{
					{
						WALK_STATE,
						{
							{ BEGIN_MOVE_STATE },	// “RUN_STATE”の“BEGIN_MOVE_STATE”と同一のステートで“WALK_STATE”状態の時にisActive = trueになる
							{ MOVING_STATE },
							{ END_MOVE_STATE }
						}
					},
					{
						RUN_STATE,
						{
							{ BEGIN_MOVE_STATE },	// “RUN_STATE”の“BEGIN_MOVE_STATE”と同一のステートで“RUN_STATE”状態の時にisActive = trueになる
							{ MOVING_STATE },
							{ END_MOVE_STATE }
						}
					}

				}
			},
			{
				JUMP_STATE,
				{
					{ BEGIN_JUMP_STATE },
					{ JUMPING_STATE },
					{ END_JUMP_STATE },
				}
			},
			{ DEAD_STATE }
		}
		**************************************************/

		// ステートを追加する
		void addState(int stateType);

		// ステートを削除する
		void removeState(int stateType);

		// 全てのステートを削除する
		void clearState();

		// 引数のステートを持っているか？
		bool contain(int stateType);

		// int型の配列でステートを指定し、子要素を追加する
		// ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		void addChild(const std::vector<int>& targetState, const GameObjectPtr& child);

		// int型の配列でステートを指定し、テンプレート引数の型のコンポーネントを引数の値を使って作る
		//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(const std::vector<int>& targetState, Args&&... args);

	private:

		void createComponentImpl(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr);

	private:

		bool												m_isActive				{ true };
		bool												m_nextFrameActive		{ true };
		bool												m_isDead				{ false };
		GameObjectTagList									m_tagList				{};
		GameObjectComponentList								m_componentList			{};
		ComponentPtr<ParentChildManager>					m_parentChildManager	{};
		
		// ステートマシン関連のクラスは「setupStateMachine()」を呼ぶまで実態が作られないのでポインタにて管理
		ComponentPtr<CurStateTypeList>						m_stateTypeList			{};
		std::unique_ptr<StateMachineList>					m_stateMachineList		{};
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// テンプレート引数の型のコンポーネントを引数の値を使って作る
	template<class ComponentType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(Args&& ...args)
	{
		auto createdComponent = DX12GameManager::createComponent<ComponentType>(std::forward<Args>(args)...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		return m_componentList.add<ComponentType>(createdComponent);
	}

	// テンプレート引数の型のコンポーネントを持っていたら取得し、持っていなかったらnullptrを返す
	// ※複数同じ型のコンポーネントを所持していた場合、最初に見つけた１つを取得する
	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObject::getComponent() const
	{
		return m_componentList.find<ComponentType>();
	}

	// テンプレート引数の型のコンポーネントを全て取得する
	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObject::getComponents() const
	{
		return m_componentList.findAll<ComponentType>();
	}

	// int型の配列でステートを指定し、テンプレート引数の型のコンポーネントを引数の値を使って作る
	//  ※「{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }」で「“MOVE_STATE”内の“WALK_STATE”内の“BEGIN_MOVE_STATE”に追加」となる
	template<class ComponentType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(const std::vector<int>& targetState, Args&& ...args)
	{
		auto createdComponent = DX12GameManager::createComponent<ComponentType>(std::forward<Args>(args)...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		createComponentImpl(targetState, ComponentBasePtr(createdComponent));
		return m_componentList.add<ComponentType>(createdComponent);
	}
}
#endif // !GAME_OBJECT_H_