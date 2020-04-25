#ifndef PARENT_CHILD_MANAGER_H_
#define PARENT_CHILD_MANAGER_H_

#include "../../ComponentBase.h"
#include "../../../GameObject/GameObjectPtr.h"
#include "ChildList.h"

namespace tktk
{
	class ParentChildManager
		: public ComponentBase
	{
	public:

		ParentChildManager() = default;

	public:

		void updateContainer();

	public:

		// 全ての子供の全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// 全ての子要素を削除する
		void removeChild(const GameObjectPtr& child);

		// 全ての子要素を殺す
		void destroyChildren();

		// 親要素を取得する
		const GameObjectPtr& getParent() const;

		// 親要素を設定する
		void setParent(const GameObjectPtr& parent);

		// 子要素のリストを取得する
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// 子要素を追加する
		void addChild(const GameObjectPtr& child);

		//// 全ての子要素にメッセージを送信する
		//void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

	public:

		GameObjectPtr m_parent;

		ChildList m_childList;
	};
}
#endif // !PARENT_CHILD_MANAGER_H_