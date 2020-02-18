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
	��	�E���̃��X�g�ɗv�f��ǉ��\���𔻒肷��uhasFuncCheck()�v�������Ă���
	��	�E���̃��X�g�Ŏ��s������urunFunc(...)�v�������Ă���
	��	�E�R���X�g���N�^�Ŏg�p�����uProcessingClassPtr�v�^�̒l���擾����uprocessingClassPtr()�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	�������̃R���e�i�͈�x�֐����ĂԂƌĂ񂾊֐������|�C���^�͎��M�̃��X�g����폜�����
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
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

		// ������NodeType���쐬���A����hasFuncCheck()��true��������addClassList�ɒǉ�����
		template <class T>
		void checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T* ptr = nullptr);

		// ���g�̃R���e�i��NodeType��runFunc(...)����������
		template <class... Args>
		void runFunc(const Args &... params);

		// �R���e�i�̗v�f�̊֐������s���邩��ݒ肷��
		void setIsRunFunc(bool flag);

	private:

		std::forward_list<NodeType> m_runFuncClassList;

		bool m_isRunFunc{ true };
	};

	// ������NodeType���쐬���A����hasFuncCheck()��true��������addClassList�ɒǉ�����
	template<class NodeType>
	template<class T>
	inline void RunFuncMoveOnceContainer<NodeType>::checkAndAdd(bool isStatic, ProcessingClassPtr newClass, T * ptr)
	{
		NodeType addNode = NodeType(newClass, ptr);
		if (!addNode.hasFuncCheck()) return;
		m_runFuncClassList.push_front(std::move(addNode));
	}

	// ���g�̃R���e�i��NodeType��runFunc(...)����������
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

	// �R���e�i�̗v�f�̊֐������s���邩��ݒ肷��
	template<class NodeType>
	inline void RunFuncMoveOnceContainer<NodeType>::setIsRunFunc(bool flag)
	{
		m_isRunFunc = flag;
	}
}
#endif // !RUN_FUNC_MOVE_ONCE_CONTAINER_H_
