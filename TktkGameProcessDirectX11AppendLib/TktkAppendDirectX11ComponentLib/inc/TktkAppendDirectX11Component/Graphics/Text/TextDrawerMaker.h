#ifndef TEXT_DRAWER_MAKER_H_
#define TEXT_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "TextDrawer.h"

namespace tktk
{
	class TextDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static TextDrawerMaker& makeStart(GameObjectPtr user);

	private:

		// ���g�̃|�C���^
		static TextDrawerMaker m_self;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		TextDrawerMaker() = default;
		TextDrawerMaker(const TextDrawerMaker& other) = default;
		TextDrawerMaker& operator = (const TextDrawerMaker& other) = default;

	public:

		// �쐬����
		CfpPtr<TextDrawer> create();

		// �`��D��x��ݒ肷��
		TextDrawerMaker& drawPriority(float value);

		// �����\���e�L�X�g��ݒ肷��
		TextDrawerMaker& initText(const std::string& value);

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{ };
		float m_drawPriority{ 0.0f };
		std::string m_initText{  };
	};
}
#endif // !TEXT_DRAWER_MAKER_H_