#ifndef SYSTEM_TEXTURE2D_ID_H_
#define SYSTEM_TEXTURE2D_ID_H_

namespace tktk
{
	enum class SystemTexture2DId
	{
		whiteShaderRes		= -100,
		redShaderRes		= -200,
		greenShaderRes		= -300,
		blueShaderRes		= -400,
		blackShaderRes		= -500,
		maxAlphaShaderRes	= -600,
		minAlphaShaderRes	= -700,

		// -65536
		fontUseResStart		= (~0x00010000 + 1),
		// -1048576
		fontUseResEnd		= (~0x00100000 + 1),

		// -1048577Å`
		materialLoadResStart= fontUseResEnd - 1,
	};
}
#endif // !SYSTEM_TEXTURE2D_ID_H_
