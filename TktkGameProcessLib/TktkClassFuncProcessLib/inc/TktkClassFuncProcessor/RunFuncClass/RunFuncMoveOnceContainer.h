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
	┃	・このリストに要素を追加可能かを判定する「hasFuncCheck()」を持っている
	┃	・このリストで実行させる「runFunc(...)」を持っている
	┃	・コンストラクタで使用した「ProcessingClassPtr」型の値を取得する「processingClassPtr()」を持っている
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃※このコンテナは一度関数を呼ぶと呼んだ関数を持つポインタは自信のリストから削除される
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	*/
	template <class NodeType>
	class RunFuncMoveOnceContainer
	{
	public:

		RunFuncMoveOnceContainer() = default;
		~RunFuncMoveOnceContainer() {}

		RunFuncMoveOnceContainer(const RunFuncMoveOnceContainer& other) = delete;
		RunFuncMoveOnceContainer& operator = (const RunFuncMoveOnceContainer& other) = delete;

	public:

		// 引数でNodeTypeを作成し、そのhasFuncCheck()がtrueだったらaddClassListに追加する
		template <class T>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T* ptr = nullptr);

		// 自身のコンテナのNodeTypeのrunFunc(...)を実装する
		template <class... Args>
		void runFunc(const Args &... params);

		// コンテナの要素の関数を実行するかを設定する
		void setIsRunFunc(bool flag);

	private:

		std::forward_list<NodeType> m_runFuncClassList;

		bool m_isRunFunc{ true };
	};

	// 引数でNodeTypeを作成し、そのhasFuncCheck()がtrueだったらaddClassListに追加する
	template<class NodeType>
	template<class T>
	inline void RunFuncMoveOnceContainer<NodeType>::checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T * ptr)
	{
		NodeType addNode = NodeType(newClass, ptr);
		if (!addNode.hasFuncCheck()) return;
		m_runFuncClassList.push_front(std::move(addNode));
	}

	// 自身のコンテナのNodeTypeのrunFunc(...)を実装する
	template<class NodeType>
	template<class ...Args>
	inline void RunFuncMoveOnceContainer<NodeType>::runFunc(const Args & ...params)
	{
		if (!m_isRunFunc) return;

		std::forward_list<NodeType> tempList = std::move(m_runFuncClassList);
		m_runFuncClassList = std::forward_list<NodeType>();

		std::for_each(
			std::begin(tempList),
			std::end(tempList),
			[](NodeType& node) { node.runFunc(params...); }
		);
	}

	// コンテナの要素の関数を実行するかを設定する
	template<class NodeType>
	inline void RunFuncMoveOnceContainer<NodeType>::setIsRunFunc(bool flag)
	{
		m_isRunFunc = flag;
	}
}
#endif // !RUN_FUNC_MOVE_ONCE_CONTAINER_H_
