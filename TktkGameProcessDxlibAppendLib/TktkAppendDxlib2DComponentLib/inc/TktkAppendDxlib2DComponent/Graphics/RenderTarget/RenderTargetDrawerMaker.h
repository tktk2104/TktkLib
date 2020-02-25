#ifndef RENDER_TARGET_DRAWER_MAKER_H_
#define RENDER_TARGET_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RenderTargetDrawer.h"

namespace tktk
{
	class RenderTargetDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RenderTargetDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<RenderTargetDrawer> create();

		// �`��D��x��ݒ肷��
		RenderTargetDrawerMaker& drawPriority(float value);

		// �`�悷�郌���_�[�^�[�Q�b�g��Id��ݒ肷��
		RenderTargetDrawerMaker&  drawRenderTargetId(int value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		RenderTargetDrawerMaker&  blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		RenderTargetDrawerMaker&  blendParam(float value);

	private:

		// ���g�̃|�C���^
		static RenderTargetDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_drawPriority{ 0.0f };
		int m_drawRenderTargetId{ -1 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
	};
}
#endif // !RENDER_TARGET_DRAWER_MAKER_H_