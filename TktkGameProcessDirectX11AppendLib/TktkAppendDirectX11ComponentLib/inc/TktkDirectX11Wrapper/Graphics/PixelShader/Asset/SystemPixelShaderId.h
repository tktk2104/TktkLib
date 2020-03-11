#ifndef SYSTEM_PIXEL_SHADER_ID_H_
#define SYSTEM_PIXEL_SHADER_ID_H_

namespace tktk
{
	enum class SystemPixelShaderId
	{
		Line2D		= -100,
		Sprite		= -200,
		Mesh		= -300,
		PbrMesh		= -400,
		IblMesh		= -500,
		PbrIblMesh	= -600,
	};
}
#endif // !SYSTEM_PIXEL_SHADER_ID_H_