#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SpriteDrawer.h"

namespace tktk
{
	class SpriteDrawerMaker
	{
	public:

		// インスタンス作成開始
		static SpriteDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成する
		CfpPtr<SpriteDrawer> create();

		SpriteDrawerMaker& drawPriority(float value);

		SpriteDrawerMaker& textureId(int value);

	private:

		// 自身のポインタを初期化する
		static void reset();

		// 自身のポインタ
		static SpriteDrawerMaker m_self;

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_textureId{ 0 };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_