#ifndef SYSTEM_CONSTANT_BUFFER_ID_H_
#define SYSTEM_CONSTANT_BUFFER_ID_H_

namespace tktk
{
	enum class SystemConstantBufferId
	{
		Line2DVertex	= -100,
		Line2DPixel		= -200,
		Sprite			= -300,
		Mesh			= -400,
		Light			= -500,
		Material		= -600,
		Pbr				= -700,
	};
}
#endif // !SYSTEM_CONSTANT_BUFFER_ID_H_