#ifndef POST_EFFECT_MATERIAL_INIT_PARAM_H_
#define POST_EFFECT_MATERIAL_INIT_PARAM_H_

namespace tktk
{
	// �|�X�g�G�t�F�N�g�̃}�e���A������鎞�ɕK�v�ȏ��
	struct PostEffectMaterialInitParam
	{
		// �g�p����p�C�v���C���X�e�[�gID
		unsigned int usePipeLineStateId;

		// �g�p����f�B�X�N���v�^�q�[�vID
		unsigned int useDescriptorHeapId;
	};
}
#endif // !POST_EFFECT_MATERIAL_INIT_PARAM_H_