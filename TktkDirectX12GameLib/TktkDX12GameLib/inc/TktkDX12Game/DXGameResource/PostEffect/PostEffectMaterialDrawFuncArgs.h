#ifndef POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_

namespace tktk
{
	// �|�X�g�G�t�F�N�g��`�悷�鎞�ɕK�v�Ȉ���
	struct PostEffectMaterialDrawFuncArgs
	{
		// �g�p����r���[�|�[�gID
		unsigned int		viewportId;

		// �g�p����V�U�[��`ID
		unsigned int		scissorRectId;

		// �g�p���郌���_�[�^�[�Q�b�g�p�f�B�X�N���v�^�q�[�vID
		unsigned int		rtvDescriptorHeapId;
	};
}
#endif // !POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
