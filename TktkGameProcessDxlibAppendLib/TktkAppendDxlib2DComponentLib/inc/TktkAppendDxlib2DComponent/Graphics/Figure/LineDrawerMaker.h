#ifndef LINE_DRAWER_MAKER_H_
#define LINE_DRAWER_MAKER_H_

#include <memory>
#include "LineDrawer.h"

namespace tktk
{
	struct LineDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static LineDrawerMaker& makeStart();

	public:

		// �쐬����
		std::shared_ptr<LineDrawer> create();

		// ���g�̍��W���猩�������̂P�ڂ̍��W��ݒ�
		LineDrawerMaker& relativeFirstPos(const Vector2& value);

		// ���g�̍��W���猩�������̂Q�ڂ̍��W��ݒ�
		LineDrawerMaker& relativeSecondPos(const Vector2& value);

		// �����̐��̑�����ݒ肷��
		LineDrawerMaker& lineThickness(float value);

		// �����̕`��F��ݒ肷��
		LineDrawerMaker& lineColor(const Color& value);

		// �`��D��x��ݒ肷��
		LineDrawerMaker& drawPriority(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		LineDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		LineDrawerMaker& blendParam(float value);

		// �A���`�G�C���A�X�̎g�p�t���O��ݒ肷��
		LineDrawerMaker& useAntialiasing(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		LineDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static LineDrawerMaker m_self;

	private:

		Vector2 m_relativeFirstPos{ Vector2(-1.0f, -1.0f) };
		Vector2 m_relativeSecondPos{ Vector2( 1.0f,  1.0f) };
		float m_lineThickness{ 1.0f };
		Color m_lineColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !LINE_DRAWER_MAKER_H_
