#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

#include <forward_list>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "../GameObject/GameObject.h"

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

	void afterChangeParent(tktk::CfpPtr<GameObject> beforParent);	// �q�v�f���ύX���ꂽ��ɌĂ΂��
	void onCollisionEnter(tktk::CfpPtr<GameObject> other);			// �ՓˊJ�n���ɌĂ΂��
	void onCollisionStay(tktk::CfpPtr<GameObject> other);			// �Փ˒��ɌĂ΂��
	void onCollisionExit(tktk::CfpPtr<GameObject> other);			// �ՓˏI�����ɌĂ΂��

	void handleMessage(int eventMessageType, const tktk::SafetyVoidPtr& param);	// ���b�Z�[�W����M�����Ƃ��ɌĂ΂��
	*/
	class ComponentBase
	{
	public:

		ComponentBase(
			float drawPriority = 0.0f,
			int collisionGroupType = 0
		);

		virtual ~ComponentBase();

	public:

		void frameBegin();

		// �A�N�e�B�u�t���O�̎擾
		bool isActive() const;

		// ���̃t���[���ŃA�N�e�B�u�t���O��ݒ�
		void setActive(bool isActive);

		// �X�V�D��x���擾
		float getUpdatePriority() const;

		// �`�悷�郌�C���[���擾
		float getDrawPriority() const;

		// �Փ˔���̃O���[�v���擾
		int getCollisionGroup() const;

		// GameObject���擾
		CfpPtr<GameObject> getGameObject() const;

		// ���g�̏����҂ƂȂ�GameObject���Đݒ�i�}�l�[�W���[�p�֐��j
		void setGameObject(CfpPtr<GameObject> user);

		// ���g�̍X�V�D��x��ݒ�i�}�l�[�W���[�p�֐��j
		void setUpdatePriority(float updatePriority);

	public:

		// �ŏ��Ɍ������e���v���[�g�p�����[�^�̃R���|�[�l���g���擾
		template <class T>
		CfpPtr<T> getComponent() const;

		// �S�Ẵe���v���[�g�p�����[�^�̃R���|�[�l���g���擾
		template <class T>
		std::forward_list<CfpPtr<T>> getComponentAll() const;

	private:

		bool m_isActive{ true };
		bool m_nextFrameIsActive{ true };

		CfpPtr<GameObject> m_user;

		float m_updatePriority{ 0.0f };
		float m_drawPriority{ 0.0f };
		int m_collisionGroupType{ 0 };
	};

	template<class T>
	inline CfpPtr<T> ComponentBase::getComponent() const
	{
		return getGameObject()->getComponent<T>();
	}

	template<class T>
	inline std::forward_list<CfpPtr<T>> ComponentBase::getComponentAll() const
	{
		return getGameObject()->getComponentAll<T>();
	}
}
#endif // !COMPONENT_BASE_H_