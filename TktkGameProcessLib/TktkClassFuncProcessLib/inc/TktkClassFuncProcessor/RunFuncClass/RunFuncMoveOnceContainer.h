#ifndef RUN_FUNC_MOVE_ONCE_CONTAINER_H_
#define RUN_FUNC_MOVE_ONCE_CONTAINER_H_

#include <forward_list>
#include <algorithm>
#include "../ProcessingClass/ProcessingClassPtr.h"

namespace tktk
{
	/*
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	�uvoid runFunc(...)�v������<NodeType>�^�̗v�f���Ǘ�����uforward_list�v�̃��b�p�[
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<NodeType>�^�̏���
	��	�E�R���X�g���N�^�̈����́uProcessingClassPtr�v�^�ƁuProcessingClassPtr�����̂Ɏg�p�����^�̋�̃|�C���^�v�^
	��	�E���̃��X�g�Ŏ��s������urunFunc(...)�v�������Ă���
	��	�E�R���X�g���N�^�Ŏg�p�����uProcessingClassPtr�v�^�̒l���擾����uprocessingClassPtr()�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<HasFuncChecker>�^�̏���
	���@�E�uHasFuncChecker<AddClassType>::value�v�ŁuAddClassType�v�����̃R���e�i�ŊǗ�����^�����R���p�C�����ɔ���ł���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	�������̃R���e�i�͈�x�֐����ĂԂƌĂ񂾊֐������|�C���^�͎��M�̃��X�g����폜�����
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	*/
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	class RunFuncMoveOnceContainer
	{
	public:

		RunFuncMoveOnceContainer() = default;
		~RunFuncMoveOnceContainer() {}

		// �R�s�[�֎~
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

		// ���g�̃R���e�i��NodeType��runFunc(...)����������
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

		// �R���e�i�̗v�f�̊֐������s���邩��ݒ肷��
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
