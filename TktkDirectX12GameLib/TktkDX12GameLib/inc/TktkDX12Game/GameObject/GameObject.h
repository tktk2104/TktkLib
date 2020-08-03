#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <memory>
#include <utility>
#include <unordered_map>
#include "GameObjectTagList.h"
#include "../Component/ComponentGameObjectFunc/GameObjectComponentList.h"
#include "../_MainManager/DX12GameManager.h"
#include "../Component/ComponentPtr.h"
#include "../Component/DefaultComponents/StateMachine/StateMachineList.h"

namespace tktk
{
	class ParentChildManager;
	class CurStateTypeList;

	// �Q�[���I�u�W�F�N�g�N���X
	class GameObject
		: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		~GameObject();

	public:

		void update();

	public: /* �t���O�Ǘ��֐� */

		// �A�N�e�B�u�t���O��ݒ肷��
		void setActive(bool activeFlag);

		// �I�u�W�F�N�g���폜����
		void destroy();

		// �A�N�e�B�u�t���O���擾����
		bool isActive() const;

		// ���S�t���O���擾����
		bool isDead() const;

	public: /* �^�O�Ǘ��֐� */

		// ���g�̃^�O��ǉ�����
		void addGameObjectTag(int tag);

		// �����̃^�O���폜����
		void removeGameobjectTag(int tag);

		// �����̃^�O�������Ă��邩�̔�����s��
		bool containGameobjectTag(int tag) const;

	public: /* �R���|�[�l���g�擾���� */

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(Args&&... args);

		// �e���v���[�g�����̌^�̃R���|�[�l���g�������Ă�����擾���A�����Ă��Ȃ�������nullptr��Ԃ�
		// �����������^�̃R���|�[�l���g���������Ă����ꍇ�A�ŏ��Ɍ������P���擾����
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const;

		// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const;

	public: /* �R���|�[�l���g�֐��Ăяo������ */

		// �S�Ẵ��b�Z�[�W�擾�֐����Ă�
		void runHandleMessageAll(unsigned int messageId, const MessageAttachment& value);

		// �S�Ă̎q���̑S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParentAll(const GameObjectPtr& beforParent);

		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnterAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStayAll(const GameObjectPtr& other);

		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExitAll(const GameObjectPtr& other);

	public: /* �e�q�֌W���� */

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

		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(unsigned int messageId, const MessageAttachment& value = {});

	public: /* �X�e�[�g�}�V���֌W���� */

		// �X�e�[�g�̎�ނ������Ƃ��ēn���A�X�e�[�g�}�V���̑���ɕK�v�ȃR���|�[�l���g����������
		void setupStateMachine(const StateMachineListInitParam& initParam);

		/**************************************************
		�ysetupStateMachine()�̈����̍쐬��z

		StateMachineListInitParam stateList = 
		{
			{
				MOVE_STATE, 
				{
					{
						WALK_STATE,
						{
							{ BEGIN_MOVE_STATE },	// �gRUN_STATE�h�́gBEGIN_MOVE_STATE�h�Ɠ���̃X�e�[�g�ŁgWALK_STATE�h��Ԃ̎���isActive = true�ɂȂ�
							{ MOVING_STATE },
							{ END_MOVE_STATE }
						}
					},
					{
						RUN_STATE,
						{
							{ BEGIN_MOVE_STATE },	// �gRUN_STATE�h�́gBEGIN_MOVE_STATE�h�Ɠ���̃X�e�[�g�ŁgRUN_STATE�h��Ԃ̎���isActive = true�ɂȂ�
							{ MOVING_STATE },
							{ END_MOVE_STATE }
						}
					}

				}
			},
			{
				JUMP_STATE,
				{
					{ BEGIN_JUMP_STATE },
					{ JUMPING_STATE },
					{ END_JUMP_STATE },
				}
			},
			{ DEAD_STATE }
		}
		**************************************************/

		// �X�e�[�g��ǉ�����
		void addState(int stateType);

		// �X�e�[�g���폜����
		void removeState(int stateType);

		// �S�ẴX�e�[�g���폜����
		void clearState();

		// �����̃X�e�[�g�������Ă��邩�H
		bool contain(int stateType);

		// int�^�̔z��ŃX�e�[�g���w�肵�A�q�v�f��ǉ�����
		// ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		void addChild(const std::vector<int>& targetState, const GameObjectPtr& child);

		// int�^�̔z��ŃX�e�[�g���w�肵�A�e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
		//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
		template <class ComponentType, class... Args>
		ComponentPtr<ComponentType> createComponent(const std::vector<int>& targetState, Args&&... args);

	private:

		void createComponentImpl(const std::vector<int>& targetState, const ComponentBasePtr& componentPtr);

	private:

		bool												m_isActive				{ true };
		bool												m_nextFrameActive		{ true };
		bool												m_isDead				{ false };
		GameObjectTagList									m_tagList				{};
		GameObjectComponentList								m_componentList			{};
		ComponentPtr<ParentChildManager>					m_parentChildManager	{};
		
		// �X�e�[�g�}�V���֘A�̃N���X�́usetupStateMachine()�v���ĂԂ܂Ŏ��Ԃ�����Ȃ��̂Ń|�C���^�ɂĊǗ�
		ComponentPtr<CurStateTypeList>						m_stateTypeList			{};
		std::unique_ptr<StateMachineList>					m_stateMachineList		{};
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
	template<class ComponentType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(Args&& ...args)
	{
		auto createdComponent = DX12GameManager::createComponent<ComponentType>(std::forward<Args>(args)...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		return m_componentList.add<ComponentType>(createdComponent);
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g�������Ă�����擾���A�����Ă��Ȃ�������nullptr��Ԃ�
	// �����������^�̃R���|�[�l���g���������Ă����ꍇ�A�ŏ��Ɍ������P���擾����
	template<class ComponentType>
	inline ComponentPtr<ComponentType> GameObject::getComponent() const
	{
		return m_componentList.find<ComponentType>();
	}

	// �e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
	template<class ComponentType>
	inline std::forward_list<ComponentPtr<ComponentType>> GameObject::getComponents() const
	{
		return m_componentList.findAll<ComponentType>();
	}

	// int�^�̔z��ŃX�e�[�g���w�肵�A�e���v���[�g�����̌^�̃R���|�[�l���g�������̒l���g���č��
	//  ���u{ MOVE_STATE, WALK_STATE, BEGIN_MOVE_STATE }�v�Łu�gMOVE_STATE�h���́gWALK_STATE�h���́gBEGIN_MOVE_STATE�h�ɒǉ��v�ƂȂ�
	template<class ComponentType, class ...Args>
	inline ComponentPtr<ComponentType> GameObject::createComponent(const std::vector<int>& targetState, Args&& ...args)
	{
		auto createdComponent = DX12GameManager::createComponent<ComponentType>(std::forward<Args>(args)...);
		createdComponent.lock()->setUser(GameObjectPtr(weak_from_this()));
		createComponentImpl(targetState, ComponentBasePtr(createdComponent));
		return m_componentList.add<ComponentType>(createdComponent);
	}
}
#endif // !GAME_OBJECT_H_