#ifndef COMPONENT_LIST_H_
#define COMPONENT_LIST_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasHandleMessageChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnDestroyChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../ComponentFrameworkProcessor.h"

namespace tktk
{
	// �X�[�p�[���ʖ��[�Y
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	using SimpleCont = RunFuncSimpleContainer<NodeType, HasFuncChecker>;

	template <class JudgePtrType>
	using hasAfterChangeParentChecker	= has_afterChangeParent_checker<JudgePtrType, void, CfpPtr<GameObject>>;
	template <class JudgePtrType>
	using hasHandleMessageChecker		= has_handleMessage_checker<JudgePtrType, void, int, const SafetyVoidPtr&>;
	template <class JudgePtrType>
	using hasOnDestroy					= has_onDestroy_checker<JudgePtrType, void>;
	template <class JudgePtrType>
	using hasOnCollisionEnter			= has_onCollisionEnter_checker<JudgePtrType, void, CfpPtr<GameObject>>;
	template <class JudgePtrType>
	using hasOnCollisionStay			= has_onCollisionStay_checker<JudgePtrType, void, CfpPtr<GameObject>>;
	template <class JudgePtrType>
	using hasOnCollisionExit			= has_onCollisionExit_checker<JudgePtrType, void, CfpPtr<GameObject>>;

	// �T�u���ʖ��[�Y
	using AfterChangeParentCont = SimpleCont<HasFuncClass<afterChangeParent_runner, void, CfpPtr<GameObject>>, hasAfterChangeParentChecker>;
	using HandleMessageCont		= SimpleCont<HasFuncClass<handleMessage_runner, void, int, const SafetyVoidPtr&>, hasHandleMessageChecker>;
	using OnDestroyCont			= SimpleCont<HasFuncClass<onDestroy_runner, void>, hasOnDestroy>;
	using OnCollisionEnterCont	= SimpleCont<HasFuncClass<onCollisionEnter_runner, void, CfpPtr<GameObject>>, hasOnCollisionEnter>;
	using OnCollisionStayCont	= SimpleCont<HasFuncClass<onCollisionStay_runner, void, CfpPtr<GameObject>>, hasOnCollisionStay>;
	using OnCollisionExitCont	= SimpleCont<HasFuncClass<onCollisionExit_runner, void, CfpPtr<GameObject>>, hasOnCollisionExit>;

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
		AfterChangeParentCont m_afterChangeParentableList;
		
		// ���b�Z�[�W��M�֐��������Ă���R���|�[�l���g�̃��X�g
		HandleMessageCont m_messageableList;

		// �폜���֐��������Ă���R���|�[�l���g�̃��X�g
		OnDestroyCont m_hasOnDestroyClassContainer;
		
		// �Փˁi�J�n�E���E�I���j���̊֐��������Ă���R���|�[�l���g�̃��X�g
		OnCollisionEnterCont m_hasCollisionEnterClassContainer;
		OnCollisionStayCont m_hasCollisionStayClassContainer;
		OnCollisionExitCont m_hasCollisionExitClassContainer;
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