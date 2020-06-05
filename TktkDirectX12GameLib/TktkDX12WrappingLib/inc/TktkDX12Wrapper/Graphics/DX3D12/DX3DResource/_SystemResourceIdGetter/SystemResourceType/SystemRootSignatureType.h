#ifndef SYSTEM_ROOT_SIGNATURE_TYPE_H_
#define SYSTEM_ROOT_SIGNATURE_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemRootSignatureNum = 8U;

	enum class SystemRootSignatureType
	{
		PostEffectMonochrome	= 0U,
		PostEffectNegative,
		PostEffectSimpleBlur,
		PostEffectEmbossing,
		PostEffectSharpness,
		PostEffectGlassFilter,
		Sprite,
		BasicMesh
	};
}
#endif // !SYSTEM_ROOT_SIGNATURE_TYPE_H_