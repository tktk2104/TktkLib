#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include "ComponentPtr.h"
#include "../GameObject/GameObject.h"
#include "../GameObject/GameObjectPtr.h"

namespace tktk
{
	/*
	�R���|�[�l���g�̊��N���X
	<PolymorphismFunc>

	void awake();				// ��������i�R���X�g���N�^���Ă΂ꂽ��j�ɌĂ΂��
	void start();				// �����������̃t���[���̍ŏ��ɌĂ΂��
	void onEnable();			// ��A�N�e�B�u����A�N�e�B�u��ԂɈڍs�������ɌĂ΂��
	void onDisable();			// �A�N�e�B�u�����A�N�e�B�u��ԂɈڍs�������ɌĂ΂��
	void onDestroy();			// �폜�t���O���������u�ԁi�f�X�g���N�^���Ă΂��O�j�ɌĂ΂��
	void update();				// ���t���[���Ă΂��

	void afterChangeParent	(const tktk::GameObjectPtr& beforParent);	// �q�v�f���ύX���ꂽ��ɌĂ΂��
	void onCollisionEnter	(const tktk::GameObjectPtr& other);			// �ՓˊJ�n���ɌĂ΂��
	void onCollisionStay	(const tktk::GameObjectPtr& other);			// �Փ˒��ɌĂ΂��
	void onCollisionExit	(const tktk::GameObjectPtr& other);			// �ՓˏI�����ɌĂ΂��
	*/
	class ComponentBase
	{
	public:

		ComponentBase(float drawPriority = 0.0f, const int collisionGroup = 0);
		virtual ~ComponentBase();

	public:

		float getDrawPriority() const;

		int getCollisionGroup() const;

		bool activeChangeCheck();

		void setActive(bool activeFlag);

		void destroy();

		bool isActive() const;

		bool isDead() const;

	public:

		const GameObjectPtr& getGameObject() const;

		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

	public:

		void setUser(const GameObjectPtr& user);

	private:

		const float		m_drawPriority;
		const int		m_collisionGroup;
		bool			m_isActive			{ true };
		bool			m_nextFrameActive	{ true };
		bool			m_isDead			{ false };
		GameObjectPtr	m_user				{ };
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType>
	inline ComponentPtr<ComponentType> ComponentBase::getComponent() const
	{
		if (m_user.expired()) return ComponentPtr<ComponentType>();
		return m_user->getComponent<ComponentType>();
	}

	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> ComponentBase::getComponents() const
	{
		if (m_user.expired()) return std::forward_list<ComponentPtr<ComponentType>>();
		return m_user->getComponents<ComponentType>();
	}
}
#endif // !COMPONENT_BASE_H_