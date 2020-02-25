#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <memory>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>

namespace tktk
{
	// スプライト描画コンポーネント
	// 【必須コンポーネント：Transform2D】
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(
			int textureId
		);

	public:

		void start();
		void draw() const;

	private:

		int m_textureId;

		CfpPtr<Transform2D> m_transform;
	};
}
#endif // !SPRITE_DRAWER_H_