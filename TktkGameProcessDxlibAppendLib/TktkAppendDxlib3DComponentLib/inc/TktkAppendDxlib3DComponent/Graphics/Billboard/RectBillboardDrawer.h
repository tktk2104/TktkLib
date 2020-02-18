#ifndef RECT_BILLBOARD_DRAWER_H_
#define RECT_BILLBOARD_DRAWER_H_

#include <TktkMath/Vector2.h>
#include <TktkMath/Vector3.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend3DComponent/Transform3D.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>
#include "../../../TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	class RectBillboardDrawer
		: public tktk::ComponentBase
	{
	public:

		RectBillboardDrawer(
			const DxLibDraw3DParam& dxLibDraw3DParam,
			int textureId,								// �\������e�N�X�`����Id
			int splitTextureIndex,						// �\������e�N�X�`���̕����ǂݍ��ݔԍ�
			const Vector2& rotateCenterRate,			// ��]������Ƃ��̒��S�ʒu�i�����j
			float billboardScaleRate					// �r���{�[�h�̃X�P�[���i�����j
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// �`�悷��e�N�X�`��ID���擾����
		int getTextureID() const;
		// �`�悷��e�N�X�`��ID���Đݒ肷��
		void setTextureID(int textureID);

		// �`�悷��e�N�X�`���̕����ǂݍ��ݔԍ����擾����
		int getSplitTextureIndex() const;
		// �`�悷��e�N�X�`���̕����ǂݍ��ݔԍ����Đݒ肷��
		void setSplitTextureIndex(int splitTextureIndex);

		// �r���{�[�h�̃X�P�[�����擾�i�����j
		float getBillboardScaleRate() const;
		// �r���{�[�h�̃X�P�[�����Đݒ�i�����j
		void setBillboardScaleRate(float billboardScaleRate);

		// ��]������Ƃ��̒��S�ʒu���擾�i�����j
		const Vector2& getRotateCenterRate() const;
		// ��]������Ƃ��̒��S�ʒu���Đݒ�i�����j
		void setRotateCenterRate(const Vector2& rotateCenterRate);

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
		std::weak_ptr<Transform3D> m_transform3D;

		// DxLib���g����3D�`��Ŏg�p����p�����[�^
		DxLibDraw3DParam m_dxLibDraw3DParam;

		// �`�悷��e�N�X�`��ID
		int m_textureID{ -1 };

		// �`�悷��e�N�X�`���̕����ǂݍ��ݔԍ�
		int m_splitTextureIndex{ -1 };

		// ��]������Ƃ��̒��S�ʒu�i�����j
		Vector2 m_rotateCenterRate{ Vector2(0.5f, 0.5f) };

		// �r���{�[�h�̃X�P�[��
		float m_billboardScaleRate{ 1.0f };
	};
}
#endif // !RECT_BILLBOARD_DRAWER_H_