#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include "ComponentPtr.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/GameObjectPtr.h"

namespace tktk
{
	/*
	コンポーネントの基底クラス
	<PolymorphismFunc>

	void awake();				// 生成直後（コンストラクタが呼ばれた後）に呼ばれる
	void start();				// 生成した次のフレームの最初に呼ばれる
	void onEnable();			// 非アクティブからアクティブ状態に移行した時に呼ばれる
	void onDisable();			// アクティブから非アクティブ状態に移行した時に呼ばれる
	void onDestroy();			// 削除フラグが立った瞬間（デストラクタが呼ばれる前）に呼ばれる
	void update();				// 毎フレーム呼ばれる

	void afterChangeParent	(const tktk::GameObjectPtr& beforParent);	// 子要素が変更された後に呼ばれる
	void onCollisionEnter	(const tktk::GameObjectPtr& other);			// 衝突開始時に呼ばれる
	void onCollisionStay	(const tktk::GameObjectPtr& other);			// 衝突中に呼ばれる
	void onCollisionExit	(const tktk::GameObjectPtr& other);			// 衝突終了時に呼ばれる
	*/
	class ComponentBase
	{
	public:

		ComponentBase(float drawPriority = 0.0f, const int collisionGroup = 0);
		virtual ~ComponentBase();

	public:

		float getDrawPriority() const;

		int getCollisionGroup() const;

		bool activeChangeCheck();

		void setActive(bool activeFlag);

		void destroy();

		bool isActive() const;

		bool isDead() const;

	public:

		const GameObjectPtr& getGameObject() const;

		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

	public:

		void setUser(const GameObjectPtr& user);

	private:

		const float		m_drawPriority;
		const int		m_collisionGroup;
		bool			m_isActive			{ true };
		bool			m_nextFrameActive	{ true };
		bool			m_isDead			{ false };
		GameObjectPtr	m_user				{ };
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class ComponentType>
	inline ComponentPtr<ComponentType> ComponentBase::getComponent() const
	{
		if (m_user.expired()) return ComponentPtr<ComponentType>();
		return m_user->getComponent<ComponentType>();
	}

	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> ComponentBase::getComponents() const
	{
		if (m_user.expired()) return std::forward_list<ComponentPtr<ComponentType>>();
		return m_user->getComponents<ComponentType>();
	}
}
#endif // !COMPONENT_BASE_H_