#ifndef PARENT_CHILD_MANAGER_H_
#define PARENT_CHILD_MANAGER_H_

#include <forward_list>
#include "ChildList.h"
#include "../../ComponentBase.h"

namespace tktk
{
	class GameObject;

	// 親要素、子要素を管理するコンポーネント
	class ParentChildManager
		: public ComponentBase
	{
	public:

		ParentChildManager() = default;

		~ParentChildManager()
		{

		}

	public:

		void updateContainer();

	public:

		// 全ての子供の全てのコンポーネントの親要素が変わった時関数を呼ぶ
		void runAfterChangeParentAll(CfpPtr<GameObject> beforParent);

		// 全ての子要素を削除する
		void removeChild(CfpPtr<GameObject> child);

		// 全ての子要素を削除する
		void removeChildren();

		// 親要素を取得する
		CfpPtr<GameObject> getParent() const;

		// 親要素を設定する
		void setParent(CfpPtr<GameObject> parent);

		// 子要素のリストを取得する
		const std::forward_list<CfpPtr<GameObject>>& getChildren() const;

		// 子要素を追加する
		void addChild(CfpPtr<GameObject> child);

		// 全ての子要素にメッセージを送信する
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

	private:

		CfpPtr<GameObject> m_parent;

		ChildList m_children;
	};
}
#endif // !PARENT_CHILD_MANAGER_H_