#ifndef COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_
#define COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_

#include <memory>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasAfterChangeParentChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionEnterChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionStayChecker.h>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasOnCollisionExitChecker.h>
#include "../../GameObject/GameObjectPtr.h"
#include "../ComponentBasePtr.h"

namespace tktk
{
	// �Q�[���I�u�W�F�N�g���g�p����R���|�[�l���g�̊֐������s����N���X
	class ComponentGameObjectFuncRunner
	{
	public:

		template <class ComponentType>
		ComponentGameObjectFuncRunner(const std::weak_ptr<ComponentType>& componentPtr);

	public:

		// �^�����B�������R���|�[�l���g�|�C���^���擾����
		const ComponentBasePtr& getComponentBasePtr() const;

		// �R���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParent(const GameObjectPtr& beforParent);

		// �R���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnter(const GameObjectPtr& other);

		// �R���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStay(const GameObjectPtr& other);

		// �R���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExit(const GameObjectPtr& other);

		// �R���|�[�l���g�̎��S�t���O��
		bool isDead() const;

		// �R���|�[�l���g���E��
		void destroy();

	private:

		struct VTable
		{
			void(*runAfterChangeParent)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionEnter)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionStay)	(const ComponentBasePtr&, const GameObjectPtr&);
			void(*runOnCollisionExit)	(const ComponentBasePtr&, const GameObjectPtr&);
		};

		template <class ComponentType>
		struct VTableInitializer
		{
			// �e�v�f���ς�������֐��������Ă�����Ă�
			static void runAfterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent);

			// �ՓˊJ�n�֐��������Ă�����Ă�
			static void runOnCollisionEnter	(const ComponentBasePtr& self, const GameObjectPtr& other);

			// �Փ˒��֐��������Ă�����Ă�
			static void runOnCollisionStay	(const ComponentBasePtr& self, const GameObjectPtr& other);

			// �ՓˏI���֐��������Ă�����Ă�
			static void runOnCollisionExit	(const ComponentBasePtr& self, const GameObjectPtr& other);

			static VTable m_vtable;
		};

	private:

		VTable* m_vtablePtr;
		ComponentBasePtr	m_selfPtr;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType>
	inline ComponentGameObjectFuncRunner::ComponentGameObjectFuncRunner(const std::weak_ptr<ComponentType>& componentPtr)
		: m_vtablePtr(&VTableInitializer<ComponentType>::m_vtable)
		, m_selfPtr(componentPtr)
	{
	}

	template<class ComponentType>
	typename ComponentGameObjectFuncRunner::VTable ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::m_vtable =
	{
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runAfterChangeParent,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay,
		&ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit,
	};

	// �e�v�f���ς�������֐��������Ă�����Ă�
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runAfterChangeParent(const ComponentBasePtr& self, const GameObjectPtr& beforParent)
	{
		afterChangeParent_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), beforParent);
	}

	// �ՓˊJ�n�֐��������Ă�����Ă�
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionEnter(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionEnter_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	// �Փ˒��֐��������Ă�����Ă�
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionStay(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionStay_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}

	// �ՓˏI���֐��������Ă�����Ă�
	template<class ComponentType>
	inline void ComponentGameObjectFuncRunner::VTableInitializer<ComponentType>::runOnCollisionExit(const ComponentBasePtr& self, const GameObjectPtr& other)
	{
		onCollisionExit_runner<void, const GameObjectPtr&>::checkAndRun(self.castPtr<ComponentType>(), other);
	}
}
#endif // !COMPONENT_GAME_OBJECT_FUNC_RUNNER_H_