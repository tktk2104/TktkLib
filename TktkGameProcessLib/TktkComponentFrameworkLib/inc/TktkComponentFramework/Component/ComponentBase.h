#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "../GameObject/GameObject.h"

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

	void afterChangeParent(tktk::CfpPtr<GameObject> beforParent);	// 子要素が変更された後に呼ばれる
	void onCollisionEnter(tktk::CfpPtr<GameObject> other);			// 衝突開始時に呼ばれる
	void onCollisionStay(tktk::CfpPtr<GameObject> other);			// 衝突中に呼ばれる
	void onCollisionExit(tktk::CfpPtr<GameObject> other);			// 衝突終了時に呼ばれる

	void handleMessage(int eventMessageType, const tktk::SafetyVoidPtr& param);	// メッセージを受信したときに呼ばれる
	*/
	class ComponentBase
	{
	public:

		ComponentBase(
			float drawPriority = 0.0f,
			int collisionGroupType = 0
		);

		virtual ~ComponentBase();

	public:

		void frameBegin();

		// アクティブフラグの取得
		bool isActive() const;

		// 次のフレームでアクティブフラグを設定
		void setActive(bool isActive);

		// 更新優先度を取得
		float getUpdatePriority() const;

		// 描画するレイヤーを取得
		float getDrawPriority() const;

		// 衝突判定のグループを取得
		int getCollisionGroup() const;

		// GameObjectを取得
		CfpPtr<GameObject> getGameObject() const;

		// 自身の所持者となるGameObjectを再設定（マネージャー用関数）
		void setGameObject(CfpPtr<GameObject> user);

		// 自身の更新優先度を設定（マネージャー用関数）
		void setUpdatePriority(float updatePriority);

	public:

		// 最初に見つけたテンプレートパラメータのコンポーネントを取得
		template <class T>
		CfpPtr<T> getComponent() const;

		// 全てのテンプレートパラメータのコンポーネントを取得
		template <class T>
		std::forward_list<CfpPtr<T>> getComponentAll() const;

	private:

		bool m_isActive{ true };
		bool m_nextFrameIsActive{ true };

		CfpPtr<GameObject> m_user;

		float m_updatePriority{ 0.0f };
		float m_drawPriority{ 0.0f };
		int m_collisionGroupType{ 0 };
	};

	template<class T>
	inline CfpPtr<T> ComponentBase::getComponent() const
	{
		return getGameObject()->getComponent<T>();
	}

	template<class T>
	inline std::forward_list<CfpPtr<T>> ComponentBase::getComponentAll() const
	{
		return getGameObject()->getComponentAll<T>();
	}
}
#endif // !COMPONENT_BASE_H_