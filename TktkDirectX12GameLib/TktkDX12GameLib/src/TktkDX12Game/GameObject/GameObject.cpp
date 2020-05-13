#include "TktkDX12Game/GameObject/GameObject.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include "TktkDX12Game/Component/DefaultComponents/ParentChildManager/ParentChildManager.h"

namespace tktk
{
	GameObject::GameObject()
	{
		m_parentChildManager = createComponent<ParentChildManager>();
	}

	GameObject::~GameObject()
	{
		if (!m_parentChildManager.expired())
		{
			m_parentChildManager->destroyChildren();
		}
		m_componentList.destroyAll();
	}

	void GameObject::update()
	{
		m_componentList.removeDeadComponent();

		m_isActive = m_nextFrameActive;
	}

	void GameObject::setActive(bool activeFlag)
	{
		m_nextFrameActive = activeFlag;
	}

	void GameObject::destroy()
	{
		m_isDead = true;
	}

	bool GameObject::isActive() const
	{
		if (!m_isActive) return false;

		if (getParent().expired()) return true;

		return getParent()->isActive();
	}

	bool GameObject::isDead() const
	{
		return m_isDead;
	}

	void GameObject::addGameObjectTag(int tag)
	{
		m_tagList.addTag(tag);
	}

	void GameObject::removeGameobjectTag(int tag)
	{
		m_tagList.removeTag(tag);
	}

	bool GameObject::containGameobjectTag(int tag) const
	{
		return m_tagList.contain(tag);
	}

	void GameObject::runAfterChangeParentAll(const GameObjectPtr& beforParent)
	{
		m_componentList.runAfterChangeParentAll(beforParent);
	}

	void GameObject::runOnCollisionEnterAll(const GameObjectPtr& other)
	{
	}

	void GameObject::runOnCollisionStayAll(const GameObjectPtr& other)
	{
	}

	void GameObject::runOnCollisionExitAll(const GameObjectPtr& other)
	{
	}

	const GameObjectPtr& GameObject::getParent() const
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		return m_parentChildManager->getParent();
	}

	void GameObject::setParent(const GameObjectPtr& parent)
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		m_parentChildManager->setParent(parent);
	}

	const std::forward_list<GameObjectPtr>& GameObject::getChildren() const
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		return m_parentChildManager->getChildren();
	}

	void GameObject::addChild(const GameObjectPtr& child)
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		// �ǉ�����O�̎q�v�f�̐e�v�f���擾
		const GameObjectPtr& beforeChildParent = child->getParent();

		// ����������GameObject�����g�̎q�v�f�������牽�����Ȃ�
		if (beforeChildParent.isSame(GameObjectPtr(weak_from_this()))) return;

		// ���ɐe�v�f�������Ă�����
		if (!beforeChildParent.expired())
		{
			// ���̐e�v�f����ǉ�����O�̎q�v�f���폜����
			beforeChildParent->m_parentChildManager->removeChild(child);
		}
		// ���g�̐e�q�֌W�Ǘ��R���|�[�l���g�ɐV���Ȏq�v�f��ǉ�����
		m_parentChildManager->addChild(child);

		// �ǉ�����q���̐e�q�֌W�Ǘ��R���|�[�l���g�̐e�v�f���X�V����
		child->m_parentChildManager->setParent(GameObjectPtr(weak_from_this()));

		// �ǉ�����q���̐e�ύX���֐����Ă�
		child->m_componentList.runAfterChangeParentAll(beforeChildParent);
	}

	void GameObject::removeChild(const GameObjectPtr& child)
	{
#ifdef _DEBUG
		if (m_parentChildManager.expired()) throw std::runtime_error("not found ParentChildManager");
#endif
		// �ǉ�����O�̎q�v�f�̐e�v�f���擾
		const GameObjectPtr& beforeChildParent = child->getParent();

		// �e�v�f�������Ă��Ȃ� or ���g�ł͂Ȃ��e�������Ă����� �������Ȃ�
		if (beforeChildParent.expired() || !beforeChildParent.isSame(GameObjectPtr(weak_from_this()))) return;

		// �폜�������q�v�f�̐e�q�֌W�Ǘ��R���|�[�l���g�̐e�v�f���X�V����
		child->m_parentChildManager->setParent(GameObjectPtr());

		// ���g�̐e�q�֌W�Ǘ��R���|�[�l���g����폜�������q�v�f���폜����
		m_parentChildManager->removeChild(child);

		// �ǉ�����q���̐e�ύX���֐����Ă�
		child->m_componentList.runAfterChangeParentAll(GameObjectPtr(weak_from_this()));
	}
}