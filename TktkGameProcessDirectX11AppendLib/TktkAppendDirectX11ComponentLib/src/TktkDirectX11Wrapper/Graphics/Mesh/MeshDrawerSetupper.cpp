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

		PixelShaderManager::load(SystemPixelShaderId::Mesh,			SystemConstantBufferId::Mesh,		basicPixelShaderFileName);
		PixelShaderManager::load(SystemPixelShaderId::PbrMesh,		SystemConstantBufferId::PbrMesh,	pbrPixelShaderFileName);
		PixelShaderManager::load(SystemPixelShaderId::IblMesh,		SystemConstantBufferId::PbrMesh,	iblMeshPixelShaderFileName);
		PixelShaderManager::load(SystemPixelShaderId::PbrIblMesh,	SystemConstantBufferId::Mesh,		pbrIblPixelShaderFileName);

		std::vector<D3D11_INPUT_ELEMENT_DESC> meshVertexLayout = std::vector<D3D11_INPUT_ELEMENT_DESC>({
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			});

		VertexShaderManager::load(SystemVertexShaderId::Mesh,		SystemConstantBufferId::Mesh,		basicVertexShaderFileName,		meshVertexLayout);
		VertexShaderManager::load(SystemVertexShaderId::PbrMesh,	SystemConstantBufferId::PbrMesh,	pbrVertexShaderFileName,		meshVertexLayout);
		VertexShaderManager::load(SystemVertexShaderId::IblMesh,	SystemConstantBufferId::PbrMesh,	iblMeshVertexShaderFileName,	meshVertexLayout);
		VertexShaderManager::load(SystemVertexShaderId::PbrIblMesh, SystemConstantBufferId::Mesh,		pbrIblVertexShaderFileName,		meshVertexLayout);
	}

	void MeshDrawerSetupper::createMeshConstantBufferData()
	{
		MeshConstantBufferData* meshConstantBufferData = new MeshConstantBufferData();
		ConstantBufferManager::create(SystemConstantBufferId::Mesh, meshConstantBufferData);

		unsigned int location = 0U;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::worldMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::viewMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::projectionMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::boneMatrices, location);
		location += sizeof(Matrix4) * 256;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::materialAmbientColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::materialDiffuseColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::materialSpecularColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::materialEmissionColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::materialShininess, location);
		location += sizeof(float) * 4;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::lightAmbientColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::lightDiffuseColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::lightSpecularColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::Mesh, SystemConstantBufferParamLocationType::lightPosition, location);
	}

	void MeshDrawerSetupper::createPbrMeshConstantBufferData()
	{
		PbrMeshConstantBufferData* pbrMeshConstantBufferData = new PbrMeshConstantBufferData();
		ConstantBufferManager::create(SystemConstantBufferId::PbrMesh, pbrMeshConstantBufferData);

		unsigned int location = 0U;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::worldMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::viewMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::projectionMatrix, location);
		location += sizeof(Matrix4);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::boneMatrices, location);
		location += sizeof(Matrix4) * 256;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::albedoColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::metallic, location);
		location += sizeof(float);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::smoothness, location);
		location += sizeof(float) * 3;
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::lightAmbientColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::lightDiffuseColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::lightSpecularColor, location);
		location += sizeof(Color);
		ConstantBufferManager::addParamLocation(SystemConstantBufferId::PbrMesh, SystemConstantBufferParamLocationType::lightPosition, location);
	}
}