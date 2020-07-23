#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă��郋�[�g�V�O�l�`���̐�
	constexpr unsigned int SystemRootSignatureNum = 9U;

	// �V�X�e���Ŏg�p���Ă��郋�[�g�V�O�l�`���̎��
	enum class SystemRootSignatureType
	{
		PostEffectMonochrome	= 0U,
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
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_