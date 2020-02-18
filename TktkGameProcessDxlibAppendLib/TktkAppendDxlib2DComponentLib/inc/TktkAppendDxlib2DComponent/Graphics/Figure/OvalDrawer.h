#ifndef OVAL_DRAWER_H_
#define OVAL_DRAWER_H_

#include <memory>
#include <TktkMath/Color.h>
#include <TktkMath/Vector2.h>
#include <TktkComponentFramework/Component/ComponentBase.h>
#include <TktkAppend2DComponent/Transform2D.h>
#include "../../../TktkDxlib2DWrapper/Graphics/BlendMode.h"

namespace tktk
{
	// �ȉ~��`�悷��R���|�[�l���g
	// �y�O��R���|�[�l���g�FTransform2D�z
	class OvalDrawer
		: public ComponentBase
	{
	public:

		OvalDrawer(
			const Vector2& ovalSize,		// �ȉ~�̑傫��
			const Vector2& localPosition,	// �ȉ~�̃��[�J�����W
			float lineThickness,			// �ȉ~�̐��̑���
			bool isFill,					// �h��Ԃ��t���O
			const Color& ovalColor,			// �ȉ~�̕`��F
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

		// �ȉ~�̑傫�����擾
		const Vector2& getOvalSize() const;
		// �ȉ~�̑傫�����Đݒ�
		void setOvalSize(const Vector2& ovalSize);

		// �ȉ~�̃��[�J�����W���擾
		const Vector2& getLocalPosition() const;
		// �ȉ~�̃��[�J�����W���Đݒ�
		void setLocalPosition(const Vector2& localPosition);

		// �h��Ԃ��t���O���擾
		bool getIsFill() const;
		// �h��Ԃ��t���O���Đݒ�
		void setIsFill(bool isFill);

		// �ȉ~�̕`��F���擾
		const Color& getOvalColor() const;
		// �ȉ~�̕`��F���Đݒ�
		void setOvalColor(const Color& ovalColor);

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
		std::weak_ptr<Transform2D> m_transform2D;

		// �ȉ~�̑傫��
		Vector2 m_ovalSize;

		// �ȉ~�̃��[�J�����W
		Vector2 m_localPosition;

		// �^�~�̐��̑���
		float m_lineThickness;

		// �h��Ԃ��t���O
		bool m_isFill;

		// �ȉ~�̕`��F
		Color m_ovalColor;

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
#endif // !OVAL_DRAWER_H_