#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Material/BasicMeshMaterial.h"

#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMeshMaterialCbuffer.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	BasicMeshMaterial::BasicMeshMaterial(const ShaderFilePaths& shaderFilePaths, const std::string& monoColorShaderPsFilePath, unsigned int basicMeshMaterialNum)
		: m_basicMeshMaterialArray(basicMeshMaterialNum)
	{
		createRootSignature();
		createGraphicsPipeLineState(shaderFilePaths, monoColorShaderPsFilePath);

		// 通常メッシュマテリアル情報と単色塗りつぶし描画色の定数バッファを作る
		DX12GameManager::createCBuffer(DX12GameManager::getSystemId(SystemCBufferType::BasicMeshMaterial),	BasicMeshMaterialCbuffer());
		DX12GameManager::createCBuffer(DX12GameManager::getSystemId(SystemCBufferType::BasicMonoColorMeshCbuffer), BasicMonoColorMeshCbuffer());
	}

	void BasicMeshMaterial::create(unsigned int id, const BasicMeshMaterialInitParam& initParam)
	{
		m_basicMeshMaterialArray.emplaceAt(id, initParam);
	}

	void BasicMeshMaterial::copy(unsigned int id, unsigned int originalId)
	{
		m_basicMeshMaterialArray.emplaceAt(id, m_basicMeshMaterialArray.at(originalId));
	}

	void BasicMeshMaterial::setMaterialData(unsigned int id) const
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.at(id);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->setMaterialData();
	}

	void BasicMeshMaterial::addAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, void* dataTopPos)
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.at(id);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->addAppendParam(cbufferId, dataSize, dataTopPos);
	}

	void BasicMeshMaterial::updateAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos)
	{
		auto basicMeshPtr = m_basicMeshMaterialArray.at(id);

#ifdef _DEBUG
		if (basicMeshPtr == nullptr)
		{
			throw std::runtime_error("not create basicMeshMaterial");
		}
#endif // _DEBUG

		basicMeshPtr->updateAppendParam(cbufferId, dataSize, dataTopPos);
	}

	void BasicMeshMaterial::createRootSignature() const
	{
		// デフォルトのルートシグネチャを作る
		{
			RootSignatureInitParam initParam{};
			initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			initParam.rootParamArray.resize(3U);
			{/* テクスチャ用のルートパラメータ */
				initParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.rootParamArray.at(0U).descriptorTable = {
					{ 2U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U }
				};
			}

			{/* 頂点シェーダー用の定数バッファ用のルートパラメータ */
				initParam.rootParamArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
				initParam.rootParamArray.at(1U).descriptorTable = {
					{ 5U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U }
				};
			}

			{/* ピクセルシェーダー用の定数バッファ用のルートパラメータ */
				initParam.rootParamArray.at(2U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.rootParamArray.at(2U).descriptorTable = {
					{ 2U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U }
				};
			}

			initParam.samplerDescArray.resize(2U);
			{/* サンプラーの設定 */
				initParam.samplerDescArray.at(0U).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.samplerDescArray.at(0U).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.samplerDescArray.at(0U).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
				initParam.samplerDescArray.at(0U).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
				initParam.samplerDescArray.at(0U).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
				initParam.samplerDescArray.at(0U).maxLod = D3D12_FLOAT32_MAX;
				initParam.samplerDescArray.at(0U).minLod = 0.0f;
				initParam.samplerDescArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.samplerDescArray.at(0U).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
				initParam.samplerDescArray.at(0U).shaderRegister = 0U;
			}
			{
				initParam.samplerDescArray.at(1U).addressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
				initParam.samplerDescArray.at(1U).addressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
				initParam.samplerDescArray.at(1U).addressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
				initParam.samplerDescArray.at(1U).bordercolor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
				initParam.samplerDescArray.at(1U).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
				initParam.samplerDescArray.at(1U).maxLod = D3D12_FLOAT32_MAX;
				initParam.samplerDescArray.at(1U).minLod = 0.0f;
				initParam.samplerDescArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.samplerDescArray.at(1U).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
				initParam.samplerDescArray.at(1U).shaderRegister = 1U;
			}
			DX12GameManager::createRootSignature(DX12GameManager::getSystemId(SystemRootSignatureType::BasicMesh), initParam);
		}

		// 単色のルートシグネチャを作る
		{
			RootSignatureInitParam initParam{};
			initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

			initParam.rootParamArray.resize(3U);
			{/* テクスチャ用のルートパラメータ */
				initParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.rootParamArray.at(0U).descriptorTable = {
					{ 1U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U }
				};
			}

			{/* 頂点シェーダー用の定数バッファ用のルートパラメータ */
				initParam.rootParamArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
				initParam.rootParamArray.at(1U).descriptorTable = {
					{ 5U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U }
				};
			}

			{/* ピクセルシェーダー用の定数バッファ用のルートパラメータ */
				initParam.rootParamArray.at(2U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.rootParamArray.at(2U).descriptorTable = {
					{ 3U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U }
				};
			}

			initParam.samplerDescArray.resize(1U);
			{/* サンプラーの設定 */
				initParam.samplerDescArray.at(0U).addressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
				initParam.samplerDescArray.at(0U).addressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
				initParam.samplerDescArray.at(0U).addressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
				initParam.samplerDescArray.at(0U).bordercolor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
				initParam.samplerDescArray.at(0U).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
				initParam.samplerDescArray.at(0U).maxLod = D3D12_FLOAT32_MAX;
				initParam.samplerDescArray.at(0U).minLod = 0.0f;
				initParam.samplerDescArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
				initParam.samplerDescArray.at(0U).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
				initParam.samplerDescArray.at(0U).shaderRegister = 0U;
			}
			DX12GameManager::createRootSignature(DX12GameManager::getSystemId(SystemRootSignatureType::BasicMonoColorMesh), initParam);
		}
	}

	void BasicMeshMaterial::createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths, const std::string& monoColorShaderPsFilePath) const
	{
		// デフォルトのパイプラインステートを作る
		{
			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable = false;
			renderTargetBlendDesc.LogicOpEnable = false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			PipeLineStateInitParam initParam{};
			initParam.rasterizerDesc.MultisampleEnable = false;
			initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
			initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
			initParam.rasterizerDesc.DepthClipEnable = true;
			initParam.blendDesc.AlphaToCoverageEnable = false;
			initParam.blendDesc.IndependentBlendEnable = false;
			initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
			initParam.inputLayoutArray = {
				{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };

			initParam.useDepth = true;
			initParam.writeDepth = true;
			initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
			initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::BasicMesh);

			DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMesh), initParam, shaderFilePaths);
		}
		
		// ワイヤーフレームのパイプラインステートを作る
		{
			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable = false;
			renderTargetBlendDesc.LogicOpEnable = false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			PipeLineStateInitParam initParam{};
			initParam.rasterizerDesc.MultisampleEnable = false;
			initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
			initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
			initParam.rasterizerDesc.DepthClipEnable = true;
			initParam.blendDesc.AlphaToCoverageEnable = false;
			initParam.blendDesc.IndependentBlendEnable = false;
			initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
			initParam.inputLayoutArray = {
				{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };

			initParam.useDepth = true;
			initParam.writeDepth = true;
			initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
			initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::BasicMesh);

			DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMeshWireFrame), initParam, shaderFilePaths);
		}

		// 単色のパイプラインステートを作る
		{
			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable = false;
			renderTargetBlendDesc.LogicOpEnable = false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			PipeLineStateInitParam initParam{};
			initParam.rasterizerDesc.MultisampleEnable = false;
			initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
			initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
			initParam.rasterizerDesc.DepthClipEnable = true;
			initParam.blendDesc.AlphaToCoverageEnable = false;
			initParam.blendDesc.IndependentBlendEnable = false;
			initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
			initParam.inputLayoutArray = {
				{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };

			initParam.useDepth = true;
			initParam.writeDepth = true;
			initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
			initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::BasicMonoColorMesh);

			ShaderFilePaths monoColorShaderFilePaths{};
			monoColorShaderFilePaths.vsFilePath = shaderFilePaths.vsFilePath;
			monoColorShaderFilePaths.psFilePath = monoColorShaderPsFilePath;

			DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMonoColorMesh), initParam, monoColorShaderFilePaths);
		}

		// 単色ワイヤーフレームのパイプラインステートを作る
		{
			D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
			renderTargetBlendDesc.BlendEnable = false;
			renderTargetBlendDesc.LogicOpEnable = false;
			renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

			PipeLineStateInitParam initParam{};
			initParam.rasterizerDesc.MultisampleEnable = false;
			initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
			initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
			initParam.rasterizerDesc.DepthClipEnable = true;
			initParam.blendDesc.AlphaToCoverageEnable = false;
			initParam.blendDesc.IndependentBlendEnable = false;
			initParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
			initParam.inputLayoutArray = {
				{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			};
			initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			initParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };

			initParam.useDepth = true;
			initParam.writeDepth = true;
			initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
			initParam.rootSignatureId = DX12GameManager::getSystemId(SystemRootSignatureType::BasicMonoColorMesh);

			ShaderFilePaths monoColorShaderFilePaths{};
			monoColorShaderFilePaths.vsFilePath = shaderFilePaths.vsFilePath;
			monoColorShaderFilePaths.psFilePath = monoColorShaderPsFilePath;

			DX12GameManager::createPipeLineState(DX12GameManager::getSystemId(SystemPipeLineStateType::BasicMonoColorMeshWireFrame), initParam, monoColorShaderFilePaths);
		}
	}
}