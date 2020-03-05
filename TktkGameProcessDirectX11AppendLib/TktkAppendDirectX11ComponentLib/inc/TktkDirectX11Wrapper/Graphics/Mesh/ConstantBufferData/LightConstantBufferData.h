#ifndef LIGHT_CONSTANT_BUFFER_DATA_H_
#define LIGHT_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>

namespace tktk
{
	// ライト情報の定数バッファの形式
	struct LightConstantBufferData
	{
		Color lightAmbientColor;
		Color lightDiffuseColor;
		Color lightSpecularColor;
		Vector3 lightPosition;
		float pad[1];
	};
}
#endif // !LIGHT_CONSTANT_BUFFER_DATA_H_