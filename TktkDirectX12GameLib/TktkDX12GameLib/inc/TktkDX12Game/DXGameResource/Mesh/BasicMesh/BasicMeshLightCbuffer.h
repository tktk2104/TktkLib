#ifndef BASIC_MESH_LIGHT_CBUFFER_H_
#define BASIC_MESH_LIGHT_CBUFFER_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// �ʏ탁�b�V���̃��C�e�B���O�̒萔�o�b�t�@
	struct BasicMeshLightCbuffer
	{
		// ���C�g�̊���
		tktkMath::Color		lightAmbient	{ 0.25f, 1.0f };

		// ���C�g�̊g�U���ˌ�
		tktkMath::Color		lightDiffuse	{ 0.25f, 1.0f };

		// ���C�g�̋��ʔ��ˌ�
		tktkMath::Color		lightSpeqular	{ 0.25f, 1.0f };

		// ���C�g�̍��W
		tktkMath::Vector3	lightPosition	{ tktkMath::vec3Zero };

		// �p�f�B���O
		float				lightDataPad	{ 0.0f };
	};
}
#endif // !BASIC_MESH_LIGHT_CBUFFER_H_
