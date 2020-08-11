#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���p�C�v���C���X�e�[�g�̐�
	constexpr unsigned int SystemPipeLineStateNum = 13U;

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
		Line2D,
		BasicMesh,
		BasicMeshWireFrame,
		BasicMonoColorMesh,
		BasicMonoColorMeshWireFrame
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_