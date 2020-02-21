#ifndef CIRCLE_DRAWER_H_
#define CIRCLE_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// �^�~��`�悷��R���|�[�l���g
	// �X�P�[���l��x�����̂ݓK�������
	// �y�O��R���|�[�l���g�FTransform2D�z
	class CircleDrawer
		: public ComponentBase
	{
	public:

		CircleDrawer(
			float radius,					// �^�~�̔��a
			const Vector2& localPosition,	// �^�~�̃��[�J�����W
			float lineThickness,			// �^�~�̐��̑���
			bool isFill,					// �h��Ԃ��t���O
			const Color& circleColor,		// �^�~�̕`��F
			float drawPriority,				// �`��D��x
			BlendMode blendMode,			// �`��̃u�����h���@�̎��
			float blendParam,				// �`��̃u�����h�Ɏg�p����l
			bool useAntialiasing,			// �A���`�G�C���A�X�̎g�p�t���O
			int vertexNum					// �A���`�G�C���A�X���g�p���鎞�Ɏg���~���`��钸�_�̐�
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// �^�~�̔��a���擾
		float getRadius() const;
		// �^�~�̔��a���Đݒ�
		void setRadius(float radius);

		// �^�~�̃��[�J�����W���擾
		const Vector2& getLocalPosition() const;
		// �^�~�̃��[�J�����W���Đݒ�
		void setLocalPosition(const Vector2& localPosition);

		// �^�~�̐��̑������擾
		float getLineThickness() const;
		// �^�~�̐��̑������Đݒ�
		void setLineThickness(float lineThickness);

		// �h��Ԃ��t���O���擾
		bool getIsFill() const;
		// �h��Ԃ��t���O���Đݒ�
		void setIsFill(bool isFill);

		// �^�~�̕`��F���擾
		const Color& getCircleColor() const;
		// �^�~�̕`��F���Đݒ�
		void setCircleColor(const Color& circleColor);

		// �`��̃u�����h���@�̎�ނ��擾
		BlendMode getBlendMode() const;
		// �`��̃u�����h���@�̎�ނ��Đݒ�
		void setBlendMode(BlendMode blendMode);

		// �`��̃u�����h�Ɏg�p����l���擾
		float getBlendParam() const;
		// �`��̃u�����h�Ɏg�p����l���Đݒ�
		void setBlendParam(float blendParam);

		// �A���`�G�C���A�X�̎g�p�t���O���擾
		bool getUseAntialiasing() const;
		// �A���`�G�C���A�X�̎g�p�t���O���Đݒ�
		void setUseAntialiasing(bool useAntialiasing);

		// �A���`�G�C���A�X���g�p���鎞�Ɏg���~���`��钸�_�̐����擾
		int getVertexNum() const;
		// �A���`�G�C���A�X���g�p���鎞�Ɏg���~���`��钸�_�̐����Đݒ�
		void setVertexNum(int vertexNum);

		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		CfpPtr<Transform2D>m_transform2D;

		// �^�~�̔��a
		float m_radius;

		// �^�~�̃��[�J�����W
		Vector2 m_localPosition;

		// �^�~�̐��̑���
		float m_lineThickness;

		// �h��Ԃ��t���O
		bool m_isFill;

		// �^�~�̕`��F
		Color m_circleColor;

		// �`��̃u�����h���@�̎��
		BlendMode m_blendMode;

		// �`��̃u�����h�Ɏg�p����l
		float m_blendParam;

		// �A���`�G�C���A�X�̎g�p�t���O
		bool m_useAntialiasing;

		// �A���`�G�C���A�X���g�p���鎞�Ɏg���~���`��钸�_�̐�
		int m_vertexNum;

		// �����_�[�^�[�Q�b�g�ɕ`�悷�邩
		bool m_useRenderTarget{ false };

		// �`�悷�郌���_�[�^�[�Q�b�g��Id
		int m_renderTargetId{ -1 };
	};
}
#endif // !CIRCLE_DRAWER_H_