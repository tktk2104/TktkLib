#include "TktkDxlib3DWrapper/Graphics/DxLibDraw3DParam.h"

namespace tktk
{
	DxLibDraw3DParam::DxLibDraw3DParam(float drawPriority)
		: drawPriority(drawPriority)
	{
	}

	DxLibDraw3DParam::DxLibDraw3DParam(
		float drawPriority,
		const Matrix4 & localMat,
		BlendMode blendMode,
		float blendParam,
		bool useLight,
		bool writeZBuffer,
		int renderTargetId,
		bool createShadow,
		float shadowCreatorPriority
	)
		: drawPriority(drawPriority)
		, localMat(localMat)
		, blendMode(blendMode)
		, blendParam(blendParam)
		, useLight(useLight)
		, writeZBuffer(writeZBuffer)
		, renderTargetId(renderTargetId)
		, createShadow(createShadow)
		, shadowCreatorPriority(shadowCreatorPriority)
	{
	}
}