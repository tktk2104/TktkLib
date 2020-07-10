#ifndef SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_
#define SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_

#include <TktkMath/Structs/Matrix3.h>

namespace tktk
{
	// �X�v���C�g�̃}�e���A����`�悷�鎞�ɕK�v�Ȉ���
	struct SpriteMaterialDrawFuncArgs
	{
		// �g�p����r���[�|�[�gID
		unsigned int		viewportId;

		// �g�p����V�U�[��`ID
		unsigned int		scissorRectId;

		// �g�p���郌���_�[�^�[�Q�b�g�p�̃f�B�X�N���v�^�q�[�vID
		unsigned int		rtvDescriptorHeapId;

		// ���[���h�s��
		tktkMath::Matrix3	worldMatrix;
	};
}
#endif // !SPRITE_MATERIAL_DRAW_FUNC_ARGS_H_