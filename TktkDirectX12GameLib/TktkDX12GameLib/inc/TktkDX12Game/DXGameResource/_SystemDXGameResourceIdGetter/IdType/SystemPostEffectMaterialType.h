#ifndef SYSTEM_POST_EFFECT_MATERIAL_TYPE_H_
#define SYSTEM_POST_EFFECT_MATERIAL_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���ʏ�̃|�X�g�G�t�F�N�g�}�e���A���̐�
	constexpr unsigned int SystemPostEffectMaterialNum = 6U;

	// �V�X�e���Ŏg�p���Ă���ʏ�̃|�X�g�G�t�F�N�g�}�e���A���̎��
	enum class SystemPostEffectMaterialType
	{
		Monochrome	= 0U,
		Negative,
		SimpleBlur,
		Embossing,
		Sharpness,
		GlassFilter 
	};
}
#endif // !SYSTEM_POST_EFFECT_MATERIAL_TYPE_H_