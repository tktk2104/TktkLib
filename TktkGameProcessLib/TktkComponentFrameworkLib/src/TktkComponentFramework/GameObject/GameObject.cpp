#include "TktkComponentFramework/GameObject/GameObject.h"

#include "TktkComponentFramework/GameObject/GameObjectManager.h"
#include "TktkComponentFramework/Component/CommonComponent/ParentChildManager/ParentChildManager.h"

namespace tktk
{
	GameObject::GameObject(bool isStatic)
		: m_isStatic(isStatic)
	{
	}

	GameObject::~GameObject()
	{
		m_pcManager->removeChildren();
		m_componentList.destroyAll();
	}

	CfpPtr<GameObject> GameObject::getParent() const
	{
		return m_pcManager->getParent();
	}
	
	void GameObject::setParent(CfpPtr<GameObject> parent)
	{
		// �e�v�f���Đݒ肷��O�̐e�v�f���擾
		CfpPtr<GameObject> befoerSelfParent = getParent();
	
		// �ݒ肷��e�����݂��Ȃ����
		if (parent.isNull())
		{
			// �e�v�f���Đݒ肷��O�̐e�v�f�����݂����炻�̐e�̂̎q�v�f���玩�g���O��
			if (!befoerSelfParent.isNull())
			{
				befoerSelfParent->removeChild(m_selfPtr);
			}
			return;
		}
		// �ݒ肷��e�̎q�v�f�Ɏ��g��ǉ�����
		parent->addChild(m_selfPtr);
	}
	
	const std::forward_list<CfpPtr<GameObject>> & GameObject::getChildren() const
	{
		return m_pcManager->getChildren();
	}
	
	void GameObject::addChild(CfpPtr<GameObject> child)
	{
		// �ǉ�����O�̎q�v�f�̐e�v�f���擾
		CfpPtr<GameObject> beforeChildParent = child->getParent();
	
		// ����������GameObject�����g�̎q�v�f�������牽�����Ȃ�
		if (beforeChildParent == m_selfPtr) return;
	
		// ���ɐe�v�f�������Ă�����
		if (!beforeChildParent.isNull())
		{
			// ���̐e�v�f����ǉ�����O�̎q�v�f���폜����
			beforeChildParent->m_pcManager->removeChild(child);
		}
		// ���g�̐e�q�֌W�Ǘ��R���|�[�l���g�ɐV���Ȏq�v�f��ǉ�����
		m_pcManager->addChild(child);
	
		// �ǉ�����q���̐e�q�֌W�Ǘ��R���|�[�l���g�̐e�v�f���X�V����
		child->m_pcManager->setParent(m_selfPtr);
	
		// �ǉ�����q���̐e�ύX���֐����Ă�
		child->m_componentList.afterChangeParentAll(beforeChildParent);
	}
	
	void GameObject::removeChild(CfpPtr<GameObject> child)
	{
		// �ǉ�����O�̎q�v�f�̐e�v�f���擾
		CfpPtr<GameObject> beforeChildParent = child->getParent();
	
		// �e�v�f�������Ă��Ȃ� or ���g�ł͂Ȃ��e�������Ă����� �������Ȃ�
		if (beforeChildParent.isNull() || beforeChildParent != m_selfPtr) return;
	
		// �폜�������q�v�f�̐e�q�֌W�Ǘ��R���|�[�l���g�̐e�v�f���X�V����
		child->m_pcManager->setParent(CfpPtr<GameObject>());
	
		// ���g�̐e�q�֌W�Ǘ��R���|�[�l���g����폜�������q�v�f���폜����
		m_pcManager->removeChild(child);
	
		// �ǉ�����q���̐e�ύX���֐����Ă�
		child->m_componentList.afterChangeParentAll(m_selfPtr);
	}
	
	void GameObject::sendMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		handleMessage(eventMessageType, param);
		m_pcManager->sendMessage(eventMessageType, param);
	}
	
	void GameObject::runAfterChangeParentAll(CfpPtr<GameObject> beforParent)
	{
		m_componentList.afterChangeParentAll(beforParent);
	}
	
	void GameObject::runOnCollisionEnterAll(CfpPtr<GameObject> other)
	{
		m_componentList.onCollisionEnterAll(other);
	}
	
	void GameObject::runOnCollisionStayAll(CfpPtr<GameObject> other)
	{
		m_componentList.onCollisionStayAll(other);
	}
	
	void GameObject::runOnCollisionExitAll(CfpPtr<GameObject> other)
	{
		m_componentList.onCollisionExitAll(other);
	}

	bool GameObject::containTag(int tag) const
	{
		return m_tagList.contain(tag);
	}

	bool GameObject::isStatic() const
	{
		return m_isStatic;
	}

	bool GameObject::isDestroy() const
	{
		return m_isDestroy;
	}

	bool GameObject::isActive() const
	{
		if (!m_isActive) return false;
		
		if (getParent().isNull()) return true;
		
		return getParent()->isActive();
	}

	void GameObject::addTag(int tag)
	{
		m_tagList.addTag(tag);
	}

	void GameObject::removeTag(int tag)
	{
		m_tagList.removeTag(tag);
	}

	void GameObject::destroy()
	{
		if (m_isDestroy) return;

		m_componentList.onDestroyAll();

		m_isDestroy = true;
	}

	void GameObject::setActive(bool isActive)
	{
		m_nextFrameIsActive = isActive;
	}

	void GameObject::setGameObject(CfpPtr<GameObject> selfPtr)
	{
		m_selfPtr = selfPtr;
	}

	void GameObject::awake()
	{
		m_pcManager = createComponent<ParentChildManager>();
	}

	void GameObject::frameBegin()
	{
		m_isActive = m_nextFrameIsActive;
		m_componentList.updateContainer();
	}

	void GameObject::handleMessage(int eventMessageType, const SafetyVoidPtr & param)
	{
		m_componentList.handleMessageAll(eventMessageType, param);
	}
}