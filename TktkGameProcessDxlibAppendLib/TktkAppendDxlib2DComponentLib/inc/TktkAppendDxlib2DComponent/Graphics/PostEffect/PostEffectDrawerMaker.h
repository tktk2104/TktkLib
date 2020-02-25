#ifndef POST_EFFECT_DRAWER_MAKER_H_
#define POST_EFFECT_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "PostEffectDrawer.h"

namespace tktk
{
	class PostEffectDrawerMaker
	{
	public:

		// インスタンス作成開始
		static PostEffectDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<PostEffectDrawer> create();

		// 描画優先度を設定する
		PostEffectDrawerMaker& drawPriority(float value);

		// ポストエフェクトをかける時に使用するパラメーターを設定する
		PostEffectDrawerMaker& postEffectDrawParameters(const std::vector<PostEffectDrawParameter>& value);

		// ポストエフェクトをかける時に使用するパラメーターを追加する
		PostEffectDrawerMaker& addPostEffectDrawParameter(const PostEffectDrawParameter& value);

	private:

		// 自身のポインタ
		static PostEffectDrawerMaker m_self;

	private:
		
		// 作成用変数達
		GameObjectPtr m_user{};
		float m_drawPriority{ 0 };
		std::vector<PostEffectDrawParameter> m_postEffectDrawParameters;
	};
}
#endif // !POST_EFFECT_DRAWER_MAKER_H_