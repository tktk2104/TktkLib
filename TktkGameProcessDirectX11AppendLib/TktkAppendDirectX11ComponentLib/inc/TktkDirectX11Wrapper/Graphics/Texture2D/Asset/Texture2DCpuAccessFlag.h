#ifndef TEXTURE_2D_CPU_ACCESS_FLAG_H_
#define TEXTURE_2D_CPU_ACCESS_FLAG_H_

namespace tktk
{
	enum class Texture2DCpuAccessFlag
	{
		Not				= 0,
		Write			= 0x10000L,
		Reade			= 0x20000L,
		WriteAndReade	= 0x10000L | 0x20000L,
	};
}
#endif // !TEXTURE_2D_CPU_ACCESS_FLAG_H_