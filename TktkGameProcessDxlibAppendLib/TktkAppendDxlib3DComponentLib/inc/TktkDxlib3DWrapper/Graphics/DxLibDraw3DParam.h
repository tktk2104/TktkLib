#ifndef DXLIB_DRAW_3D_PARAM_H_
#define DXLIB_DRAW_3D_PARAM_H_

#include <TktkMath/Matrix4.h>
#include <TktkDxlib2DWrapper/Graphics/BlendMode.h>

namespace tktk
{
	struct DxLibDraw3DParam
	{
		explicit DxLibDraw3DParam(float drawPriority);

		DxLibDraw3DParam(
			float drawPriority,
			const Matrix4& localMat,
			BlendMode blendMode,
			float blendParam,
			bool useLight,
			bool writeZBuffer,
			int renderTargetId,
			bool createShadow,
			float shadowCreatorPriority
		);

		// �`��D��x�i�萔�j
		const float drawPriority;

		// �`��ʒu�̃��[�J�����W
		Matrix4 localMat{ Matrix4::identity };

		// �`��̃u�����h���@�̎��
		BlendMode blendMode{ BlendMode::None };

		// �`��̃u�����h�Ɏg�p����l
		float blendParam{ 1.0f };

		// ���C�g���g�p���ĕ`����s�����H
		bool useLight{ true };

		// Z�o�b�t�@���g�p���ĕ`����s�����H
		bool writeZBuffer{ true };

		// �`�悷�郌���_�[�^�[�Q�b�g��Id�i-1�ŉ�ʂɒ��ڕ`��j
		int renderTargetId{ -1 };

		// �e�𐶐����邩�H
		bool createShadow{ false };

		// �V���h�E�}�b�v�̐������s���`��D��x
		float shadowCreatorPriority{ 100 };
	};
}
#endif // !DXLIB_DRAW_3D_PARAM_H_
