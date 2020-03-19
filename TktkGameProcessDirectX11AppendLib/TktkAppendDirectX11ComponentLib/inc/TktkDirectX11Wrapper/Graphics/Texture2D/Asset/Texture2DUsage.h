#ifndef TEXTURE_2D_USAGE_H_
#define TEXTURE_2D_USAGE_H_

namespace tktk
{
	enum class Texture2DUsage
	{
		Default		= 0,
		Immutable	= 1,
		Dynamic		= 2,
		Staging		= 3
	};
}
#endif // !TEXTURE_2D_USAGE_H_