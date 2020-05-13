#ifndef DX3D_BASE_OBJECTS_INIT_PARAM_H_
#define DX3D_BASE_OBJECTS_INIT_PARAM_H_

namespace tktk
{
	struct DX3DBaseObjectsInitParam
	{
		unsigned int viewPortNum;
		unsigned int scissorRectNum;
		unsigned int vertexBufferNum;
		unsigned int indexBufferNum;
		unsigned int graphicsPipeLineNum;
		unsigned int rootSignatureNum;
		unsigned int basicDescriptorHeapNum;
		unsigned int rtvDescriptorHeapNum;
		unsigned int dsvDescriptorHeapNum;
		unsigned int textureBufferNum;
		unsigned int constantBufferNum;
		unsigned int renderTargetBufferNum;
		unsigned int backBufferNum;
		unsigned int depthStencilBufferNum;

		unsigned int spriteNum;
		unsigned int basicMeshNum;
		unsigned int basicMeshMaterialNum;
	};
}
#endif // !DX3D_BASE_OBJECTS_INIT_PARAM_H_