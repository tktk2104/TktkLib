#ifndef SYSTEM_VERTEX_SHADER_ID_H_
#define SYSTEM_VERTEX_SHADER_ID_H_

namespace tktk
{
	enum class SystemVertexShaderId
	{
		Line2D			= -100,
		Sprite			= -200,
		Mesh			= -300,
		MonoColorMesh	= -400,
		PbrMesh			= -500,
		IblMesh			= -600,
		PbrIblMesh		= -700,
	};
}
#endif // !SYSTEM_VERTEX_SHADER_ID_H_