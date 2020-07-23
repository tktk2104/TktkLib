#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	// システムで使用しているパイプラインステートの数
	constexpr unsigned int SystemPipeLineStateNum = 9U;

	// システムで使用しているパイプラインステートの種類
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