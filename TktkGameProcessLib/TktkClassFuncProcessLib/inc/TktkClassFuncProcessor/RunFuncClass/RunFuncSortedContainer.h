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
	��	�E���̃��X�g�ɗv�f��ǉ��\���𔻒肷��uhasFuncCheck()�v�������Ă���
	��	�E���̃��X�g�Ŏ��s������urunFunc(...)�v�������Ă���
	��	�E�R���X�g���N�^�Ŏg�p�����uProcessingClassPtr�v�^�̒l���擾����uprocessingClassPtr()�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<GetPriorityFuncRunner>�^�̏���
	��	�E�uTktkTemplateMetaFuncLib/TktkMetaFunc/HasFuncCheck/HasReturnFloatFuncCheckMacro.h�v�́uHAS_RETURN_FLOAT_FUNC_CHECK(funcName)�v�}�N���ō쐬���ꂽ�\����
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
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

		// ������NodeType���쐬���A����hasFuncCheck()��true��������addClassList�ɒǉ�����
		template <class T>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T* ptr = nullptr);

		// ���g�̃R���e�i��NodeType��runFunc(...)����������
		template <class... Args>
		void runFunc(const Args &... params);

		// �R���e�i�̗v�f���X�V����
		void updateContainer();

		// �R���e�i�̗v�f�̊֐������s���邩��ݒ肷��
		void setIsRunFunc(bool flag);

	private:

		// �����̔z���NodeType��runFunc(...)����������
		template <class... Args>
		void runFuncInNodeArray(std::vector<NodeType>* vector, const Args &... params);

		// addClassList�̗v�f��runFuncClassSortedArray��runFuncClassSortedList�Ɉړ�����
		void moveContainerNode();

		// �폜���ꂽ�N���X�̃|�C���^���R���e�i����폜����
		void removeDeleteClass();

		// �폜���ꂽ�N���X�̃|�C���^�������̔z�񂩂�폜����
		void removeDeleteClassInNodeArray(std::vector<NodeType>* vectorPtr);

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

	// ������NodeType���쐬���A����hasFuncCheck()��true��������addClassList�ɒǉ�����
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

	// ���g�̃R���e�i��NodeType��runFunc(...)����������
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

	// �R���e�i�̗v�f���X�V����
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::updateContainer()
	{
		moveContainerNode();
		removeDeleteClass();
	}

	// �R���e�i�̗v�f�̊֐������s���邩��ݒ肷��
	template<class NodeType, class GetPriorityFuncRunner>
	inline void RunFuncSortedContainer<NodeType, GetPriorityFuncRunner>::setIsRunFunc(bool flag)
	{
		m_isRunFunc = flag;
	}

	// �����̔z���NodeType��runFunc(...)����������
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
	
	// addClassList�̗v�f��runFuncClassSortedArray��runFuncClassSortedList�Ɉړ�����
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

	// �폜���ꂽ�N���X�̃|�C���^���R���e�i����폜����
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

	// �폜���ꂽ�N���X�̃|�C���^�������̔z�񂩂�폜����
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