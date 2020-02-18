#ifndef SHADER_TYPE_H_
#define SHADER_TYPE_H_

namespace tktk
{
	enum ShaderType
	{
		SHADER_TYPE_VERTEX		= 0,
		SHADER_TYPE_PIXEL		= 1,
		SHADER_TYPE_GEOMETRY	= 2,
		SHADER_TYPE_COMPUTE		= 3,
		SHADER_TYPE_DOMAIN		= 4,
		SHADER_TYPE_HULL		= 5,
	};
}
#endif // !SHADER_TYPE_H_