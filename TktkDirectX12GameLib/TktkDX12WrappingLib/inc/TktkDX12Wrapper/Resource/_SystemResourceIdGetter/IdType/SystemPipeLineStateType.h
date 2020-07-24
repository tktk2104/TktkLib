#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���p�C�v���C���X�e�[�g�̐�
	constexpr unsigned int SystemPipeLineStateNum = 9U;

	// �V�X�e���Ŏg�p���Ă���p�C�v���C���X�e�[�g�̎��
	enum class SystemPipeLineStateType
	{
		PostEffectMonochrome = 0U,
		PostEffectNegative,
		PostEffectSimpleBlur,
		PostEffectEmbossing,
		PostEffectSharpness,
		PostEffectGlassFilter,
		ShadowMap,
		Sprite,
		BasicMesh
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_