#ifndef RUN_FUNC_SIMPLE_CONTAINER_H_
#define RUN_FUNC_SIMPLE_CONTAINER_H_

#include <vector>
#include <forward_list>
#include <algorithm>
#include "../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	/*
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	�uvoid runFunc(...)�v������<NodeType>�^�̗v�f���Ǘ�����uvector�v�Ɓuforward_list�v�̃��b�p�[
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<NodeType>�^�̏���
	��	�E�R���X�g���N�^�̈����́uProcessingClassPtr�v�^�ƁuProcessingClassPtr�����̂Ɏg�p�����^�̋�̃|�C���^�v�^
	��	�E���̃��X�g�Ŏ��s������urunFunc(...)�v�������Ă���
	��	�E�R���X�g���N�^�Ŏg�p�����uProcessingClassPtr�v�^�̒l���擾����uprocessingClassPtr()�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<HasFuncChecker>�^�̏���
	���@�E�uHasFuncChecker<AddClassType>::value�v�ŁuAddClassType�v�����̃R���e�i�ŊǗ�����^�����R���p�C�����ɔ���ł���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	*/
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	class RunFuncSimpleContainer
	{
	public:

		RunFuncSimpleContainer() = default;
		~RunFuncSimpleContainer() {};

		RunFuncSimpleContainer(const RunFuncSimpleContainer& other) = delete;
		RunFuncSimpleContainer& operator = (const RunFuncSimpleContainer& other) = delete;

	public:

		template <class AddClassType, std::enable_if_t<HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr)
		{
			if (isStatic) ++m_addStaticClassNum;
			m_addClassList.push_front({ NodeType(newClass, ptr), isStatic });
		}

		template <class AddClassType, std::enable_if_t<!HasFuncChecker<AddClassType*>::value>* = nullptr>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, AddClassType* ptr = nullptr) {}

		// ���g�̃R���e�i��NodeType��runFunc(...)����������
		template <class... Args>
		void runFunc(Args&&... params)
		{
			if (!m_isRunFunc) return;

			std::for_each(
				std::begin(m_runFuncClassArray),
				std::end(m_runFuncClassArray),
				[&params...](NodeType& node) { node.runFunc(std::forward<Args>(params)...); }
			);

			std::for_each(
				std::begin(m_runFuncClassList),
				std::end(m_runFuncClassList),
				[&params...](NodeType& node) { node.runFunc(std::forward<Args>(params)...); }
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

		// addClassList�̗v�f��runFuncClassArray��runFuncClassList�Ɉړ�����
		void moveContainerNode()
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

		// �폜���ꂽ�N���X�̃|�C���^���R���e�i����폜����
		void removeDeleteClass()
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

	private:

		// �ǉ�����N���X�̏��
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
}
#endif // !RUN_FUNC_SIMPLE_CONTAINER_H_