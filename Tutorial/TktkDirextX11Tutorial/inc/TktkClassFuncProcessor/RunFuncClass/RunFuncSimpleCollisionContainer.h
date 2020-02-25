#ifndef RUN_FUNC_SIMPLE_COLLISION_CONTAINER_H_
#define RUN_FUNC_SIMPLE_COLLISION_CONTAINER_H_

#include <vector>
#include <forward_list>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	/*
	┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	「void runFunc(NodeType* other)」を持つ<NodeType>型の要素を管理する「map<int, vector<NodeType>>」と「unordered_multimap<int, NodeType>」のラッパー
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<NodeType>型の条件
	┃	・コンストラクタの引数は「ProcessingClassPtr」型と「ProcessingClassPtrを作るのに使用した型の空のポインタ」型
	┃	・このリストで実行させる「runFunc(NodeType* other)」を持っている
	┃	・コンストラクタで使用した「ProcessingClassPtr」型の値を取得する「processingClassPtr()」を持っている
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<HasFuncChecker>型の条件
	┃　・「HasFuncChecker<AddClassType>::value」で「AddClassType」がこのコンテナで管理する型かをコンパイル時に判定できる
	┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	┃	<GetGroupFuncRunner>型の条件
	┃	・「TktkTemplateMetaFuncLib/TktkMetaFunc/HasFuncCheck/HasReturnIntFuncCheckMacro.h」の「HAS_RETURN_INT_FUNC_CHECK(funcName)」マクロで作成された構造体
	┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	*/
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker, class GetGroupFuncRunner>
	class RunFuncSimpleCollisionContainer
	{
	public:

		RunFuncSimpleCollisionContainer() = default;
		~RunFuncSimpleCollisionContainer() {}

		// コピー禁止
		RunFuncSimpleCollisionContainer(const RunFuncSimpleCollisionContainer& other) = delete;
		RunFuncSimpleCollisionContainer& operator = (const RunFuncSimpleCollisionContainer& other) = delete;

	public:

		// 衝突判定の組み合わせの種類を管理する配列が使用するメモリ幅を設定する
		void setCollisionGroupPairArrayCapacity(unsigned int capacity)
		{
			m_collisionGroupPairArray.reserve(capacity);
		}

		// 衝突判定の組み合わせを追加する
		void addCollisionGroupPair(int first, int second)
		{
			m_collisionGroupList.insert(first);
			m_collisionGroupList.insert(second);
			m_collisionGroupPairArray.push_back(std::make_pair(first, second));
		}

		template <class AddClassType, std::enable_if_t<HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr)
		{
			int collisionGroup = GetGroupFuncRunner::checkAndRun(newClass->castPtr<AddClassType>(), 0);
			if (isStatic)
			{
				if (m_addStaticClassNumMap.count(collisionGroup) == 0U) m_addStaticClassNumMap.emplace(collisionGroup, 0U);
				++m_addStaticClassNumMap.at(collisionGroup);
			}
			m_addClassList.push_front({ NodeType(newClass, ptr), collisionGroup, isStatic });
		}

		template <class AddClassType, std::enable_if_t<!HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr) {}

		// 衝突判定を開始する
		void runFunc()
		{
			if (!m_isRunFunc) return;

			std::unordered_map<int, std::vector<NodeType*>> collideTempArrayMap;

			for (const auto& collisionGroup : m_collisionGroupList)
			{
				if (m_listSizeMap.count(collisionGroup) == 0U) continue;

				collideTempArrayMap.emplace(collisionGroup, std::vector<NodeType*>());
				collideTempArrayMap.at(collisionGroup).reserve(m_listSizeMap.at(collisionGroup));

				auto itrRange = m_sortedList.equal_range(collisionGroup);

				std::for_each(
					itrRange.first,
					itrRange.second,
					[&collideTempArrayMap](auto& node) { collideTempArrayMap.at(node.first).push_back(&(node.second)); }
				);
			}

			std::for_each(
				std::begin(m_collisionGroupPairArray),
				std::end(m_collisionGroupPairArray),
				[this, &collideTempArrayMap](const auto& node) { collidePair(node, collideTempArrayMap); }
			);
		}

		// コンテナの要素を更新する
		void updateContainer()
		{
			moveContainerNode();
			removeDeleteClass();
		}

		// コンテナの要素の関数を実行するかを設定する
		void setIsRunFunc(bool flag)
		{
			m_isRunFunc = flag;
		}

	private:

		// ２つのグループで衝突判定を行う
		void collidePair(const std::pair<int, int>& groupPair, const std::unordered_map<int, std::vector<NodeType*>>& collideTempArrayMap)
		{
			if (collideTempArrayMap.count(groupPair.first) != 0U)
			{
				for (NodeType* firstNode : collideTempArrayMap.at(groupPair.first))
				{
					collide(groupPair.second, firstNode, collideTempArrayMap);
				}
			}

			if (m_arrayMap.count(groupPair.first) != 0U)
			{
				for (NodeType& firstNode : m_arrayMap.at(groupPair.first))
				{
					collide(groupPair.second, &firstNode, collideTempArrayMap);
				}
			}
		}

		void collide(int secondGroup, NodeType* firstNodePtr, const std::unordered_map<int, std::vector<NodeType*>>& collideTempArrayMap)
		{
			if (collideTempArrayMap.count(secondGroup) != 0U)
			{
				for (NodeType* secondNode : collideTempArrayMap.at(secondGroup))
				{
					firstNodePtr->runFunc(secondNode);
				}
			}

			if (m_arrayMap.count(secondGroup) != 0U)
			{
				for (NodeType& secondNode : m_arrayMap.at(secondGroup))
				{
					firstNodePtr->runFunc(&secondNode);
				}
			}
		}

		// addClassListの要素をrunFuncClassSortedArrayかrunFuncClassSortedListに移動する
		void moveContainerNode()
		{
			for (const auto& node : m_addStaticClassNumMap)
			{
				m_arrayMap[node.first].reserve(m_arrayMap[node.first].size() + node.second);
			}
			m_addStaticClassNumMap.clear();

			for (auto& node : m_addClassList)
			{
				if (node.isStatic)
				{
					m_arrayMap.at(node.collisionGroup).push_back(std::move(node.containerNode));
					continue;
				}
				if (m_listSizeMap.count(node.collisionGroup) == 0U) m_listSizeMap.emplace(node.collisionGroup, 0U);
				++m_listSizeMap.at(node.collisionGroup);

				m_sortedList.insert(std::make_pair(node.collisionGroup, std::move(node.containerNode)));
			}
			m_addClassList.clear();
		}

		// 削除されたクラスのポインタをコンテナから削除する
		void removeDeleteClass()
		{
			// 配列の要素削除
			for (auto itr = std::begin(m_arrayMap); itr != std::end(m_arrayMap);)
			{
				removeDeleteClassInNodeArray(&((*itr).second));

				if ((*itr).second.empty())
				{
					itr = m_arrayMap.erase(itr);
					continue;
				}
				++itr;
			}

			// マルチマップの要素削除
			for (auto itr = std::begin(m_sortedList); itr != std::end(m_sortedList);)
			{
				if ((*itr).second.processingClassPtr().isNull())
				{
					--m_listSizeMap.at((*itr).first);
					if (m_listSizeMap.at((*itr).first) == 0U) m_listSizeMap.erase((*itr).first);

					itr = m_sortedList.erase(itr);
					continue;
				}
				++itr;
			}
		}

		// 削除されたクラスのポインタを引数の配列から削除する
		void removeDeleteClassInNodeArray(std::vector<NodeType>* vectorPtr)
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

	private:

		// 追加するクラスの情報
		struct AddClass
		{
			NodeType containerNode;
			int collisionGroup{ 0 };
			bool isStatic{ true };
		};

	private:

		std::forward_list<AddClass> m_addClassList;
		std::unordered_map<int, unsigned int> m_addStaticClassNumMap;

		std::unordered_set<int> m_collisionGroupList;
		std::vector<std::pair<int, int>> m_collisionGroupPairArray;

		std::unordered_map<int, std::vector<NodeType>> m_arrayMap;

		std::unordered_map<int, unsigned int> m_listSizeMap;
		std::unordered_multimap<int, NodeType> m_sortedList;

		bool m_isRunFunc{ true };
	};
}
#endif // !RUN_FUNC_SIMPLE_COLLISION_CONTAINER_H_