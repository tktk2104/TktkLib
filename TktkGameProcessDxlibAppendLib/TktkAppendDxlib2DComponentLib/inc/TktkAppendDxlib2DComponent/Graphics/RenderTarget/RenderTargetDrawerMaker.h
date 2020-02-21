#ifndef RENDER_TARGET_DRAWER_MAKER_H_
#define RENDER_TARGET_DRAWER_MAKER_H_

#include "RenderTargetDrawer.h"

namespace tktk
{
	class RenderTargetDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RenderTargetDrawerMaker& makeStart();

	public:

		// �쐬����
		RenderTargetDrawer* create();

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

		float m_drawPriority{ 0 };
		int m_drawRenderTargetId{ -1 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
	};
}
#endif // !RENDER_TARGET_DRAWER_MAKER_H_