#ifndef SPRITE_DRAWER_MAKER_H_
#define SPRITE_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "SpriteDrawer.h"

namespace tktk
{
	class SpriteDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static SpriteDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<SpriteDrawer> create();

		SpriteDrawerMaker& drawPriority(float value);

		SpriteDrawerMaker& textureId(int value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static SpriteDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		int m_textureId{ 0 };
	};
}
#endif // !SPRITE_DRAWER_MAKER_H_