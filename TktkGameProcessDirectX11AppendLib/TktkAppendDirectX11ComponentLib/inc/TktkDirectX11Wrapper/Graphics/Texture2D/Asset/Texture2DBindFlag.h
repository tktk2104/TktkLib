#ifndef TEXTURE_2D_BIND_FLAG_H_
#define TEXTURE_2D_BIND_FLAG_H_

namespace tktk
{
	enum class Texture2DBindFlag
	{
		ShaderResource	= 8U,
		RenderTarget	= 32U,
	};
}
#endif // !TEXTURE_2D_BIND_FLAG_H_