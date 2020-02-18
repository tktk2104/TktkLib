#ifndef LINE_DRAWER_H_
#define LINE_DRAWER_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// ������`�悷��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class LineDrawer
		: public ComponentBase
	{
	public:

		LineDrawer(
			const Vector2& relativeFirstPos,	// ���g�̍��W���猩�������̂P�ڂ̍��W
			const Vector2& relativeSecondPos,	// ���g�̍��W���猩�������̂Q�ڂ̍��W
			float lineThickness,				// �����̑���
			const Color& lineColor,				// �����̕`��F
			float drawPriority,					// �`��D��x
			BlendMode blendMode,				// �`��̃u�����h���@�̎��
			float blendParam,					// �`��̃u�����h�Ɏg�p����l
			bool useAntialiasing				// �A���`�G�C���A�X�̎g�p�t���O
		);

	public:

		// <PolymorphismFunc>
		void start();
		void draw() const;

	public:

		// ���g�̍��W���猩�������̂P�ڂ̍��W���擾
		const Vector2& getRelativeFirstPos() const;
		// ���g�̍��W���猩�������̂P�ڂ̍��W���Đݒ�
		void setRelativeFirstPos(const Vector2& relativeFirstPos);

		// ���g�̍��W���猩�������̂Q�ڂ̍��W���擾
		const Vector2& getRelativeSecondPos() const;
		// ���g�̍��W���猩�������̂Q�ڂ̍��W���Đݒ�
		void setRelativeSecondPos(const Vector2& relativeSecondPos);

		// �����̑������擾
		float getLineThickness() const;
		// �����̑������Đݒ�
		void setLineThickness(float lineThickness);

		// �����̕`��F���擾
		const Color& getLineColor() const;
		// �����̕`��F���Đݒ�
		void setLineColor(const Color& lineColor);

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
		std::weak_ptr<Transform2D> m_transform2D;

		// ���g�̍��W���猩�������̂P�ڂ̍��W
		Vector2 m_relativeFirstPos;

		// ���g�̍��W���猩�������̂Q�ڂ̍��W
		Vector2 m_relativeSecondPos;

		// �����̑���
		float m_lineThickness;

		// �����̕`��F
		Color m_lineColor;

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
#endif // !LINE_DRAWER_H_