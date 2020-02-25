#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetActiveChecker.h>
#include <TktkClassFuncProcessor/RunFuncClass/RunFuncSimpleContainer.h>
#include <TktkClassFuncProcessor/RunFuncClass/HasFuncClass/HasAlwaysRunFuncClass.h>
#include <TktkComponentFramework/GameObject/GameObject.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include "CurStateTypeList.h"
#include "StateMachineRegistrationList.h"

namespace tktk
{
	// �X�[�p�[���ʖ��[�Y
	template <class NodeType, template<class JudgePtrType> class HasFuncChecker>
	using SimpleCont = RunFuncSimpleContainer<NodeType, HasFuncChecker>;

	template <class JudgePtrType>
	using HasSetActiveChecker = has_setActive_checker<JudgePtrType, void, bool>;

	// �T�u���ʖ��[�Y
	using SetActiveCont = SimpleCont<HasAlwaysRunFuncClass<setActive_runner, void, bool>, HasSetActiveChecker>;

	// �X�e�[�g�}�V�[���R���|�[�l���g
	// �y�O��R���|�[�l���g�FCurStateTypeList�z
	class StateMachine
		: public ComponentBase
	{
	public:

		// StateMachinePtr�𐶐�����
		static CfpPtr<StateMachine> create(
			CfpPtr<GameObject> user,	// ���̃X�e�[�g������GameObject
			int stateType				// ���̃X�e�[�g�}�V���̃X�e�[�g�^�C�v
		);

		// StateMachinePtr�𐶐�����i����q�X�e�[�g�j
		static CfpPtr<StateMachine> create(
			CfpPtr<StateMachine> parentState,	// ���̃X�e�[�g�����X�e�[�g
			int stateType					// ���̃X�e�[�g�}�V���̃X�e�[�g�^�C�v
		);

	public:

		StateMachine(
			int stateType	// ���̃X�e�[�g�}�V���̃X�e�[�g�^�C�v
		);

	public:

		// <PolymorphismFunc>
		void onDisable();
		void update();

	public:

		// ���̃X�e�[�g�Ɏq�v�f��ǉ�����
		void addChild(bool isStatic, CfpPtr<GameObject> child);

		// ���̃X�e�[�g�ɃR���|�[�l���g��ǉ�����
		template <class T>
		CfpPtr<T> addComponent(T* component);

		// �����̃R���|�[�l���g���X�e�[�g�}�V���ɓo�^����Ă��邩�𔻒肷��
		template <class T>
		bool isRegistrationStateMachine(CfpPtr<T> component);

	private:

		// ���g�̃X�e�[�g�̎��
		int m_selfStateType;

		// ���g�̌��݂̃X�e�[�g�̎�ނ̃R���|�[�l���g
		CfpPtr<CurStateTypeList> m_curStateTypeList;

		// �A�N�e�B�u��Ԃ�؂�ւ��邽�߂̃R���e�i�̃��b�p�[
		SetActiveCont m_hasSetActiveClassList;

		// ���̃X�e�[�g�}�V�[���ɂǂ̃R���|�[�l���g���o�^����Ă��邩���Ǘ����郊�X�g
		StateMachineRegistrationList m_stateMachineRegistrationList;
	};

	// ���̃X�e�[�g�ɃR���|�[�l���g��ǉ�����
	template<class T>
	inline CfpPtr<T> StateMachine::addComponent(T* component)
	{
		auto cfpPtr = getGameObject()->addComponent(component);
		setActive_runner<bool>::checkAndRun(component, false);
		m_hasSetActiveClassList.checkAndAdd<T>(getGameObject()->isStatic(), cfpPtr.processingClassPtr(), component);
		m_stateMachineRegistrationList.addNode(cfpPtr.processingClassPtr());
		return cfpPtr;
	}

	// �����̃R���|�[�l���g���X�e�[�g�}�V���ɓo�^����Ă��邩�𔻒肷��
	template<class T>
	inline bool StateMachine::isRegistrationStateMachine(CfpPtr<T> component)
	{
		return m_stateMachineRegistrationList.contain(component);
	}
}
#endif // !STATE_MACHINE_H_