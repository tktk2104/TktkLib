#ifndef RUN_FUNC_MOVE_ONCE_CONTAINER_H_
#define RUN_FUNC_MOVE_ONCE_CONTAINER_H_

#include <forward_list>
#include <algorithm>
#include "../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	「void runFunc(...)」を持つ<NodeType>型の要素を管理する「forward_list」のラッパー
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<NodeType>型の条件
	┃	・コンストラクタの引数は「ProcessingClassPtr」型と「ProcessingClassPtrを作るのに使用した型の空のポインタ」型
	┃	・このリストで実行させる「runFunc(...)」を持っている
	┃	・コンストラクタで使用した「ProcessingClassPtr」型の値を取得する「processingClassPtr()」を持っている
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<HasFuncChecker>型の条件
	┃　・「HasFuncChecker<AddClassType>::value」で「AddClassType」がこのコンテナで管理する型かをコンパイル時に判定できる
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃※このコンテナは一度関数を呼ぶと呼んだ関数を持つポインタは自信のリストから削除される
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	*/
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	class RunFuncMoveOnceContainer
	{
	public:

		RunFuncMoveOnceContainer() = default;
		~RunFuncMoveOnceContainer() {}

		// コピー禁止
		RunFuncMoveOnceContainer(const RunFuncMoveOnceContainer& other) = delete;
		RunFuncMoveOnceContainer& operator = (const RunFuncMoveOnceContainer& other) = delete;

	public:

		template <class AddClassType, std::enable_if_t<HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr)
		{
			m_runFuncClassList.push_front(NodeType(newClass, ptr));
		}

		template <class AddClassType, std::enable_if_t<!HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr) {}

		// 自身のコンテナのNodeTypeのrunFunc(...)を実装する
		template <class... Args>
		void runFunc(Args&&... params)
		{
			if (!m_isRunFunc) return;

			std::forward_list<NodeType> tempList = std::move(m_runFuncClassList);
			m_runFuncClassList = std::forward_list<NodeType>();

			std::for_each(
				std::begin(tempList),
				std::end(tempList),
				[](NodeType& node) { node.runFunc(std::forward<Args>(params)...); }
			);
		}

		// コンテナの要素の関数を実行するかを設定する
		void setIsRunFunc(bool flag)
		{
			m_isRunFunc = flag;
		}

	private:

		std::forward_list<NodeType> m_runFuncClassList;

		bool m_isRunFunc{ true };
	};
}
#endif // !RUN_FUNC_MOVE_ONCE_CONTAINER_H_
