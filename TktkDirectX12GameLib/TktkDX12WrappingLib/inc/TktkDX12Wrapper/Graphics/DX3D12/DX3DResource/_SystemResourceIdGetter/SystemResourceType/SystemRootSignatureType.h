#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemRootSignatureNum = 9U;

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