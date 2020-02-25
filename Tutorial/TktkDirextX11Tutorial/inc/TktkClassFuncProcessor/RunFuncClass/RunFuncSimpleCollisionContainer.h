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
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	�uvoid runFunc(NodeType* other)�v������<NodeType>�^�̗v�f���Ǘ�����umap<int, vector<NodeType>>�v�Ɓuunordered_multimap<int, NodeType>�v�̃��b�p�[
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<NodeType>�^�̏���
	��	�E�R���X�g���N�^�̈����́uProcessingClassPtr�v�^�ƁuProcessingClassPtr�����̂Ɏg�p�����^�̋�̃|�C���^�v�^
	��	�E���̃��X�g�Ŏ��s������urunFunc(NodeType* other)�v�������Ă���
	��	�E�R���X�g���N�^�Ŏg�p�����uProcessingClassPtr�v�^�̒l���擾����uprocessingClassPtr()�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<HasFuncChecker>�^�̏���
	���@�E�uHasFuncChecker<AddClassType>::value�v�ŁuAddClassType�v�����̃R���e�i�ŊǗ�����^�����R���p�C�����ɔ���ł���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<GetGroupFuncRunner>�^�̏���
	��	�E�uTktkTemplateMetaFuncLib/TktkMetaFunc/HasFuncCheck/HasReturnIntFuncCheckMacro.h�v�́uHAS_RETURN_INT_FUNC_CHECK(funcName)�v�}�N���ō쐬���ꂽ�\����
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	*/
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker, class GetGroupFuncRunner>
	class RunFuncSimpleCollisionContainer
	{
	public:

		RunFuncSimpleCollisionContainer() = default;
		~RunFuncSimpleCollisionContainer() {}

		// �R�s�[�֎~
		RunFuncSimpleCollisionContainer(const RunFuncSimpleCollisionContainer& other) = delete;
		RunFuncSimpleCollisionContainer& operator = (const RunFuncSimpleCollisionContainer& other) = delete;

	public:

		// �Փ˔���̑g�ݍ��킹�̎�ނ��Ǘ�����z�񂪎g�p���郁��������ݒ肷��
		void setCollisionGroupPairArrayCapacity(unsigned int capacity)
		{
			m_collisionGroupPairArray.reserve(capacity);
		}

		// �Փ˔���̑g�ݍ��킹��ǉ�����
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

		// �Փ˔�����J�n����
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

		// �R���e�i�̗v�f���X�V����
		void updateContainer()
		{
			moveContainerNode();
			removeDeleteClass();
		}

		// �R���e�i�̗v�f�̊֐������s���邩��ݒ肷��
		void setIsRunFunc(bool flag)
		{
			m_isRunFunc = flag;
		}

	private:

		// �Q�̃O���[�v�ŏՓ˔�����s��
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

		// addClassList�̗v�f��runFuncClassSortedArray��runFuncClassSortedList�Ɉړ�����
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

		// �폜���ꂽ�N���X�̃|�C���^���R���e�i����폜����
		void removeDeleteClass()
		{
			// �z��̗v�f�폜
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

			// �}���`�}�b�v�̗v�f�폜
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

		// �폜���ꂽ�N���X�̃|�C���^�������̔z�񂩂�폜����
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

		// �ǉ�����N���X�̏��
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