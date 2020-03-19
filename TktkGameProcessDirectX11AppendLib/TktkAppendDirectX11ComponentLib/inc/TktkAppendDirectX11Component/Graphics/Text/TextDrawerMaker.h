#ifndef TEXT_DRAWER_MAKER_H_
#define TEXT_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TextDrawer.h"

namespace tktk
{
	class TextDrawerMaker
	{
	public:

		// インスタンス作成開始
		static TextDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// 自身のポインタ
		static TextDrawerMaker m_self;

	private:

		// プライベートコンストラクタ達
		TextDrawerMaker() = default;
		TextDrawerMaker(const TextDrawerMaker& other) = default;
		TextDrawerMaker& operator = (const TextDrawerMaker& other) = default;

	public:

		// 作成する
		CfpPtr<TextDrawer> create();

		// 描画優先度を設定する
		TextDrawerMaker& drawPriority(float value);

		// 初期表示テキストを設定する
		TextDrawerMaker& initText(const std::string& value);

	private:

		// 作成用変数達
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		std::string m_initText{  };
	};
}
#endif // !TEXT_DRAWER_MAKER_H_