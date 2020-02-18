#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetGameObjectChecker.h>
#include "GameObjectTagList.h"
#include "../Component/ComponentList.h"
#include "../Component/ComponentUpdatePrioritySetter.h"

namespace tktk
{
	class ParentChildManager;

	// ゲームオブジェクトクラス
	class GameObject
	{
	public:

		GameObject(bool isStatic);

		virtual ~GameObject();

	// 親子関係関数
	public:

		// 親要素を取得
		CfpPtr<GameObject> getParent() const;
		
		// 親要素を設定
		void setParent(CfpPtr<GameObject> parent);
		
		// 子要素のリストを取得
		const std::forward_list<CfpPtr<GameObject>>& getChildren() const;
		
		// 子要素をリストに追加する
		void addChild(CfpPtr<GameObject> child);
		
		// 指定した子要素をリストから削除する
		void removeChild(CfpPtr<GameObject> child);
		
		// 全ての子要素にメッセージを送信する
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param = SafetyVoidPtr());
		
	// コンポーネント関連関数
	public:

		// 最初に見つけたテンプレートパラメータのコンポーネントを取得
		template <class T>
		CfpPtr<T> getComponent() const;
		
		// 全てのテンプレートパラメータのコンポーネントを取得
		template <class T>
		std::forward_list<CfpPtr<T>> getComponentAll() const;
		
		// コンポーネントを追加する
		template <class T>
		CfpPtr<T> addComponent(T* addClass);

		// コンポーネントを生成して追加する
		template <class T, class... Args>
		CfpPtr<T> createComponent(const Args&... constructorValue);
		
		// 全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParentAll(CfpPtr<GameObject> beforParent);
		
		// 全てのコンポーネントの衝突開始関数を呼ぶ
		void runOnCollisionEnterAll(CfpPtr<GameObject> other);
		
		// 全てのコンポーネントの衝突中関数を呼ぶ
		void runOnCollisionStayAll(CfpPtr<GameObject> other);
		
		// 全てのコンポーネントの衝突終了関数を呼ぶ
		void runOnCollisionExitAll(CfpPtr<GameObject> other);

	// その他パラメータ設定/取得関数
	public:

		// 引数のタグを持っているか判定する
		bool containTag(int tag) const;

		// 自身が静的なクラスかを取得
		bool isStatic() const;

		// 削除フラグを取得
		bool isDestroy() const;

		// アクティブフラグを取得
		bool isActive() const;

		// 自身にタグを追加
		void addTag(int tag);

		// 自身のタグを削除
		void removeTag(int tag);

		// 自身を削除する
		void destroy();

		// アクティブフラグを設定する
		void setActive(bool isActive);

		// 自身のProcessPtrを設定する
		void setGameObject(CfpPtr<GameObject> selfPtr);

	// ポリモーフィズムな関数
	public:

		void awake();
		void frameBegin();
		void handleMessage(int eventMessageType, const SafetyVoidPtr& param);

	private:

		bool m_isStatic{ false };
		bool m_isDestroy{ false };
		bool m_isActive{ true };
		bool m_nextFrameIsActive{ true };

		GameObjectTagList m_tagList;
		ComponentList m_componentList;
		CfpPtr<GameObject> m_selfPtr;
		CfpPtr<ParentChildManager> m_pcManager;
	};

	template<class T>
	inline CfpPtr<T> GameObject::getComponent() const
	{
		return m_componentList.getComponent<T>();
	}
	
	template<class T>
	inline std::forward_list<CfpPtr<T>> GameObject::getComponentAll() const
	{
		return m_componentList.getComponentAll<T>();
	}
	
	template<class T>
	inline CfpPtr<T> GameObject::addComponent(T* addClass)
	{
		setGameObject_runner<CfpPtr<GameObject>>::checkAndRun(addClass, m_selfPtr);

		ComponentUpdatePrioritySetter::setUpdatePriority(addClass);

		return m_componentList.add<T>(m_isStatic, addClass);
	}

	template<class T, class ...Args>
	inline CfpPtr<T> GameObject::createComponent(const Args & ...constructorValue)
	{
		return addComponent(new T(constructorValue...));
	}
}
#endif // !GAME_OBJECT_H_