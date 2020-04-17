#include "TktkDX12Wrapper/Graphics/DX3D12/GraphicsPipeLineState/GraphicsPipeLineState.h"
#ifdef _DEBUG
#include <stdexcept>
#endif // _DEBUG

namespace tktk
{
	GraphicsPipeLineState::GraphicsPipeLineState(unsigned int graphicsPipeLineNum, unsigned int rootSignatureNum)
		: m_rootSignature(rootSignatureNum)
	{
		m_graphicsPipeLineStateDataArray.resize(graphicsPipeLineNum);
	}

	void GraphicsPipeLineState::createRootSignature(unsigned int id, ID3D12Device* device, const RootSignatureInitParam& initParam)
	{
		m_rootSignature.create(id, device, initParam);
	}

	void GraphicsPipeLineState::createGraphicsPipeLineState(unsigned int graphicsPipeLineId, ID3D12Device* device, const GraphicsPipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath, unsigned int useRootSignatureId)
	{
		// 頂点シェーダーを読み込む
		std::vector<char> vsByteArray;
		{
			std::FILE* fp;
	
			int ret = fopen_s(&fp, shaderFilePath.vsFilePath.c_str(), "rb");
	
#ifdef _DEBUG
			if (ret != 0)
			{
				throw std::runtime_error("load vertexShader error");
			}
#endif // _DEBUG
	
			fseek(fp, 0, SEEK_END);
			vsByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);
	
			fread(vsByteArray.data(), vsByteArray.size(), 1, fp);
			fclose(fp);
		}
	
		// ピクセルシェーダーを読み込む
		std::vector<char> psByteArray;
		{
			std::FILE* fp;
	
			int ret = fopen_s(&fp, shaderFilePath.psFilePath.c_str(), "rb");
	
#ifdef _DEBUG
			if (ret != 0)
			{
				throw std::runtime_error("load pixelShader error");
			}
#endif // _DEBUG
	
			fseek(fp, 0, SEEK_END);
			psByteArray.resize(ftell(fp));
			fseek(fp, 0, SEEK_SET);
	
			fread(psByteArray.data(), psByteArray.size(), 1, fp);
			fclose(fp);
		}
	
		m_graphicsPipeLineStateDataArray.at(graphicsPipeLineId).initialize(
			device,
			initParam,
			vsByteArray,
			psByteArray,
			m_rootSignature.getPtr(useRootSignatureId),
			useRootSignatureId
		);
	}

	void GraphicsPipeLineState::set(unsigned int id, ID3D12GraphicsCommandList* commandList) const
	{
		m_rootSignature.set(m_graphicsPipeLineStateDataArray.at(id).getUseRootSignatureIndex(), commandList);
		m_graphicsPipeLineStateDataArray.at(id).set(commandList);
	}
}