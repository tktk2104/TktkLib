#ifndef CHILD_LIST_H_
#define CHILD_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>

namespace tktk
{
	class GameObject;

	// 子要素のリスト
	class ChildList
	{
	public:

		ChildList() = default;
		~ChildList() {}

	public:

		// 新たな子要素を追加
		void addChild(CfpPtr<GameObject> child);

		// 子要素のリストを取得
		const std::forward_list<CfpPtr<GameObject>>& getChildren() const;

		// リストを更新する
		void updateContainer();

		// 指定の子要素を削除する
		void remove(CfpPtr<GameObject> gameObject);

		// 全ての子要素をリストから削除する
		void removeAll();

		// 全ての子要素にメッセージを送信する
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param);

	private:

		std::forward_list<CfpPtr<GameObject>> m_childList;
	};
}
#endif // !CHILD_LIST_H_