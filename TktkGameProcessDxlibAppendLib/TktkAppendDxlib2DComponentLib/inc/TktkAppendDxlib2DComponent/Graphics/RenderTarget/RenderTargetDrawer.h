#ifndef RENDER_TARGET_DRAWER_H_
#define RENDER_TARGET_DRAWER_H_

#include <TktkComponentFramework/Component/ComponentBase.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	class RenderTargetDrawer
		: public ComponentBase
	{
	public:

		RenderTargetDrawer(
			int drawRenderTargetId,			// �`�悷�郌���_�[�^�[�Q�b�g��Id
			float drawPriority,				// �`��D��x
			BlendMode blendMode,			// �`��̃u�����h���@�̎��
			float blendParam				// �`��̃u�����h�Ɏg�p����l
		);

	public:

		void draw() const;

	private:

		// �`�悷�郌���_�[�^�[�Q�b�g��Id
		int m_drawRenderTargetId;

		// �`��̃u�����h���@�̎��
		BlendMode m_blendMode;

		// �`��̃u�����h�Ɏg�p����l
		float m_blendParam;
	};
}
#endif // !RENDER_TARGET_DRAWER_H_