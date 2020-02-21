#ifndef QUADRILATERALBILL_BOARD_DRAWER_H_
#define QUADRILATERALBILL_BOARD_DRAWER_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	// �l�p�`�̃r���{�[�h��\��
	// �S�_�̍��W���w�肵�쐬�����l�p�`��Transform3D���g���Ĉړ��E�X�P�[�����O�����`�悷��
	// �y�O��R���|�[�l���g�FTransform3D�z
	// ����]�͂ł��Ȃ�
	// ���X�P�[����Transform3D��LocalScale.xy���g�p
	class QuadrilateralBillboardDrawer
		: public ComponentBase
	{
	public:

		QuadrilateralBillboardDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,	// 
			int textureID,								// �`�悷��e�N�X�`��ID
			int splitTextureIndex,						// �`�悷��e�N�X�`���̕����ǂݍ��ݔԍ�
			const Vector2& leftTopPos,					// ������W
			const Vector2& rightTopPos,					// �E����W
			const Vector2& leftBottomPos,				// �������W
			const Vector2& rightBottomPos				// �E�����W
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// �`�悷��e�N�X�`��ID���擾����
		int getTextureID() const;
		// �`�悷��e�N�X�`��ID��ݒ肷��
		void setTextureID(int textureID);

		// �`�悷��e�N�X�`���̕����ԍ����擾
		int getSplitTextureIndex() const;
		// �`�悷��e�N�X�`���̕����ԍ���ݒ�
		void setSplitTextureIndex(int splitTextureIndex);

		// ������W���擾
		Vector2 getLeftTopPos() const;
		// �E����W���擾
		Vector2 getRightTopPos() const;
		// �������W���擾
		Vector2 getLeftBottomPos() const;
		// �E�����W���擾
		Vector2 getRightBottomPos() const;

		// ������W��ݒ�
		void setLeftTopPos(const Vector2& leftTopPos);
		// �E����W��ݒ�
		void setRightTopPos(const Vector2& rightTopPos);
		// �������W��ݒ�
		void setLeftBottomPos(const Vector2& leftBottomPos);
		// �E�����W��ݒ�
		void setRightBottomPos(const Vector2& rightBottomPos);

		// DxLib���g����3D�`��Ŏg�p����p�����[�^���擾
		const DxLibDraw3DParam& getDxLibDraw3DParam() const;

		// �\�����闧���̂̃��[�J���s����Đݒ�
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
		CfpPtr<Transform3D> m_transform3D;

		// DxLib���g����3D�`��Ŏg�p����p�����[�^
		DxLibDraw3DParam m_dxLibDraw3DParam;

		// �`�悷��e�N�X�`��ID
		int m_textureID{ -1 };

		// �`�悷��e�N�X�`���̕����ǂݍ��ݔԍ�
		int m_splitTextureIndex{ -1 };

		// ������W
		Vector2 m_leftTopPos;

		// �E����W
		Vector2 m_rightTopPos;

		// �������W
		Vector2 m_leftBottomPos;

		// �E�����W
		Vector2 m_rightBottomPos;
	};
}
#endif // !QUADRILATERALBILL_BOARD_DRAWER_H_