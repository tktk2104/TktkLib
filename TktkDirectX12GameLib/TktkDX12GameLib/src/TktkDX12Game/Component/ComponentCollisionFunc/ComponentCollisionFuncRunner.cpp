#include "TktkDX12Game/Component/ComponentCollisionFunc/ComponentCollisionFuncRunner.h"

#include <algorithm>
#include "TktkDX12Game/Component/ComponentBase.h"

namespace tktk
{
	void ComponentCollisionFuncRunner::updateHitObjectList()
	{
		// �O�t���[���̏Փ˔��茋�ʂ��X�V���āA���݂̏Փ˔��茋�ʂ�����������
		m_preHitObjectList = std::move(m_curHitObjectList);
		m_curHitObjectList.clear();
	}

	void ComponentCollisionFuncRunner::runCollideFunc(ComponentCollisionFuncRunner& other)
	{
		if (m_vtablePtr->runIsCollide(m_selfPtr, other.m_selfPtr))
		{
			auto curHitObject = HitObject(other.m_vtablePtr, other.m_selfPtr);

			m_curHitObjectList.push_front(curHitObject);

			// �O�t���[���ŏՓ˂��Ă��������肷��
			bool preFrameHit = false;
			for (const auto& node : m_preHitObjectList)
			{
				if (node.m_selfPtr.isSame(other.m_selfPtr))
				{
					preFrameHit = true;
					break;
				}
			}
			if (preFrameHit)
			{
				// �Փ˒�����
				      m_vtablePtr->runOnCollisionStay(      m_selfPtr, other.m_selfPtr->getGameObject());
				other.m_vtablePtr->runOnCollisionStay(other.m_selfPtr,       m_selfPtr->getGameObject());
			}
			else
			{
				// �ՓˊJ�n����
				      m_vtablePtr->runOnCollisionEnter(      m_selfPtr,	other.m_selfPtr->getGameObject());
				other.m_vtablePtr->runOnCollisionEnter(other.m_selfPtr,	      m_selfPtr->getGameObject());
			}
		}
		else
		{
			// �O�t���[���ŏՓ˂��Ă��������肷��
			bool preFrameHit = false;
			for (const auto& node : m_preHitObjectList)
			{
				if (node.m_selfPtr.isSame(other.m_selfPtr))
				{
					preFrameHit = true;
					break;
				}
			}
			if (preFrameHit)
			{
				// �ՓˏI������
				      m_vtablePtr->runOnCollisionExit(      m_selfPtr,	other.m_selfPtr->getGameObject());
				other.m_vtablePtr->runOnCollisionExit(other.m_selfPtr,	      m_selfPtr->getGameObject());
			}
		}
	}

	bool ComponentCollisionFuncRunner::isDead() const
	{
		return m_selfPtr.isDead();
	}

	ComponentCollisionFuncRunner::HitObject::HitObject(VTable* vtablePtr, ComponentBasePtr selfPtr)
		: m_vtablePtr(vtablePtr)
		, m_selfPtr(selfPtr) {}
}