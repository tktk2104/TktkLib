#ifndef SYSTEM_PIXEL_SHADER_ID_H_
#define SYSTEM_PIXEL_SHADER_ID_H_

namespace tktk
{
	enum class SystemPixelShaderId
	{
		Sprite		= -100,
		Mesh		= -200,
		PbrMesh		= -300,
		IblMesh		= -400,
		PbrIblMesh	= -500,
	};
}
#endif // !SYSTEM_PIXEL_SHADER_ID_H_