#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include <memory>
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	public:

		// �C���X�^���X�쐬�J�n
		static MeshDrawerMaker& makeStart();

	public:

		// �쐬����
		MeshDrawer* create();

		// �`��D��x
		MeshDrawerMaker& drawPriority(float value);

		// �\�����郁�b�V����Id
		MeshDrawerMaker& meshID(int value);

		// �\�����郁�b�V���̃��[�J�����W
		MeshDrawerMaker& meshLocalPos(const Vector3& value);

		// �\�����郁�b�V���̃��[�J����]
		MeshDrawerMaker& meshLocalRotation(const Quaternion& value);

		// �\�����郁�b�V���̃��[�J���X�P�[��
		MeshDrawerMaker& meshLocalScale(const Vector3& value);

		// �`��̃u�����h���@�̎��
		MeshDrawerMaker& blendMode(BlendMode value);

		// �`��̃u�����h�Ɏg�p����l
		MeshDrawerMaker& blendParam(float value);

		// ���C�g���g�p���ĕ`����s�����H
		MeshDrawerMaker& useLight(bool value);

		// Z�o�b�t�@���g�p���ĕ`����s����?
		MeshDrawerMaker& writeZBuffer(bool value);

		// �`�悷�郌���_�[�^�[�Q�b�g��ݒ肷��
		MeshDrawerMaker& renderTargetId(int value);

		// �e�𐶐����邩��ݒ�
		MeshDrawerMaker& createShadow(bool value);

		// �e�̐������s���R���|�[�l���g�̕`��D��x��ݒ�
		MeshDrawerMaker& shadowCreatorPriority(float value);

	private:

		// ���g�̃|�C���^
		static MeshDrawerMaker m_self;

	private:

		float m_drawPriority{ 0.0f };
		int m_meshID{ -1 };
		Vector3 m_meshLocalPos{ Vector3::zero };
		Quaternion m_meshLocalRotation{ Quaternion::createFromEulerAngle(Vector3(0.0f, 180.0f, 0.0f)) };
		Vector3 m_meshLocalScale{ Vector3::one };
		BlendMode m_blendMode{ BlendMode::None };
		float m_blendParam{ 1.0f };
		bool m_useLight{ true };
		bool m_writeZBuffer{ true };
		int m_renderTargetId{ -1 };
		bool m_createShadow{ false };
		float m_shadowCreatorPriority{ 100 };
	};
}
#endif // !MESH_DRAWER_MAKER_H_