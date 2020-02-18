#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshDrawerSetupper.h"

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/MeshConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/PbrMeshConstantBufferData.h"

namespace tktk
{
	void MeshDrawerSetupper::setUp(
		const std::string & basicPixelShaderFileName,
		const std::string & basicVertexShaderFileName,
		const std::string & pbrPixelShaderFileName,
		const std::string & pbrVertexShaderFileName,
		const std::string & iblMeshPixelShaderFileName,
		const std::string & iblMeshVertexShaderFileName,
		const std::string & pbrIblPixelShaderFileName,
		const std::string & pbrIblVertexShaderFileName
	)
	{
		createMeshConstantBufferData();
		createPbrMeshConstantBufferData();
		
		PixelShaderManager::load(SYSTEM_PIXEL_SHADER_MESH, SYSTEM_CONSTANT_BUFFER_MESH, basicPixelShaderFileName);
		PixelShaderManager::load(SYSTEM_PIXEL_SHADER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PBR_MESH, pbrPixelShaderFileName);
		PixelShaderManager::load(SYSTEM_PIXEL_SHADER_IBL_MESH, SYSTEM_CONSTANT_BUFFER_PBR_MESH, iblMeshPixelShaderFileName);
		PixelShaderManager::load(SYSTEM_PIXEL_SHADER_PBR_IBL_MESH, SYSTEM_CONSTANT_BUFFER_MESH, pbrIblPixelShaderFileName);
		
		std::vector<D3D11_INPUT_ELEMENT_DESC> meshVertexLayout = std::vector<D3D11_INPUT_ELEMENT_DESC>({
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		});

		VertexShaderManager::load(SYSTEM_VERTEX_SHADER_MESH, SYSTEM_CONSTANT_BUFFER_MESH, basicVertexShaderFileName, meshVertexLayout);
		VertexShaderManager::load(SYSTEM_VERTEX_SHADER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PBR_MESH, pbrVertexShaderFileName, meshVertexLayout);
		VertexShaderManager::load(SYSTEM_VERTEX_SHADER_IBL_MESH, SYSTEM_CONSTANT_BUFFER_PBR_MESH, iblMeshVertexShaderFileName, meshVertexLayout);
		VertexShaderManager::load(SYSTEM_VERTEX_SHADER_PBR_IBL_MESH, SYSTEM_CONSTANT_BUFFER_MESH, pbrIblVertexShaderFileName, meshVertexLayout);
	}

	void MeshDrawerSetupper::createMeshConstantBufferData()
	{
		MeshConstantBufferData* meshConstantBufferData = new MeshConstantBufferData();
		ConstantBufferManager::create(SYSTEM_CONSTANT_BUFFER_MESH, meshConstantBufferData);

		unsigned int location = 0U;
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_worldMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_viewMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_projectionMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_boneMatrices, location);
		location += sizeof(Matrix4) * 256;
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_materialAmbientColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_materialDiffuseColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_materialSpecularColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_materialEmissionColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_materialShininess, location);
		location += sizeof(float) * 4;
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightAmbientColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightDiffuseColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightSpecularColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightPosition, location);
	}

	void MeshDrawerSetupper::createPbrMeshConstantBufferData()
	{
		PbrMeshConstantBufferData* pbrMeshConstantBufferData = new PbrMeshConstantBufferData();
		ConstantBufferManager::create(SYSTEM_CONSTANT_BUFFER_PBR_MESH, pbrMeshConstantBufferData);

		unsigned int location = 0U;
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_worldMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_viewMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_projectionMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_boneMatrices, location);
		location += sizeof(Matrix4) * 256;
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_albedoColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_metallic, location);
		location += sizeof(float);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_smoothness, location);
		location += sizeof(float) * 3;
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightAmbientColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightDiffuseColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightSpecularColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SYSTEM_CONSTANT_BUFFER_PBR_MESH, SYSTEM_CONSTANT_BUFFER_PARAM_lightPosition, location);
	}
}