#ifndef MATERIAL_CONSTANT_BUFFER_DATA_H_
#define MATERIAL_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>

namespace tktk
{
	// マテリアル情報の定数バッファの形式
	struct MaterialConstantBufferData
	{
		Color materialAmbientColor;
		Color materialDiffuseColor;
		Color materialSpecularColor;
		Color materialEmissionColor;
		float materialShininess;
		float pad[3];
	};
}
#endif // !MATERIAL_CONSTANT_BUFFER_DATA_H_