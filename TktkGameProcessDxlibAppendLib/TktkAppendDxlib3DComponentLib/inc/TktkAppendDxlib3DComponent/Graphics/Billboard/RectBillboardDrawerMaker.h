#ifndef RECT_BILLBOARD_DRAWER_MAKER_H_
#define RECT_BILLBOARD_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "RectBillboardDrawer.h"

namespace tktk
{
	class RectBillboardDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static RectBillboardDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<RectBillboardDrawer> create();

		// �`��D��x��ݒ肷��
		RectBillboardDrawerMaker& drawPriority(float value);

		// �\������e�N�X�`����Id��ݒ肷��
		RectBillboardDrawerMaker& textureId(int value);

		// �\������e�N�X�`���̕����ǂݍ��ݔԍ���ݒ肷��
		RectBillboardDrawerMaker& splitTextureIndex(int value);

		// �r���{�[�h�̃��[�J�����W��ݒ肷��
		RectBillboardDrawerMaker& localPos(const Vector3& value);

		// ��]������Ƃ��̒��S�ʒu�i�����j��ݒ肷��
		RectBillboardDrawerMaker& rotateCenterRate(const Vector2& value);

		// �r���{�[�h�̃X�P�[���i�����j��ݒ肷��
		RectBillboardDrawerMaker& billboardScaleRate(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		RectBillboardDrawerMaker& blendMode(const BlendMode& value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		RectBillboardDrawerMaker& blendParam(float value);

		// ���C�g���g�p���ĕ`����s�����H
		RectBillboardDrawerMaker& useLight(bool value);

		// Z�o�b�t�@���g�p���ĕ`����s����?
		RectBillboardDrawerMaker& writeZBuffer(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		RectBillboardDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^
		static RectBillboardDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_drawPriority{ 0 };
		int m_textureId{ -1 };
		int m_splitTextureIndex{ -1 };
		Vector3 m_localPos{ Vector3::zero };
		Vector2 m_rotateCenterRate{ Vector2(0.5f, 0.5f) };
		float m_billboardScaleRate{ 1.0f };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
	};
}
#endif // !RECT_BILLBOARD_DRAWER_MAKER_H_
