#ifndef PBR_MESH_CONSTANT_BUFFER_DATA_H_
#define PBR_MESH_CONSTANT_BUFFER_DATA_H_

#include <TktkMath/Color.h>
#include <TktkMath/Vector3.h>
#include <TktkMath/Matrix4.h>

namespace tktk
{
	struct PbrMeshConstantBufferData
	{
		Matrix4 world;
		Matrix4 view;
		Matrix4 projection;
		Matrix4 boneMatrices[256];

		Color albedoColor;
		float metallic;
		float smoothness;
		float pad0[2];

		Color lightAmbient;
		Color lightDiffuse;
		Color lightSpecular;
		Vector3 lightPosition;
		float pad1[1];
	}; 
}
#endif // !PBR_MESH_CONSTANT_BUFFER_DATA_H_