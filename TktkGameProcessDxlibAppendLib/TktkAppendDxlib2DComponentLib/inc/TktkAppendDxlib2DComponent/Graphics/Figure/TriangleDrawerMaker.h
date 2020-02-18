#ifndef TRIANGLE_DRAWER_MAKER_H_
#define TRIANGLE_DRAWER_MAKER_H_

#include <memory>
#include "TriangleDrawer.h"

namespace tktk
{
	struct TriangleDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static TriangleDrawerMaker& makeStart();

	public:

		// �쐬����
		std::shared_ptr<TriangleDrawer> create();

		// ���g�̍��W���猩���O�p�`�̂P�ڂ̍��W��ݒ�
		TriangleDrawerMaker& relativeFirstPos(const Vector2& value);

		// ���g�̍��W���猩���O�p�`�̂Q�ڂ̍��W��ݒ�
		TriangleDrawerMaker& relativeSecondPos(const Vector2& value);

		//���g�̍��W���猩���O�p�`�̂R�ڂ̍��W��ݒ�
		TriangleDrawerMaker& relativeThirdPos(const Vector2& value);

		// �O�p�`�̐��̑�����ݒ肷��
		TriangleDrawerMaker& lineThickness(float value);

		// �h��Ԃ��t���O��ݒ肷��
		TriangleDrawerMaker& isFill(bool value);

		// �O�p�`�̕`��F��ݒ肷��
		TriangleDrawerMaker& triangleColor(const Color& value);

		// �`��D��x��ݒ肷��
		TriangleDrawerMaker& drawPriority(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		TriangleDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		TriangleDrawerMaker& blendParam(float value);

		// �A���`�G�C���A�X�̎g�p�t���O��ݒ肷��
		TriangleDrawerMaker& useAntialiasing(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		TriangleDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static TriangleDrawerMaker m_self;

	private:

		Vector2 m_relativeFirstPos{ Vector2(0.0f, 1.0f) };
		Vector2 m_relativeSecondPos{ Vector2(1.0f, -1.0f) };
		Vector2 m_relativeThirdPos{ Vector2(1.0f, 1.0f) };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_triangleColor{ Color::white };
		float m_drawPriority{ 0 };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !TRIANGLE_DRAWER_MAKER_H_

