#ifndef SPHERE_DRAWER_H_
#define SPHERE_DRAWER_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	// ���̂�`�悷��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform3D�z
	class SphereDrawer
		: public ComponentBase
	{
	public:

		SphereDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,	// DxLib���g����3D�`��Ŏg�p����p�����[�^
			float radius,
			int divNum,
			bool isFill,
			const Color& sphereColor
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// ���̂̑傫�����擾
		float getRadius() const;
		// ���̂̑傫�����Đݒ�
		void setRadius(float radius);

		// ���̂�`�悷�鎞�̃|���S���ׂ̍������擾
		int getDivNum() const;
		// ���̂�`�悷�鎞�̃|���S���ׂ̍������Đݒ�
		void setDivNum(int divNum);

		// �h��Ԃ��t���O���擾
		bool getIsFill() const;
		// �h��Ԃ��t���O���Đݒ�
		void setIsFill(bool isFill);

		// ���̂̕`��F���擾
		const Color& getSphereColor() const;
		// ���̂̕`��F���Đݒ�
		void setSphereColor(const Color& sphereColor);

		// DxLib���g����3D�`��Ŏg�p����p�����[�^���擾
		const DxLibDraw3DParam& getDxLibDraw3DParam() const;

		// �\�����郁�b�V���̃��[�J���s����Đݒ�
		void setMeshLocalMat(const Matrix4& localMat);
		// �`��̃u�����h���@�̎�ނ��Đݒ�
		void setBlendMode(BlendMode blendMode);
		// �`��̃u�����h�Ɏg�p����l���Đݒ�
		void setBlendParam(float blendParam);
		// ���C�g���g�p���ĕ`����s�������Đݒ�
		void setUseLight(bool useLight);
		// Z�o�b�t�@���g�p���ĕ`����s�������Đݒ�
		void setWriteZBuffer(bool writeZBuffer);
		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂R�������W�R���|�[�l���g
		std::weak_ptr<Transform3D> m_transform3D;

		// DxLib���g����3D�`��Ŏg�p����p�����[�^
		DxLibDraw3DParam m_dxLibDraw3DParam;

		// ���̂̔��a
		float m_radius;

		// ���̂�`�悷�鎞�̃|���S���ׂ̍���
		int m_divNum;

		// �h��Ԃ��t���O
		bool m_isFill;

		// ���̂̕`��F
		Color m_sphereColor;
	};
}
#endif // !SPHERE_DRAWER_H_