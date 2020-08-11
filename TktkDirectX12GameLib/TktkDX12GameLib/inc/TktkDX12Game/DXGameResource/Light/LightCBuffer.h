#ifndef LIGHT_CBUFFER_H_
#define LIGHT_CBUFFER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	// ���C�g���̒萔�o�b�t�@
	struct LightCBuffer
	{
		// ���C�g�̊���
		tktkMath::Color		lightAmbient	{ 0.25f, 1.0f };

		// ���C�g�̊g�U���ˌ�
		tktkMath::Color		lightDiffuse	{ 0.25f, 1.0f };

		// ���C�g�̋��ʔ��ˌ�
		tktkMath::Color		lightSpeqular	{ 0.25f, 1.0f };

		// ���C�g�̍��W
		tktkMath::Vector3	lightPosition	{ tktkMath::Vector3_v::zero };

		// �p�f�B���O
		float				lightDataPad	{ 0.0f };
	};
}
#endif // !LIGHT_CBUFFER_H_
