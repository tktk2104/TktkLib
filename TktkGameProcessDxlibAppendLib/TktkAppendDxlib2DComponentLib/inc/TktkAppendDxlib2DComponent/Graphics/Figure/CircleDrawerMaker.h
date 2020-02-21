#ifndef CIRCLE_DRAWER_MAKER_H_
#define CIRCLE_DRAWER_MAKER_H_

#include "CircleDrawer.h"

namespace tktk
{
	struct CircleDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static CircleDrawerMaker& makeStart();

	public:

		// �쐬����
		CircleDrawer* create();

		// �^�~�̔��a��ݒ肷��
		CircleDrawerMaker& radius(float value);

		// �^�~�̃��[�J�����W��ݒ肷��
		CircleDrawerMaker& localPosition(const Vector2& value);

		// �^�~�̐��̑�����ݒ肷��
		CircleDrawerMaker& lineThickness(float value);

		// �h��Ԃ��t���O��ݒ肷��
		CircleDrawerMaker& isFill(bool value);

		/// �^�~�̕`��F��ݒ肷��
		CircleDrawerMaker& circleColor(const Color& value);

		// �`��D��x��ݒ肷��
		CircleDrawerMaker& drawPriority(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		CircleDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		CircleDrawerMaker& blendParam(float value);

		// �A���`�G�C���A�X�̎g�p�t���O��ݒ肷��
		CircleDrawerMaker& useAntialiasing(bool value);

		// �A���`�G�C���A�X���g�p���鎞�Ɏg���~���`��钸�_�̐���ݒ肷��
		CircleDrawerMaker& vertexNum(int value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		CircleDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static CircleDrawerMaker m_self;

	private:

		float m_radius{ 1.0f };
		Vector2 m_localPosition{ Vector2::zero };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_circleColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		int m_vertexNum{ 32 };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !CIRCLE_DRAWER_MAKER_H_