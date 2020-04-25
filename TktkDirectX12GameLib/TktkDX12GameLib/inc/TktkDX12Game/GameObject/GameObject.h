#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <memory>
#include "GameObjectTagList.h"
#include "../Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "../_MainManager/DX12GameManager.h"
#include "../Component/ComponentPtr.h"

namespace tktk
{
	class ParentChildManager;

	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

	public:

		void setActive(bool activeFlag);

		void destroy();

		bool isActive() const;

		bool isDead() const;

	public:

		void addGameObjectTag(int tag);

		void removeGameobjectTag(int tag);

		bool containGameobjectTag(int tag) const;

	public:

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args... args);

		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

		// �S�Ă̎q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExitAll(const GameObjectPtr& other);

	public:

		// �e�v�f���擾
		const GameObjectPtr& getParent() const;

		// �e�v�f��ݒ�
		void setParent(const GameObjectPtr& parent);

		// �q�v�f�̃��X�g���擾
		const std::forward_list<GameObjectPtr>& getChildren() const;

		// �q�v�f�����X�g�ɒǉ�����
		void addChild(const GameObjectPtr& child);

		// �w�肵���q�v�f�����X�g����폜����
		void removeChild(const GameObjectPtr& child);

		//// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		//void sendMessage(int eventMessageType, const SafetyVoidPtr& param = SafetyVoidPtr());

	private:

		bool								m_isActive				{ true };
		bool								m_nextFrameActive		{ true };
		bool								m_isDead				{ false };
		GameObjectTagList					m_tagList				{};
		GameObjectComponentList				m_componentList			{};
		ComponentPtr<ParentChildManager>	m_parentChildManager	{};
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class ComponentType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(Args ...args)
	{
		auto createdComponent = DX12GameManager::createComponent<ComponentType>(args...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		return m_componentList.add<ComponentType>(createdComponent);
	}

	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObject::getComponent() const
	{
		return m_componentList.find<ComponentType>();
	}

	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObject::getComponents() const
	{
		return m_componentList.findAll<ComponentType>();
	}
}
#endif // !GAME_OBJECT_H_