#ifndef SYSTEM_PIPELINE_STATE_TYPE_H_
#define SYSTEM_PIPELINE_STATE_TYPE_H_

namespace tktk
{
	constexpr unsigned int SystemPipeLineStateNum = 8U;

	enum class SystemPipeLineStateType
	{
		PostEffectMonochrome = 0U,
		PostEffectNegative,
		PostEffectSimpleBlur,
		PostEffectEmbossing,
		PostEffectSharpness,
		PostEffectGlassFilter,
		Sprite,
		BasicMesh
	};
}
#endif // !SYSTEM_PIPELINE_STATE_TYPE_H_