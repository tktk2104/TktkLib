#ifndef CLASS_FUNC_PROCESSOR_H_
#define CLASS_FUNC_PROCESSOR_H_

#include "ProcessingClass/ProcessingSimpleContainer.h"
#include "RunFuncManager/RunFuncManager.h"
#include "ProcessingClass/CfpPtr.h"

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasAwakeChecker.h>

namespace tktk
{
	// �N���X�̃C���X�^���X���Ǘ�����@�\�̑����C���^�[�t�F�[�X
	template <class... RunFuncContainers>
	class ClassFuncProcessor
	{
	public:

		// �����Ɏ����Ŏ��s����֐��̐����w�肷��
		ClassFuncProcessor(unsigned int autoRunFuncCount);
		~ClassFuncProcessor() {};

		ClassFuncProcessor(const ClassFuncProcessor& other) = delete;
		ClassFuncProcessor& operator = (const ClassFuncProcessor& other) = delete;

	public:

		// �V���ȃN���X������processing()���s���ɒǉ�
		// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
		template <class T>
		CfpPtr<T> addClass(bool isStatic, T* rawPtr);

		// �ǉ��������N���X���쐬������Ŏ���processing()���s���ɒǉ�
		// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
		template <class T, class... Args>
		CfpPtr<T> createClass(bool isStatic, const Args&... constructorValue);

		// �w�肵���֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
		template<int ContainerNum>
		void setIsRunFunc(bool flag);

		// �S�Ă̊֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
		void setIsRunFuncAll(bool flag);

		// �w�肵���֐����s�R���e�i�̃|�C���^���擾
		template<int ContainerNum, class RunFuncContainer>
		RunFuncContainer* getRunFuncContainerPtr();

	public:

		// �������s��
		void processing();

		// ��n��
		void finalize();

	private:

		ProcessingSimpleContainer m_processingSimpleContainer;
		RunFuncManager<RunFuncContainers...> m_runFuncManager;
	};

	// �����Ɏ����Ŏ��s����֐��̐����w�肷��
	template<class ...RunFuncContainers>
	inline ClassFuncProcessor<RunFuncContainers...>::ClassFuncProcessor(unsigned int autoRunFuncCount)
		: m_runFuncManager({ autoRunFuncCount })
	{
	}

	// �V���ȃN���X������processing()���s���ɒǉ�
	// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
	template<class ...RunFuncContainers>
	template<class T>
	inline CfpPtr<T> ClassFuncProcessor<RunFuncContainers...>::addClass(bool isStatic, T * rawPtr)
	{
		ProcessingClassPtr newClass = m_processingSimpleContainer.addClass(isStatic, rawPtr);
		m_runFuncManager.addClass<T>(isStatic, newClass);
		awake_runner<>::checkAndRun(rawPtr);
		return CfpPtr<T>(newClass);
	}

	// �ǉ��������N���X���쐬������Ŏ���processing()���s���ɒǉ�
	// ��isStatic��true�ɂ���Ɠ���͌y���Ȃ邪�A�ǉ����ƍ폜�����d����
	template<class ...RunFuncContainers>
	template<class T, class ...Args>
	inline CfpPtr<T> ClassFuncProcessor<RunFuncContainers...>::createClass(bool isStatic, const Args & ...constructorValue)
	{
		return addClass<T>(isStatic, new T(constructorValue...));
	}

	// �w�肵���֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
	template<class ...RunFuncContainers>
	template<int ContainerNum>
	inline void ClassFuncProcessor<RunFuncContainers...>::setIsRunFunc(bool flag)
	{
		m_runFuncManager.setIsRunFunc<ContainerNum>(flag);
	}

	// �S�Ă̊֐����s�R���e�i�̊֐����s�t���O��ݒ肷��
	template<class ...RunFuncContainers>
	inline void ClassFuncProcessor<RunFuncContainers...>::setIsRunFuncAll(bool flag)
	{
		m_runFuncManager.setIsRunFuncAll(flag);
	}

	// �w�肵���֐����s�R���e�i�̃|�C���^���擾
	template<class ...RunFuncContainers>
	template<int ContainerNum, class RunFuncContainer>
	inline RunFuncContainer * ClassFuncProcessor<RunFuncContainers...>::getRunFuncContainerPtr()
	{
		return m_runFuncManager.getRunFuncContainerPtr<ContainerNum, RunFuncContainer>();
	}

	// �������s��
	template<class ...RunFuncContainers>
	inline void ClassFuncProcessor<RunFuncContainers...>::processing()
	{
		m_processingSimpleContainer.updateContainer();
		m_runFuncManager.updateContainer();
		m_runFuncManager.runFunc();
	}

	// ��n��
	template<class ...RunFuncContainers>
	inline void ClassFuncProcessor<RunFuncContainers...>::finalize()
	{
		m_processingSimpleContainer.deleteAll();
	}
}
#endif // !CLASS_FUNC_PROCESSOR_H_