#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawerMaker.h"

namespace tktk
{
	PostEffectDrawerMaker PostEffectDrawerMaker::m_self;

	PostEffectDrawerMaker& PostEffectDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = PostEffectDrawerMaker();
		
		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープIDのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapId = DX12GameManager::getSystemId(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		// コンポーネントを作成してそのポインタを返す
		return m_user->createComponent<PostEffectDrawer>(
			m_drawPriority,
			m_postEffectMaterialId,
			m_useRtvDescriptorHeapId
			);
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::useRtvDescriptorHeapIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapId = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialIdImpl(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_postEffectMaterialId = value;
		return *this;
	}
}