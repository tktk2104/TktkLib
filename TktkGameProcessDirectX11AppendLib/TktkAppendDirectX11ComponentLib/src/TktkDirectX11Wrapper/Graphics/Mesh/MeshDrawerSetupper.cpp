#include "TktkDirectX11Wrapper/Graphics/Mesh/MeshDrawerSetupper.h"

#include <TktkClassFuncProcessor/ProcessingClass/CfpPtr.h>
#include "TktkDirectX11Wrapper/Graphics/ConstantBuffer/ConstantBufferManager.h"
#include "TktkDirectX11Wrapper/Graphics/PixelShader/PixelShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/VertexShader/VertexShaderManager.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/MeshConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/LightConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/MaterialConstantBufferData.h"
#include "TktkDirectX11Wrapper/Graphics/Mesh/ConstantBufferData/PbrConstantBufferData.h"

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
		ConstantBufferManager::create(SystemConstantBufferId::Mesh, new MeshConstantBufferData());
		ConstantBufferManager::create(SystemConstantBufferId::Material, new MaterialConstantBufferData());
		ConstantBufferManager::create(SystemConstantBufferId::Light, new LightConstantBufferData());
		ConstantBufferManager::create(SystemConstantBufferId::Pbr, new PbrConstantBufferData());

		PixelShaderManager::load(
			basicPixelShaderFileName,
			SystemPixelShaderId::Mesh,
			SystemConstantBufferId::Material,
			SystemConstantBufferId::Light
		);
		PixelShaderManager::load(
			pbrPixelShaderFileName,
			SystemPixelShaderId::PbrMesh,
			SystemConstantBufferId::Pbr
		);
		PixelShaderManager::load(
			iblMeshPixelShaderFileName,
			SystemPixelShaderId::IblMesh,
			SystemConstantBufferId::Pbr
		);
		PixelShaderManager::load(
			pbrIblPixelShaderFileName,
			SystemPixelShaderId::PbrIblMesh
		);

		std::vector<D3D11_INPUT_ELEMENT_DESC> meshVertexLayout = std::vector<D3D11_INPUT_ELEMENT_DESC>({
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			});

		VertexShaderManager::load(
			SystemVertexShaderId::Mesh,
			basicVertexShaderFileName,
			meshVertexLayout,
			SystemConstantBufferId::Mesh,
			SystemConstantBufferId::Light
		);
		VertexShaderManager::load(
			SystemVertexShaderId::PbrMesh,
			pbrVertexShaderFileName,
			meshVertexLayout,
			SystemConstantBufferId::Mesh,
			SystemConstantBufferId::Light
		);
		VertexShaderManager::load(
			SystemVertexShaderId::IblMesh,
			iblMeshVertexShaderFileName,
			meshVertexLayout,
			SystemConstantBufferId::Mesh,
			SystemConstantBufferId::Light
		);
		VertexShaderManager::load(
			SystemVertexShaderId::PbrIblMesh,
			pbrIblVertexShaderFileName,
			meshVertexLayout,
			SystemConstantBufferId::Mesh,
			SystemConstantBufferId::Light
		);
	}
}