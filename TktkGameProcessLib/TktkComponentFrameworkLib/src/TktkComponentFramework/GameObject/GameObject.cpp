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
		// 親要素を再設定する前の親要素を取得
		CfpPtr<GameObject> befoerSelfParent = getParent();
	
		// 設定する親が存在しなければ
		if (parent.isNull())
		{
			// 親要素を再設定する前の親要素が存在したらその親のの子要素から自身を外す
			if (!befoerSelfParent.isNull())
			{
				befoerSelfParent->removeChild(m_selfPtr);
			}
			return;
		}
		// 設定する親の子要素に自身を追加する
		parent->addChild(m_selfPtr);
	}
	
	const std::forward_list<CfpPtr<GameObject>> & GameObject::getChildren() const
	{
		return m_pcManager->getChildren();
	}
	
	void GameObject::addChild(CfpPtr<GameObject> child)
	{
		// 追加する前の子要素の親要素を取得
		CfpPtr<GameObject> beforeChildParent = child->getParent();
	
		// もう引数のGameObjectが自身の子要素だったら何もしない
		if (beforeChildParent == m_selfPtr) return;
	
		// 既に親要素を持っていたら
		if (!beforeChildParent.isNull())
		{
			// その親要素から追加する前の子要素を削除する
			beforeChildParent->m_pcManager->removeChild(child);
		}
		// 自身の親子関係管理コンポーネントに新たな子要素を追加する
		m_pcManager->addChild(child);
	
		// 追加する子供の親子関係管理コンポーネントの親要素を更新する
		child->m_pcManager->setParent(m_selfPtr);
	
		// 追加する子供の親変更時関数を呼ぶ
		child->m_componentList.afterChangeParentAll(beforeChildParent);
	}
	
	void GameObject::removeChild(CfpPtr<GameObject> child)
	{
		// 追加する前の子要素の親要素を取得
		CfpPtr<GameObject> beforeChildParent = child->getParent();
	
		// 親要素を持っていない or 自身ではない親を持っていたら 何もしない
		if (beforeChildParent.isNull() || beforeChildParent != m_selfPtr) return;
	
		// 削除したい子要素の親子関係管理コンポーネントの親要素を更新する
		child->m_pcManager->setParent(CfpPtr<GameObject>());
	
		// 自身の親子関係管理コンポーネントから削除したい子要素を削除する
		m_pcManager->removeChild(child);
	
		// 追加する子供の親変更時関数を呼ぶ
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