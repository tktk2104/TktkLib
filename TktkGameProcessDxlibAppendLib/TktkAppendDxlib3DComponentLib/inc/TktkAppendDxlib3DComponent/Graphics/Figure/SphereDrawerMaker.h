#ifndef SPHERE_DRAWER_MAKER_H_
#define SPHERE_DRAWER_MAKER_H_

#include <memory>
#include "SphereDrawer.h"

namespace tktk
{
	class SphereDrawerMaker
	{
	public:

		static SphereDrawerMaker& makeStart();

	public:

		std::shared_ptr<SphereDrawer> create();

		// �`��D��x��ݒ肷��
		SphereDrawerMaker& drawPriority(float value);

		// ���̂̑傫����ݒ肷��
		SphereDrawerMaker& radius(float value);

		// ���̂�`�悷�鎞�̃|���S���ׂ̍�����ݒ肷��
		SphereDrawerMaker& divNum(int value);

		// ���̂̃��[�J�����W��ݒ肷��
		SphereDrawerMaker& localPosition(const Vector3& value);

		// �h��Ԃ��t���O��ݒ肷��
		SphereDrawerMaker& isFill(bool value);

		// ���̂̕`��F��ݒ肷��
		SphereDrawerMaker& sphereColor(const Color& value);

		// �`��̃u�����h���@�̎�ނ�ݒ肷��
		SphereDrawerMaker& blendMode(const BlendMode& value);

		// �`��̃u�����h�Ɏg�p����l��ݒ肷��
		SphereDrawerMaker& blendParam(float value);

		// ���C�g���g�p���ĕ`����s�����H
		SphereDrawerMaker& useLight(bool value);

		// Z�o�b�t�@���g�p���ĕ`����s����?
		SphereDrawerMaker& writeZBuffer(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		SphereDrawerMaker& renderTargetId(int value);

		// �e�𐶐����邩��ݒ�
		SphereDrawerMaker& createShadow(bool value);

		// �e�̐������s���R���|�[�l���g�̕`��D��x��ݒ�
		SphereDrawerMaker& shadowCreatorPriority(float value);

	private:

		static SphereDrawerMaker m_self;

	private:

		float m_drawPriority{ 0.0f };
		float m_radius{ 1.0f };
		int m_divNum{ 30 };
		Vector3 m_localPosition{ Vector3::zero };
		bool m_isFill{ true };
		Color m_sphereColor{ Color::white };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
		bool m_createShadow{ false };
		float m_shadowCreatorPriority{ 100 };
	};
}
#endif // !SPHERE_DRAWER_MAKER_H_