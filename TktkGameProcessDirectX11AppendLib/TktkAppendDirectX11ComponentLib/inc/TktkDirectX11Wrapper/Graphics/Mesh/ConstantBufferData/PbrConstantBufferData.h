#ifndef PBR_CONSTANT_BUFFER_DATA_H_
#define PBR_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>

namespace tktk
{
	// 物理ベースレンダリングで使用する定数バッファ
	struct PbrConstantBufferData
	{
		Color albedoColor;
		float metallic;
		float smoothness;
		float pad0[2];
	}; 
}
#endif // !PBR_CONSTANT_BUFFER_DATA_H_