#ifndef RUN_FUNC_SIMPLE_CONTAINER_H_
#define RUN_FUNC_SIMPLE_CONTAINER_H_

#include <vector>
#include <forward_list>
#include <algorithm>
#include "../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	「void runFunc(...)」を持つ<NodeType>型の要素を管理する「vector」と「forward_list」のラッパー
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<NodeType>型の条件
	┃	・コンストラクタの引数は「ProcessingClassPtr」型と「ProcessingClassPtrを作るのに使用した型の空のポインタ」型
	┃	・このリストに要素を追加可能かを判定する「hasFuncCheck()」を持っている
	┃	・このリストで実行させる「runFunc(...)」を持っている
	┃	・コンストラクタで使用した「ProcessingClassPtr」型の値を取得する「processingClassPtr()」を持っている
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	*/
	template <class NodeType>
	class RunFuncSimpleContainer
	{
	public:

		RunFuncSimpleContainer() = default;
		~RunFuncSimpleContainer() {};

		RunFuncSimpleContainer(const RunFuncSimpleContainer& other) = delete;
		RunFuncSimpleContainer& operator = (const RunFuncSimpleContainer& other) = delete;

	public:

		// 引数でNodeTypeを作成し、そのhasFuncCheck()がtrueだったらaddClassListに追加する
		template <class T>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T* ptr = nullptr);

		// 自身のコンテナのNodeTypeのrunFunc(...)を実装する
		template <class... Args>
		void runFunc(const Args &... params);

		// コンテナの要素を更新する
		void updateContainer();

		// コンテナの要素の関数を実行するかを設定する
		void setIsRunFunc(bool flag);

	private:

		// addClassListの要素をrunFuncClassArrayかrunFuncClassListに移動する
		void moveContainerNode();

		// 削除されたクラスのポインタをコンテナから削除する
		void removeDeleteClass();

	private:

		// 追加するクラスの情報
		struct AddClass
		{
			NodeType containerNode;
			bool isStatic{ true };
		};

	private:

		std::forward_list<AddClass> m_addClassList;
		unsigned int m_addStaticClassNum{ 0U };

		std::vector<NodeType> m_runFuncClassArray;
		std::forward_list<NodeType> m_runFuncClassList;

		bool m_isRunFunc{ true };
	};

	// 引数でNodeTypeを作成し、そのhasFuncCheck()がtrueだったらaddClassListに追加する
	template<class NodeType>
	template<class T>
	inline void RunFuncSimpleContainer<NodeType>::checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T* ptr)
	{
		AddClass addClass{ NodeType(newClass, ptr), isStatic };
		if (!addClass.containerNode.hasFuncCheck()) return;
		if (isStatic) ++m_addStaticClassNum;
		m_addClassList.push_front(std::move(addClass));
	}

	// 自身のコンテナのNodeTypeのrunFunc関数を実装する
	template<class NodeType>
	template<class ...Args>
	inline void RunFuncSimpleContainer<NodeType>::runFunc(const Args & ...params)
	{
		if (!m_isRunFunc) return;

		std::for_each(
			std::begin(m_runFuncClassArray),
			std::end(m_runFuncClassArray),
			[&params...](NodeType& node) { node.runFunc(params...); }
		);

		std::for_each(
			std::begin(m_runFuncClassList),
			std::end(m_runFuncClassList),
			[&params...](NodeType& node) { node.runFunc(params...); }
		);
	}

	// コンテナの要素を更新する
	template<class NodeType>
	inline void RunFuncSimpleContainer<NodeType>::updateContainer()
	{
		moveContainerNode();
		removeDeleteClass();
	}

	template<class NodeType>
	inline void RunFuncSimpleContainer<NodeType>::setIsRunFunc(bool flag)
	{
		m_isRunFunc = flag;
	}

	// addClassListの要素をrunFuncClassArrayかrunFuncClassListに移動する
	template<class NodeType>
	inline void RunFuncSimpleContainer<NodeType>::moveContainerNode()
	{
		m_runFuncClassArray.reserve(m_runFuncClassArray.size() + m_addStaticClassNum);
		m_addStaticClassNum = 0U;

		for (AddClass& node : m_addClassList)
		{
			if (node.isStatic)
			{
				m_runFuncClassArray.push_back(std::move(node.containerNode));
				continue;
			}
			m_runFuncClassList.push_front(std::move(node.containerNode));
		}
		m_addClassList.clear();
	}

	// 削除されたクラスのポインタをコンテナから削除する
	template<class NodeType>
	inline void RunFuncSimpleContainer<NodeType>::removeDeleteClass()
	{
		for (auto itr = std::begin(m_runFuncClassArray); itr != std::end(m_runFuncClassArray);)
		{
			if ((*itr).processingClassPtr().isNull())
			{
				itr = m_runFuncClassArray.erase(itr);
				continue;
			}
			++itr;
		}

		m_runFuncClassList.remove_if(
			[](const NodeType& node) { return node.processingClassPtr().isNull(); }
		);
	}
}
#endif // !RUN_FUNC_SIMPLE_CONTAINER_H_