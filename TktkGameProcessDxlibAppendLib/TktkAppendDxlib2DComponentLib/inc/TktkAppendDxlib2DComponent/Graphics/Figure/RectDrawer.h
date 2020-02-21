#ifndef RECT_DRAWER_H_
#define RECT_DRAWER_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// �����`��`�悷��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class RectDrawer
		: public ComponentBase
	{
	public:

		RectDrawer(
			const Vector2& rectSize,		// �����`�̑傫��
			const Vector2& localPosition,	// �����`�̃��[�J�����W
			float lineThickness,			// �����`�̕ӂ̑���
			bool isFill,					// �h��Ԃ��t���O
			const Color& rectColor,			// �����`�̕`��F
			float drawPriority,				// �`��D��x
			BlendMode blendMode,			// �`��̃u�����h���@�̎��
			float blendParam,				// �`��̃u�����h�Ɏg�p����l
			bool useAntialiasing			// �A���`�G�C���A�X�̎g�p�t���O
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// �����`�̑傫�����擾
		const Vector2& getRectSize() const;
		// �����`�̑傫�����Đݒ�
		void setRectSize(const Vector2& rectSize);

		// �����`�̃��[�J�����W���擾
		const Vector2& getLocalPosition() const;
		// �����`�̃��[�J�����W���Đݒ�
		void setLocalPosition(const Vector2& localPosition);

		// �����`�̕ӂ̑������擾
		float getLineThickness() const;
		// �����`�̕ӂ̑������Đݒ�
		void setLineThickness(float lineThickness);

		// �h��Ԃ��t���O���擾
		bool getIsFill() const;
		// �h��Ԃ��t���O���Đݒ�
		void setIsFill(bool isFill);

		// �����`�̕`��F���擾
		const Color& getRectColor() const;
		// �����`�̕`��F���Đݒ�
		void setRectColor(const Color& rectColor);

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

		// �w�肵�������_�[�^�[�Q�b�g�ɕ`�悷��
		void useRenderTarget(int renderTargetId);
		// �����_�[�^�[�Q�b�g���g�p�����ɕ`�悷��
		void unUseRenderTarget();

	private:

		// ���g�̂Q�������W�R���|�[�l���g
		CfpPtr<Transform2D> m_transform2D;

		// �����`�̑傫��
		Vector2 m_rectSize;

		// �����`�̃��[�J�����W
		Vector2 m_localPosition;

		// �����`�̕ӂ̑���
		float m_lineThickness;

		// �h��Ԃ��t���O
		bool m_isFill;

		// �����`�̕`��F
		Color m_rectColor;

		// �`��̃u�����h���@�̎��
		BlendMode m_blendMode;

		// �`��̃u�����h�Ɏg�p����l
		float m_blendParam;

		// �A���`�G�C���A�X�̎g�p�t���O
		bool m_useAntialiasing;

		// �����_�[�^�[�Q�b�g�ɕ`�悷�邩
		bool m_useRenderTarget{ false };

		// �`�悷�郌���_�[�^�[�Q�b�g��Id
		int m_renderTargetId{ -1 };
	};
}
#endif // !RECT_DRAWER_H_