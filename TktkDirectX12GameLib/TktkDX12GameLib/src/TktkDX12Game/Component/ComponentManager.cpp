#include "TktkDX12Game/Component/ComponentManager.h"

#include "TktkDX12Game/Component/ComponentMainList.h"

namespace tktk
{
	void ComponentManager::update()
	{
		// アクティブフラグの判定とフラグ変更時の関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->activeChangeCheck();
		}
		
		// 「update()」関数呼び出し処理
		for (const auto& node : m_mainMap)
		{
			node.second->runUpdate();
		}

		// 衝突判定系関数呼び出し処理
		m_collisionList.runCollisionFunc();
		
		// メインリストが管理しているコンポーネントポインタの生存確認
		for (const auto& node : m_mainMap)
		{
			node.second->removeDeadComponent();
		}

		// 衝突判定リストが管理しているコンポーネントポインタの生存確認
		m_collisionList.removeDeadComponent();
		
		// 描画リストが管理しているコンポーネントポインタの生存確認
		m_drawList.removeDeadComponent();
	}

	void ComponentManager::draw()
	{
		// 「draw()」関数呼び出し処理
		m_drawList.runDraw();
	}

	void ComponentManager::addCollisionGroup(int firstGroup, int secondGroup)
	{
		m_collisionList.addCollisionGroup(firstGroup, secondGroup);
	}
}