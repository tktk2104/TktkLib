#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/ProcessingClassPtr.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkMetaFunc/HasFuncCheck/CreatedStruct/HasSetGameObjectChecker.h>
#include "GameObjectTagList.h"
#include "../Component/ComponentList.h"
#include "../Component/ComponentUpdatePrioritySetter.h"

namespace tktk
{
	class ParentChildManager;

	// �Q�[���I�u�W�F�N�g�N���X
	class GameObject
	{
	public:

		GameObject(bool isStatic);

		virtual ~GameObject();

	// �e�q�֌W�֐�
	public:

		// �e�v�f���擾
		CfpPtr<GameObject> getParent() const;
		
		// �e�v�f��ݒ�
		void setParent(CfpPtr<GameObject> parent);
		
		// �q�v�f�̃��X�g���擾
		const std::forward_list<CfpPtr<GameObject>>& getChildren() const;
		
		// �q�v�f�����X�g�ɒǉ�����
		void addChild(CfpPtr<GameObject> child);
		
		// �w�肵���q�v�f�����X�g����폜����
		void removeChild(CfpPtr<GameObject> child);
		
		// �S�Ă̎q�v�f�Ƀ��b�Z�[�W�𑗐M����
		void sendMessage(int eventMessageType, const SafetyVoidPtr& param = SafetyVoidPtr());
		
	// �R���|�[�l���g�֘A�֐�
	public:

		// �ŏ��Ɍ������e���v���[�g�p�����[�^�̃R���|�[�l���g���擾
		template <class T>
		CfpPtr<T> getComponent() const;
		
		// �S�Ẵe���v���[�g�p�����[�^�̃R���|�[�l���g���擾
		template <class T>
		std::forward_list<CfpPtr<T>> getComponentAll() const;
		
		// �R���|�[�l���g��ǉ�����
		template <class T>
		CfpPtr<T> addComponent(T* addClass);

		// �R���|�[�l���g�𐶐����Ēǉ�����
		template <class T, class... Args>
		CfpPtr<T> createComponent(const Args&... constructorValue);
		
		// �S�ẴR���|�[�l���g�̐e�v�f���ς�������֐����Ă�
		void runAfterChangeParentAll(CfpPtr<GameObject> beforParent);
		
		// �S�ẴR���|�[�l���g�̏ՓˊJ�n�֐����Ă�
		void runOnCollisionEnterAll(CfpPtr<GameObject> other);
		
		// �S�ẴR���|�[�l���g�̏Փ˒��֐����Ă�
		void runOnCollisionStayAll(CfpPtr<GameObject> other);
		
		// �S�ẴR���|�[�l���g�̏ՓˏI���֐����Ă�
		void runOnCollisionExitAll(CfpPtr<GameObject> other);

	// ���̑��p�����[�^�ݒ�/�擾�֐�
	public:

		// �����̃^�O�������Ă��邩���肷��
		bool containTag(int tag) const;

		// ���g���ÓI�ȃN���X�����擾
		bool isStatic() const;

		// �폜�t���O���擾
		bool isDestroy() const;

		// �A�N�e�B�u�t���O���擾
		bool isActive() const;

		// ���g�Ƀ^�O��ǉ�
		void addTag(int tag);

		// ���g�̃^�O���폜
		void removeTag(int tag);

		// ���g���폜����
		void destroy();

		// �A�N�e�B�u�t���O��ݒ肷��
		void setActive(bool isActive);

		// ���g��ProcessPtr��ݒ肷��
		void setGameObject(CfpPtr<GameObject> selfPtr);

	// �|�����[�t�B�Y���Ȋ֐�
	public:

		void awake();
		void frameBegin();
		void handleMessage(int eventMessageType, const SafetyVoidPtr& param);

	private:

		bool m_isStatic{ false };
		bool m_isDestroy{ false };
		bool m_isActive{ true };
		bool m_nextFrameIsActive{ true };

		GameObjectTagList m_tagList;
		ComponentList m_componentList;
		CfpPtr<GameObject> m_selfPtr;
		CfpPtr<ParentChildManager> m_pcManager;
	};

	template<class T>
	inline CfpPtr<T> GameObject::getComponent() const
	{
		return m_componentList.getComponent<T>();
	}
	
	template<class T>
	inline std::forward_list<CfpPtr<T>> GameObject::getComponentAll() const
	{
		return m_componentList.getComponentAll<T>();
	}
	
	template<class T>
	inline CfpPtr<T> GameObject::addComponent(T* addClass)
	{
		setGameObject_runner<CfpPtr<GameObject>>::checkAndRun(addClass, m_selfPtr);

		ComponentUpdatePrioritySetter::setUpdatePriority(addClass);

		return m_componentList.add<T>(m_isStatic, addClass);
	}

	template<class T, class ...Args>
	inline CfpPtr<T> GameObject::createComponent(const Args & ...constructorValue)
	{
		return addComponent(new T(constructorValue...));
	}
}
#endif // !GAME_OBJECT_H_