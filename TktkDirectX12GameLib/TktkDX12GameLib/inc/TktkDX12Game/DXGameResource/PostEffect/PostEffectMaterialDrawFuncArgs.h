#ifndef POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
#define POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_

namespace tktk
{
	struct PostEffectMaterialDrawFuncArgs
	{
		unsigned int		viewportId;
		unsigned int		scissorRectId;
		unsigned int		rtvDescriptorHeapId;
	};
}
#endif // !POST_EFFECT_MATERIAL_DRAW_FUNC_ARGS_H_
