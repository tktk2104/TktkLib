#ifndef RUN_FUNC_MANAGER_H_
#define RUN_FUNC_MANAGER_H_

#include <tuple>
#include "../ProcessingClass/ProcessingClassPtr.h"

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasRunFuncChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasUpdateContainerChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasCheckAndAddChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetIsRunFuncChecker.h>
#include "../ProcessingClass/ClassTypeChecker.h"

namespace tktk
{
	/*
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	�uvoid runFunc(...)�v������<RunFuncContainers>�^�̕����̗v�f���Ǘ�����utuple�v�̃��b�p�[
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	��	<RunFuncContainers>�^�̏���
	��	�E�����Ȃ��ō쐬�ł���
	��	�E�v�f��ǉ�����ucheckAndAdd(bool, ProcessingClassPtr, T*)�v�������Ă���
	��	�E�S�Ă̗v�f�̊֐������s����urunFunc(...)�v�������Ă���
	��	�E�e�R���e�i���X�V����uupdateContainer()�v�������Ă���
	���@�E�e�R���e�i���Ɏ��g�����N���X�̊֐������s���邩�̃t���O��ݒ肷��usetIsRunFunc(bool)�v�������Ă���
	������������������������������������������������������������������������������������������������������������������������������������������������������������������
	*/
	template <class... RunFuncContainers>
	class RunFuncManager
	{
	public:

		// �����Ɏ����Ŏ��s����֐��̐����w�肷��
		RunFuncManager(unsigned int autoRunFuncCount);
		~RunFuncManager() {}

		RunFuncManager(const RunFuncManager& other) = delete;
		RunFuncManager& operator = (const RunFuncManager& other) = delete;

	public:

		// �֐������s����
		void runFunc();

		// �R���e�i���X�V����
		void updateContainer();

		// �����̃N���X�̃|�C���^���e�֐����s�R���e�i�ɒǉ�����
		template<class T>
		void addClass(bool isStatic, ProcessingClassPtr addClass);

		// �w�肵���֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
		template<int ContainerNum>
		void setIsRunFunc(bool flag);

		// �S�Ă̊֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
		void setIsRunFuncAll(bool flag);

		// �w�肵���֐����s�R���e�i�̃|�C���^���擾
		template<int ContainerNum, class RunFuncContainer>
		RunFuncContainer* getRunFuncContainerPtr();

	private:

		// �֐������s���鏈���̎���
		template <int N, class Thead, class... Tbody>
		void runFuncImpl();

		// �֐������s���鏈���̎���
		template <int N>
		void runFuncImpl();

		// �R���e�i���X�V���鏈���̎���
		template <int N, class Thead, class... Tbody>
		void updateContainerImpl();

		// �R���e�i���X�V���鏈���̎���
		template <int N>
		void updateContainerImpl();

		// �N���X��ǉ����鏈���̎���
		template <int N, class T, class Thead, class... Tbody>
		void addClassImpl(bool isStatic, ProcessingClassPtr addClass);

		// �N���X��ǉ����鏈���̎���
		template <int N, class T>
		void addClassImpl(bool isStatic, ProcessingClassPtr addClass);

		// �֐����s�t���O��ݒ肷�鏈���̎���
		template <int N, class Thead, class... Tbody>
		void setIsRunFuncAllImpl(bool flag);

		// �֐����s�t���O��ݒ肷�鏈���̎���
		template <int N>
		void setIsRunFuncAllImpl(bool flag);

	private:

		// �e�֐����Ƃ̊֐����s�R���e�i�N���X
		std::tuple<RunFuncContainers...> m_runFuncContainers;

		// �����Ŏ��s����֐��̐�
		unsigned int m_autoRunFuncCount;
	};

	// �����Ɏ����Ŏ��s����֐��̐����w�肷��
	template<class ...RunFuncContainers>
	inline RunFuncManager<RunFuncContainers...>::RunFuncManager(unsigned int autoRunFuncCount)
		: m_autoRunFuncCount(autoRunFuncCount)
	{
	}

	// �֐������s����
	template<class ...RunFuncContainers>
	inline void RunFuncManager<RunFuncContainers...>::runFunc()
	{
		if (m_autoRunFuncCount == 0U) return;
		runFuncImpl<0, RunFuncContainers...>();
	}

	// �R���e�i���X�V����
	template<class ...RunFuncContainers>
	inline void RunFuncManager<RunFuncContainers...>::updateContainer()
	{
		updateContainerImpl<0, RunFuncContainers...>();
	}

	// �����̃N���X�̃|�C���^���e�֐����s�R���e�i�ɒǉ�����
	template<class ...RunFuncContainers>
	template<class T>
	inline void RunFuncManager<RunFuncContainers...>::addClass(bool isStatic, ProcessingClassPtr addClass)
	{
		addClassImpl<0, T, RunFuncContainers...>(isStatic, addClass);
	}

	// �w�肵���֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
	template<class ...RunFuncContainers>
	template<int ContainerNum>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFunc(bool flag)
	{
		std::get<ContainerNum>(m_runFuncContainers).setIsRunFunc(flag);
	}

	// �S�Ă̊֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
	template<class ...RunFuncContainers>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFuncAll(bool flag)
	{
		setIsRunFuncAllImpl<0, RunFuncContainers...>(flag);
	}

	// �w�肵���֐����s�R���e�i�̃|�C���^���擾
	template<class ...RunFuncContainers>
	template<int ContainerNum, class RunFuncContainer>
	inline RunFuncContainer * RunFuncManager<RunFuncContainers...>::getRunFuncContainerPtr()
	{
		return &(std::get<ContainerNum>(m_runFuncContainers));
	}

	// �֐������s���鏈���̎���
	template<class ...RunFuncContainers>
	template <int N, class Thead, class... Tbody>
	inline void RunFuncManager<RunFuncContainers...>::runFuncImpl()
	{
		runFunc_runner<>::checkAndRun(&std::get<N>(m_runFuncContainers));
		if (static_cast<unsigned int>(N + 1) >= m_autoRunFuncCount) return;
		runFuncImpl<N + 1, Tbody...>();
	}

	// �֐������s���鏈���̎���
	template<class ...RunFuncContainers>
	template <int N>
	inline void RunFuncManager<RunFuncContainers...>::runFuncImpl()
	{
		/* not value */
	}

	// �R���e�i���X�V���鏈���̎���
	template<class ...RunFuncContainers>
	template<int N, class Thead, class ...Tbody>
	inline void RunFuncManager<RunFuncContainers...>::updateContainerImpl()
	{
		updateContainer_runner<>::checkAndRun(&std::get<N>(m_runFuncContainers));
		updateContainerImpl<N + 1, Tbody...>();
	}

	// �R���e�i���X�V���鏈���̎���
	template<class ...RunFuncContainers>
	template<int N>
	inline void RunFuncManager<RunFuncContainers...>::updateContainerImpl()
	{
		/* not value */
	}

	// �N���X��ǉ����鏈���̎���
	template<class ...RunFuncContainers>
	template<int N, class T, class Thead, class ...Tbody>
	inline void RunFuncManager<RunFuncContainers...>::addClassImpl(bool isStatic, ProcessingClassPtr addClass)
	{
		checkAndAdd_runner<bool, const ProcessingClassPtr &, T*>::checkAndRun(&std::get<N>(m_runFuncContainers), isStatic, addClass, nullptr);
		addClassImpl<N + 1, T, Tbody...>(isStatic, addClass);
	}

	// �N���X��ǉ����鏈���̎���
	template<class ...RunFuncContainers>
	template<int N, class T>
	inline void RunFuncManager<RunFuncContainers...>::addClassImpl(bool isStatic, ProcessingClassPtr addClass)
	{
		/* not value */
	}

	// �֐����s�t���O��ݒ肷�鏈���̎���
	template<class ...RunFuncContainers>
	template<int N, class Thead, class ...Tbody>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFuncAllImpl(bool flag)
	{
		setIsRunFunc_runner<bool>::checkAndRun(&std::get<N>(m_runFuncContainers), flag);
		setIsRunFuncAllImpl<N + 1, Tbody...>(flag);
	}

	// �֐����s�t���O��ݒ肷�鏈���̎���
	template<class ...RunFuncContainers>
	template<int N>
	inline void RunFuncManager<RunFuncContainers...>::setIsRunFuncAllImpl(bool flag)
	{
		/* not value */
	}
}
#endif // !RUN_FUNC_MANAGER_H_