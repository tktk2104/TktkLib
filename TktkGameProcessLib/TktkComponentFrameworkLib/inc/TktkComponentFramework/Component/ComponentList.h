#ifndef COMPONENT_LIST_H_
#define COMPONENT_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasOneArgFuncClass.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasTwoArgFuncClass.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasHandleMessageChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../ComponentFrameworkProcessor.h"

namespace tktk
{
	// �ʖ��[�Y
	template <class T>
	using SimpleCont = RunFuncSimpleContainer<T>;

	// �R���|�[�l���g���Ǘ����郊�X�g
	class ComponentList
	{
	public:

		ComponentList() = default;
		~ComponentList() {}

	public:

		// �V���ȃR���|�[�l���g��ǉ�
		template <class T>
		CfpPtr<T> add(bool isStatic, T* component);

		// �ŏ��Ɍ������e���v���[�g�p�����[�^�̃R���|�[�l���g���擾
		template <class T>
		CfpPtr<T> getComponent() const;

		// �S�Ẵe���v���[�g�p�����[�^�̃R���|�[�l���g���擾
		template <class T>
		std::forward_list<CfpPtr<T>> getComponentAll() const;

		void updateContainer();

		// �S�ẴR���|�[�l���g���폜����
		void destroyAll();

		// �S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void afterChangeParentAll(CfpPtr<GameObject> beforParent);
		
		// �S�ẴR���|�[�l���g�Ƀ��b�Z�[�W�𑗐M����
		void handleMessageAll(int eventMessageType, const SafetyVoidPtr& param);

		// �S�ẴR���|�[�l���g�̍폜���֐����Ă�
		void onDestroyAll();
		
		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void onCollisionEnterAll(CfpPtr<GameObject> other);
		
		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void onCollisionStayAll(CfpPtr<GameObject> other);
		
		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void onCollisionExitAll(CfpPtr<GameObject> other);

	private:

		std::forward_list<ProcessingClassPtr> m_componentList;

		// �e�v�f���ς�������ɌĂ΂��R���|�[�l���g�̃��X�g
		SimpleCont<HasOneArgFuncClass<
			has_afterChangeParent_checker<CfpPtr<GameObject>>,
			afterChangeParent_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_afterChangeParentableList;
		
		// ���b�Z�[�W��M�֐��������Ă���R���|�[�l���g�̃��X�g
		SimpleCont<HasTwoArgFuncClass<
			has_handleMessage_checker<int, const SafetyVoidPtr&>,
			handleMessage_runner<int, const SafetyVoidPtr&>,
			int, const SafetyVoidPtr&
		>> m_messageableList;

		// �폜���֐��������Ă���R���|�[�l���g�̃��X�g
		SimpleCont<HasAlwaysRunFuncClass<
				has_onDestroy_checker<>,
				onDestroy_runner<>
		>> m_hasOnDestroyClassContainer;
		
		// �Փˁi�J�n�E���E�I���j���̊֐��������Ă���R���|�[�l���g�̃��X�g
		SimpleCont<HasOneArgFuncClass<
			has_onCollisionEnter_checker<CfpPtr<GameObject>>,
			onCollisionEnter_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_hasCollisionEnterClassContainer;

		SimpleCont<HasOneArgFuncClass<
			has_onCollisionStay_checker<CfpPtr<GameObject>>,
			onCollisionStay_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_hasCollisionStayClassContainer;

		SimpleCont<HasOneArgFuncClass<
			has_onCollisionExit_checker<CfpPtr<GameObject>>,
			onCollisionExit_runner<CfpPtr<GameObject>>,
			CfpPtr<GameObject>
		>> m_hasCollisionExitClassContainer;
	};

	template<class T>
	inline CfpPtr<T> ComponentList::add(bool isStatic, T* component)
	{
		CfpPtr<T> componentPtr = ComponentFrameworkProcessor::addClass(isStatic, component);
		m_componentList.push_front(componentPtr.processingClassPtr());
		m_afterChangeParentableList.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_messageableList.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasOnDestroyClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasCollisionEnterClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasCollisionStayClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		m_hasCollisionExitClassContainer.checkAndAdd(isStatic, componentPtr.processingClassPtr(), component);
		return componentPtr;
	}

	template<class T>
	inline CfpPtr<T> ComponentList::getComponent() const
	{
		for (ProcessingClassPtr component : m_componentList)
		{
			if (component->canCast<T>()) return CfpPtr<T>(component);
		}
		return CfpPtr<T>();
	}

	template<class T>
	inline std::forward_list<CfpPtr<T>> ComponentList::getComponentAll() const
	{
		std::forward_list<CfpPtr<T>> resultList;

		auto curItr = std::begin(m_componentList);

		while (curItr != std::end(m_componentList))
		{
			curItr = std::find_if(
				++curItr,
				std::end(m_componentList),
				[](ProcessingClassPtr node) { return node->canCast<T>(); }
			);

			if (curItr == std::end(m_componentList)) break;

			resultList.push_front(CfpPtr<T>((*curItr)));
		}
		return resultList;
	}
}
#endif // !COMPONENT_LIST_H_