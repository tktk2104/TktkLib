#ifndef OVAL_DRAWER_MAKER_H_
#define OVAL_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "OvalDrawer.h"

namespace tktk
{
	struct OvalDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static OvalDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		CfpPtr<OvalDrawer> create();

	public:

		// �ȉ~�̑傫����ݒ肷��
		OvalDrawerMaker& ovalSize(const Vector2& value);

		// �ȉ~�̃��[�J�����W��ݒ肷��
		OvalDrawerMaker& localPosition(const Vector2& value);

		// �ȉ~�̐��̑�����ݒ肷��
		OvalDrawerMaker& lineThickness(float value);

		// �h��Ԃ��t���O��ݒ肷��
		OvalDrawerMaker& isFill(bool value);

		/// �ȉ~�̕`��F��ݒ肷��
		OvalDrawerMaker& ovalColor(const Color& value);

		// �`��D��x��ݒ肷��
		OvalDrawerMaker& drawPriority(float value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		OvalDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		OvalDrawerMaker& blendParam(float value);

		// �A���`�G�C���A�X�̎g�p�t���O��ݒ肷��
		OvalDrawerMaker& useAntialiasing(bool value);

		// �A���`�G�C���A�X���g�p���鎞�Ɏg���~���`��钸�_�̐���ݒ肷��
		OvalDrawerMaker& vertexNum(int value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		OvalDrawerMaker& renderTargetId(int value);

	private:

		// ���g�̃|�C���^������������
		static void reset();

		// ���g�̃|�C���^
		static OvalDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		Vector2 m_ovalSize{ Vector2::one };
		Vector2 m_localPosition{ Vector2::zero };
		float m_lineThickness{ 1.0f };
		bool m_isFill{ true };
		Color m_ovalColor{ Color::white };
		float m_drawPriority{ 0.0f };
		BlendMode m_blendMode{ BlendMode::Alpha };
		float m_blendParam{ 1.0f };
		bool m_useAntialiasing{ true };
		int m_vertexNum{ 32 };
		bool m_useRenderTarget{ false };
		int m_renderTargetId{ -1 };
	};
}
#endif // !OVAL_DRAWER_MAKER_H_
