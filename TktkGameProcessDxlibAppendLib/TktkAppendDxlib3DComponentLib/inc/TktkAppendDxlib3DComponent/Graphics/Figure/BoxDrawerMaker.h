#ifndef BOX_DRAWER_MAKER_H_
#define BOX_DRAWER_MAKER_H_

#include <TktkComponentFramework/GameObject/GameObjectPtr.h>
#include "BoxDrawer.h"

namespace tktk
{
	class BoxDrawerMaker
	{
	public:

		static BoxDrawerMaker& makeStart(GameObjectPtr user);

	public:

		CfpPtr<BoxDrawer> create();

		// �`��D��x��ݒ肷��
		BoxDrawerMaker& drawPriority(float value);

		// �����̂̑傫����ݒ肷��
		BoxDrawerMaker& boxSize(const Vector3& value);

		// �����̂̃��[�J�����W��ݒ肷��
		BoxDrawerMaker& localPosition(const Vector3& value);

		// �h��Ԃ��t���O��ݒ肷��
		BoxDrawerMaker& isFill(bool value);

		// �����̂̕`��F��ݒ肷��
		BoxDrawerMaker& boxColor(const Color& value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		BoxDrawerMaker& blendMode(const BlendMode& value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		BoxDrawerMaker& blendParam(float value);

		// ���C�g���g�p���ĕ`����s�����H
		BoxDrawerMaker& useLight(bool value);

		// Z�o�b�t�@���g�p���ĕ`����s����?
		BoxDrawerMaker& writeZBuffer(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		BoxDrawerMaker& renderTargetId(int value);

		// �e�𐶐����邩��ݒ�
		BoxDrawerMaker& createShadow(bool value);

		// �e�̐������s���R���|�[�l���g�̕`��D��x��ݒ�
		BoxDrawerMaker& shadowCreatorPriority(float value);

	private:

		static BoxDrawerMaker m_self;

	private:

		// �쐬�p�ϐ��B
		GameObjectPtr m_user{};
		float m_drawPriority{ 0.0f };
		Vector3 m_boxSize{ Vector3::one };
		Vector3 m_localPosition{ Vector3::zero };
		bool m_isFill{ true };
		Color m_boxColor{ Color::white };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
		bool m_createShadow{ false };
		float m_shadowCreatorPriority{ 100 };
	};
}
#endif // !BOX_DRAWER_MAKER_H_