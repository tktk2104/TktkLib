#ifndef RECT_DRAWER_MAKER_H_
#define RECT_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RectDrawer.h"

namespace tktk
{
	struct RectDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RectDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<RectDrawer> create();

	public:

		// �����`�̑傫����ݒ�
		RectDrawerMaker& rectSize(const Vector2& value);

		// �����`�̃��[�J�����W��ݒ�
		RectDrawerMaker& localPosition(const Vector2& value);

		// �����`�̐��̑�����ݒ肷��
		RectDrawerMaker& lineThickness(float value);

		// �h��Ԃ��t���O��ݒ肷��
		RectDrawerMaker& isFill(bool value);

		// �����`�̕`��F��ݒ肷��
		RectDrawerMaker& rectColor(const Color& value);

		// �`��D��x��ݒ肷��
		RectDrawerMaker& drawPriority(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		RectDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		RectDrawerMaker& blendParam(float value);

		// �A���`�G�C���A�X�̎g�p�t���O��ݒ肷��
		RectDrawerMaker& useAntialiasing(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		RectDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static RectDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		Vector2 m_rectSize{ Vector2::one };
		Vector2 m_localPosition{ Vector2::zero };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_rectColor{ Color::white };
		float m_drawPriority{ 0.0f };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !RECT_DRAWER_MAKER_H_
