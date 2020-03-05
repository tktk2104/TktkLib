#ifndef MATERIAL_CONSTANT_BUFFER_DATA_H_
#define MATERIAL_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>

namespace tktk
{
	// �}�e���A�����̒萔�o�b�t�@�̌`��
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