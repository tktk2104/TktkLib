#ifndef RUN_FUNC_SORTED_CONTAINER_H_
#define RUN_FUNC_SORTED_CONTAINER_H_

#include <limits>
#include <vector>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "../ProcessingClass/ProcessingClassPtr.h"

// ???
#undef min

namespace tktk
{
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	「void runFunc(...)」を持つ<NodeType>型の要素を管理する「map<float, vector<NodeType>>」と「multimap<float, NodeType>」のラッパー
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<NodeType>型の条件
	┃	・コンストラクタの引数は「ProcessingClassPtr」型と「ProcessingClassPtrを作るのに使用した型の空のポインタ」型
	┃	・このリストに要素を追加可能かを判定する「hasFuncCheck()」を持っている
	┃	・このリストで実行させる「runFunc(...)」を持っている
	┃	・コンストラクタで使用した「ProcessingClassPtr」型の値を取得する「processingClassPtr()」を持っている
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<GetPriorityFuncRunner>型の条件
	┃	・「TktkTemplateMetaFuncLib/TktkMetaFunc/HasFuncCheck/HasReturnFloatFuncCheckMacro.h」の「HAS_RETURN_FLOAT_FUNC_CHECK(funcName)」マクロで作成された構造体
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	*/
	template <class NodeType, class GetPriorityFuncRunner>
	class RunFuncSortedContainer
	{
	public:

		RunFuncSortedContainer() = default;
		~RunFuncSortedContainer() {};

		RunFuncSortedContainer(const RunFuncSortedContainer& other) = delete;
		RunFuncSortedContainer& operator = (const RunFuncSortedContainer& other) = delete;

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

		// 引数の配列のNodeTypeのrunFunc(...)を実装する
		template <class... Args>
		void runFuncInNodeArray(std::vector<NodeType>* vector, const Args &... params);

		// addClassListの要素をrunFuncClassSortedArrayかrunFuncClassSortedListに移動する
		void moveContainerNode();

		// 削除されたクラスのポインタをコンテナから削除する
		void removeDeleteClass();

		// 削除されたクラスのポインタを引数の配列から削除する
		void removeDeleteClassInNodeArray(std::vector<NodeType>* vectorPtr);

	private:

		// 追加するクラスの情報
		struct AddClass
		{
			NodeType containerNode;
			float priority{ 0.0f };
			bool isStatic{ true };
		};

	private:

		std::forward_list<AddClass> m_addClassList;
		std::unordered_map<float, unsigned int> m_addStaticClassNumMap;

		std::map<float, std::vector<NodeType>> m_runFuncClassSortedArrayMap;
		std::multimap<float, NodeType> m_runFuncClassSortedList;

		bool m_isRunFunc{ true };
	};

	// 引数でNodeTypeを作成し、そのhasFuncCheck()がtrueだったらaddClassListに追加する
	template<class NodeType, class GetPriorityFuncRunner>
	template<class T>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T * ptr)
	{
		float priority = GetPriorityFuncRunner::checkAndRun(newClass->castPtr<T>());
		AddClass addClass{ NodeType(newClass, ptr), priority, isStatic };
		if (!addClass.containerNode.hasFuncCheck()) return;
		if (isStatic)
		{
			if (m_addStaticClassNumMap.find(priority) == std::end(m_addStaticClassNumMap)) m_addStaticClassNumMap.emplace(priority, 0U);
			++m_addStaticClassNumMap.at(priority);
		}
		m_addClassList.push_front(std::move(addClass));
	}

	// 自身のコンテナのNodeTypeのrunFunc(...)を実装する
	template<class NodeType, class GetPriorityFuncRunner>
	template<class ...Args>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::runFunc(const Args & ...params)
	{
		if (!m_isRunFunc) return;

		auto arrayMapItr = std::begin(m_runFuncClassSortedArrayMap);
		float curPriority = (std::begin(m_runFuncClassSortedList) == std::end(m_runFuncClassSortedList)) ? std::numeric_limits<float>::min() : (*std::begin(m_runFuncClassSortedList)).first;

		if (m_runFuncClassSortedList.empty())
		{
			std::for_each(
				std::begin(m_runFuncClassSortedArrayMap),
				std::end(m_runFuncClassSortedArrayMap),
				[this, &params...](auto& node) { runFuncInNodeArray(&node.second, params...); }
			);
			return;
		}

		for (auto& node : m_runFuncClassSortedList)
		{
			while (arrayMapItr != std::end(m_runFuncClassSortedArrayMap) && (*arrayMapItr).first < curPriority)
			{
				runFuncInNodeArray(&(*arrayMapItr).second, params...);
				++arrayMapItr;
			}
			node.second.runFunc(params...);
			if (curPriority < node.first) curPriority = node.first;
		}

		std::for_each(
			arrayMapItr,
			std::end(m_runFuncClassSortedArrayMap),
			[this, &params...](auto & node) { runFuncInNodeArray(&node.second, params...); }
		);
	}

	// コンテナの要素を更新する
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::updateContainer()
	{
		moveContainerNode();
		removeDeleteClass();
	}

	// コンテナの要素の関数を実行するかを設定する
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::setIsRunFunc(bool flag)
	{
		m_isRunFunc = flag;
	}

	// 引数の配列のNodeTypeのrunFunc(...)を実装する
	template<class NodeType, class GetPriorityFuncRunner>
	template<class ...Args>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::runFuncInNodeArray(std::vector<NodeType>* vector, const Args & ...params)
	{
		std::for_each(
			std::begin(*vector),
			std::end(*vector),
			[&params...](auto& node) { node.runFunc(params...); }
		);
	}
	
	// addClassListの要素をrunFuncClassSortedArrayかrunFuncClassSortedListに移動する
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::moveContainerNode()
	{
		for (const auto& node : m_addStaticClassNumMap)
		{
			if (m_runFuncClassSortedArrayMap.find(node.first) == std::end(m_runFuncClassSortedArrayMap))
			{
				m_runFuncClassSortedArrayMap.emplace(node.first, std::vector<NodeType>());
			}
			m_runFuncClassSortedArrayMap.at(node.first).reserve(m_runFuncClassSortedArrayMap.at(node.first).size() + node.second);
		}
		m_addStaticClassNumMap.clear();

		for (auto& node : m_addClassList)
		{
			if (node.isStatic)
			{
				m_runFuncClassSortedArrayMap.at(node.priority).push_back(std::move(node.containerNode));
				continue;
			}
			m_runFuncClassSortedList.insert(std::make_pair(node.priority, std::move(node.containerNode)));
		}
		m_addClassList.clear();
	}

	// 削除されたクラスのポインタをコンテナから削除する
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::removeDeleteClass()
	{
		for (auto itr = std::begin(m_runFuncClassSortedArrayMap); itr != std::end(m_runFuncClassSortedArrayMap);)
		{
			removeDeleteClassInNodeArray(&((*itr).second));

			if ((*itr).second.empty())
			{
				itr = m_runFuncClassSortedArrayMap.erase(itr);
				continue;
			}
			++itr;
		}

		for (auto itr = std::begin(m_runFuncClassSortedList); itr != std::end(m_runFuncClassSortedList);)
		{
			if ((*itr).second.processingClassPtr().isNull())
			{
				itr = m_runFuncClassSortedList.erase(itr);
				continue;
			}
			++itr;
		}
	}

	// 削除されたクラスのポインタを引数の配列から削除する
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::removeDeleteClassInNodeArray(std::vector<NodeType> * vectorPtr)
	{
		for (auto itr = std::begin(*vectorPtr); itr != std::end(*vectorPtr);)
		{
			if ((*itr).processingClassPtr().isNull())
			{
				itr = (*vectorPtr).erase(itr);
				continue;
			}
			++itr;
		}
	}
}
#endif // !RUN_FUNC_SORTED_CONTAINER_H_