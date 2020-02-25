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
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	�uvoid runFunc(...)�v������<NodeType>�^�̗v�f���Ǘ�����umap<float, vector<NodeType>>�v�Ɓumultimap<float, NodeType>�v�̃��b�p�[
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<NodeType>�^�̏���
	��	�E�R���X�g���N�^�̈����́uProcessingClassPtr�v�^�ƁuProcessingClassPtr�����̂Ɏg�p�����^�̋�̃|�C���^�v�^
	��	�E���̃��X�g�Ŏ��s������urunFunc(...)�v�������Ă���
	��	�E�R���X�g���N�^�Ŏg�p�����uProcessingClassPtr�v�^�̒l���擾����uprocessingClassPtr()�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<HasFuncChecker>�^�̏���
	���@�E�uHasFuncChecker<AddClassType>::value�v�ŁuAddClassType�v�����̃R���e�i�ŊǗ�����^�����R���p�C�����ɔ���ł���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<GetPriorityFuncRunner>�^�̏���
	��	�E�uTktkTemplateMetaFuncLib/TktkMetaFunc/HasFuncCheck/HasReturnFloatFuncCheckMacro.h�v�́uHAS_RETURN_FLOAT_FUNC_CHECK(funcName)�v�}�N���ō쐬���ꂽ�\����
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	*/
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker, class GetPriorityFuncRunner>
	class RunFuncSortedContainer
	{
	public:

		RunFuncSortedContainer() = default;
		~RunFuncSortedContainer() {};

		RunFuncSortedContainer(const RunFuncSortedContainer& other) = delete;
		RunFuncSortedContainer& operator = (const RunFuncSortedContainer& other) = delete;

	public:

		template <class AddClassType, std::enable_if_t<HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr)
		{
			float priority = GetPriorityFuncRunner::checkAndRun(newClass->castPtr<AddClassType>(), 0.0f);
			if (isStatic)
			{
				if (m_addStaticClassNumMap.find(priority) == std::end(m_addStaticClassNumMap)) m_addStaticClassNumMap.emplace(priority, 0U);
				++m_addStaticClassNumMap.at(priority);
			}
			m_addClassList.push_front({ NodeType(newClass, ptr), priority, isStatic });
		}

		template <class AddClassType, std::enable_if_t<!HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr) {}

		// ���g�̃R���e�i��NodeType��runFunc(...)����������
		template <class... Args>
		void runFunc(Args&&... params)
		{
			if (!m_isRunFunc) return;

			auto arrayMapItr = std::begin(m_runFuncClassSortedArrayMap);
			float curPriority = (std::begin(m_runFuncClassSortedList) == std::end(m_runFuncClassSortedList)) ? std::numeric_limits<float>::min() : (*std::begin(m_runFuncClassSortedList)).first;

			if (m_runFuncClassSortedList.empty())
			{
				std::for_each(
					std::begin(m_runFuncClassSortedArrayMap),
					std::end(m_runFuncClassSortedArrayMap),
					[this, &params...](auto& node) { runFuncInNodeArray(&node.second, std::forward<Args>(params)...); }
				);
				return;
			}

			for (auto& node : m_runFuncClassSortedList)
			{
				while (arrayMapItr != std::end(m_runFuncClassSortedArrayMap) && (*arrayMapItr).first < curPriority)
				{
					runFuncInNodeArray(&(*arrayMapItr).second, std::forward<Args>(params)...);
					++arrayMapItr;
				}
				node.second.runFunc(std::forward<Args>(params)...);
				if (curPriority < node.first) curPriority = node.first;
			}

			std::for_each(
				arrayMapItr,
				std::end(m_runFuncClassSortedArrayMap),
				[this, &params...](auto & node) { runFuncInNodeArray(&node.second, std::forward<Args>(params)...); }
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

		// �����̔z���NodeType��runFunc(...)����������
		template <class... Args>
		void runFuncInNodeArray(std::vector<NodeType>* vector, Args&&... params)
		{
			std::for_each(
				std::begin(*vector),
				std::end(*vector),
				[&params...](auto& node) { node.runFunc(std::forward<Args>(params)...); }
			);
		}

		// addClassList�̗v�f��runFuncClassSortedArray��runFuncClassSortedList�Ɉړ�����
		void moveContainerNode()
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

		// �폜���ꂽ�N���X�̃|�C���^���R���e�i����폜����
		void removeDeleteClass()
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
}
#endif // !RUN_FUNC_SORTED_CONTAINER_H_