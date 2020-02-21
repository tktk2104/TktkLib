#ifndef QUADRILATERAL_BILLBOARD_DRAWER_MAKER_H_
#define QUADRILATERAL_BILLBOARD_DRAWER_MAKER_H_

#include "QuadrilateralBillboardDrawer.h"

namespace tktk
{
	class QuadrilateralBillboardDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static QuadrilateralBillboardDrawerMaker& makeStart();

	public:

		// �쐬����
		QuadrilateralBillboardDrawer* create();

		// �`��D��x��ݒ肷��
		QuadrilateralBillboardDrawerMaker& drawPriority(float value);

		// �\������e�N�X�`����Id��ݒ肷��
		QuadrilateralBillboardDrawerMaker& textureId(int value);

		// �\������e�N�X�`���̕����ǂݍ��ݔԍ���ݒ肷��
		QuadrilateralBillboardDrawerMaker& splitTextureIndex(int value);

		// �r���{�[�h�̃��[�J�����W��ݒ肷��
		QuadrilateralBillboardDrawerMaker& localPos(const Vector3& value);

		// ������W��ݒ肷��
		QuadrilateralBillboardDrawerMaker& leftTopPos(const Vector2& value);

		// �E����W��ݒ肷��
		QuadrilateralBillboardDrawerMaker& rightTopPos(const Vector2& value);

		// �������W��ݒ肷��
		QuadrilateralBillboardDrawerMaker& leftBottomPos(const Vector2& value);

		// �E�����W��ݒ肷��
		QuadrilateralBillboardDrawerMaker& rightBottomPos(const Vector2& value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		QuadrilateralBillboardDrawerMaker& blendMode(const BlendMode& value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		QuadrilateralBillboardDrawerMaker& blendParam(float value);

		// ���C�g���g�p���ĕ`����s�����H
		QuadrilateralBillboardDrawerMaker& useLight(bool value);

		// Z�o�b�t�@���g�p���ĕ`����s����?
		QuadrilateralBillboardDrawerMaker& writeZBuffer(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		QuadrilateralBillboardDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static QuadrilateralBillboardDrawerMaker m_self;

	private:

		float m_drawPriority{ 0 };
		int m_textureId{ -1 };
		int m_splitTextureIndex{ -1 };
		Vector3 m_localPos{ Vector3::zero };
		Vector2 m_leftTopPos	{ Vector2(-0.5f, -0.5f) };
		Vector2 m_rightTopPos	{ Vector2( 0.5f, -0.5f) };
		Vector2 m_leftBottomPos	{ Vector2(-0.5f,  0.5f) };
		Vector2 m_rightBottomPos{ Vector2( 0.5f,  0.5f) };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
	};
}
#endif // !QUADRILATERAL_BILLBOARD_DRAWER_MAKER_H_